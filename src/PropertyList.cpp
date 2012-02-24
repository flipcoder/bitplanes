
#include "PropertyList.h"
#include <fstream>
//#include <iostream>
#include <sstream>
using namespace std;

#define LINELENGTH 256
#define DEFAULT_GROUP "default"

const std::string badchars = "\r\t";

void PropertyList :: cutCmdString(std::string& s)
{
    size_t index;

    for(size_t i=0; i < badchars.size(); i++)
    {
        while( ( index = s.find(badchars[i]) ) != string::npos )
            s.erase(index);
    }
}

void PropertyList :: cutQuotedString(std::string& s)
{
    size_t index;
    while((index = s.find('\"')) != s.npos)
        s.erase(index);
    while((index = s.find('\'')) != s.npos)
        s.erase(index);
}

void PropertyList :: cutAdjacentChars(std::string& s, std::string chars)
{
    size_t start_str = s.find_first_not_of(chars);
    size_t end_str = s.find_last_not_of(chars);
    if(start_str == s.npos)
        start_str = 0;
    if(end_str == s.npos)
        end_str = s.length();

    s = s.substr(start_str, end_str - start_str + 1);
}

std::string PropertyList :: getStringRep(const std::string& s)
{
    if(s.empty())
        return "";

    if(s.find(' ') != s.npos) // if string has spaces
    {
        if(!(s[0]=='\"' && s[s.length()-1]=='\"'))
        {
            ostringstream oss;
            oss << '\"' << s << '\"';
            return oss.str();
        }
        else
            return "";
    }
    else
        return s;
}

void PropertyList :: parseLine(const std::string& s, std::string& group)
{
    // make local copy of const string `s`
    std::string _s = s;

    // TODO cut out adjacent spaces and tabs
    cutAdjacentChars(_s," \t");

    // throw out blank lines
    if(_s.length()==0)
        return;

    // ignore comment lines (example: "// comment here")
    if(_s[0]=='/' && _s[1] == '/')
        return;
    if(_s[0]=='#' || _s[0]==';')
        return;

    // group line (example: "[MyGroup]")
    if(_s[0]=='[' && _s[_s.length()-1]==']')
    {
        string group_name = _s.substr(1, _s.length()-2);
        cutAdjacentChars(group_name, " \t");

        if(group_name.length()==0)
            return;

        // enter current group
        group = group_name;

        if(m_GroupList.find(group) == m_GroupList.end())
        {
            // new group
            m_GroupList[group] = Group();
        }
    }
    else if(_s.find('=') != _s.npos) // has = sign
    {
        size_t eq_idx = _s.find('=');
        pair<string,string> prop;

        // if no characters before or after equal sign, return
        if(eq_idx + 1 >= _s.length())
            return;
        if(eq_idx - 1 < 0)
            return;

        prop.first = _s.substr(0, eq_idx);
        cutAdjacentChars(prop.first, " \t");
        cutQuotedString(prop.first);

        prop.second = _s.substr(eq_idx+1);
        cutAdjacentChars(prop.second, " \t");
        cutQuotedString(prop.second);

        // add property inside the current group
        m_GroupList[group][prop.first] = prop.second;
        
        //cout<<"PL: "<<_s.substr(0, eq_idx)<<": "
        //    <<prop.second<<endl;
    }
}

int PropertyList :: stringToInt(const std::string& s) const
{
    std::istringstream iss(s);
    int n;
    if((iss >> n).fail())
        return 0;
    return n;

//    unsigned int n = 0;
//    unsigned int digit = 1;
//    int num = 0;
//    std::string _s = s;

//    while(1)
//    {
//        n = _s.find_last_of("0123456789");
//        if(n == _s.npos)
//            break;

//        num += (((int)_s[n] - '0') * digit);
//        digit *= 10;
//        _s[n] = ' ';
//    };

//    if(_s[0] == '-')
//        return -num;
//    return num;
}

float PropertyList :: stringToFloat(const std::string& s) const
{
    std::istringstream iss(s);
    float f;
    if((iss >> f).fail())
        return 0.0f;
    return f;
}

bool PropertyList :: open(const char* fn)
{
    ifstream file;
    string line;
    string group = DEFAULT_GROUP;

    file.open(fn);
    if(!file.is_open())
        return false;

    while(!file.eof())
    {
        getline(file, line);
        cutCmdString(line);
        parseLine(line, group);
    }

    return true;
}

bool PropertyList :: save(const char* fn)
{
    ofstream file;

    file.open(fn, ios::trunc);
    if(!file.is_open())
        return false;

    // save all properties in default group at the top of the file
    for(std::map<std::string, Group>::iterator itr = m_GroupList.begin();
        itr != m_GroupList.end();
        itr++)
    {
        if(itr->first.compare(DEFAULT_GROUP)==0)
        {
            for(Group::iterator jtr = itr->second.begin();
                jtr != itr->second.end();
                jtr++)
                {
                    file << jtr->first << " = " << getStringRep(jtr->second) << std::endl;
                }

            file << std::endl;
        }
    }

    // save the named group properties in their respective group sections
    for(std::map<std::string, Group>::iterator itr = m_GroupList.begin();
        itr != m_GroupList.end();
        itr++)
    {
        // skip default group, since they were already saved
        if(itr->first.compare(DEFAULT_GROUP)==0)
            continue;

        file << "[" << itr->first << "]" << std::endl;

        for(Group::iterator jtr = itr->second.begin();
            jtr != itr->second.end();
            jtr++)
        {
            file << jtr->first << " = " << getStringRep(jtr->second) << std::endl;
        }

        file << std::endl;
    }

    return true;
}


bool PropertyList :: getStringValue(const char* _group, const char* _prop, std::string& value)
{
    if(m_GroupList.find(_group) != m_GroupList.end())
        if(m_GroupList[_group].find(_prop) != m_GroupList[_group].end())
        {
            value = m_GroupList[_group][_prop];
            return true;
        }
    return false;
}

bool PropertyList :: getIntValue(const char* _group, const char* _prop, int& value)
{
    if(m_GroupList.find(_group) != m_GroupList.end())
        if(m_GroupList[_group].find(_prop) != m_GroupList[_group].end())
        {
            value = stringToInt(m_GroupList[_group][_prop]);
            return true;
        }
    return false;
}

bool PropertyList :: getFloatValue(const char* _group, const char* _prop, float& value)
{
    if(m_GroupList.find(_group) != m_GroupList.end())
        if(m_GroupList[_group].find(_prop) != m_GroupList[_group].end())
        {
            value = stringToFloat(m_GroupList[_group][_prop]);
            return true;
        }
    return false;
}


void PropertyList :: setStringValue(const char* _group, const char* _prop, const std::string& value)
{
    if(value.length()==0)
        removeProperty(_group, _prop);

    m_GroupList[_group][_prop] = value;
}

void PropertyList :: setIntValue(const char* _group, const char* _prop, const int value)
{
    ostringstream oss;
    oss << value;
    m_GroupList[_group][_prop] = oss.str();
}

void PropertyList :: setFloatValue(const char* _group, const char* _prop, const float value)
{
    ostringstream oss;
    oss << value;
    m_GroupList[_group][_prop] = oss.str();
}


void PropertyList :: removeProperty(const char* _group, const char* _prop)
{
    if(m_GroupList.find(_group) != m_GroupList.end())
        if(m_GroupList[_group].find(_prop) != m_GroupList[_group].end())
            m_GroupList[_group].erase(m_GroupList[_group].find(_prop));
}

void PropertyList :: removeGroup(const char* _group)
{
    if(m_GroupList.find(_group) != m_GroupList.end())
        m_GroupList.erase(m_GroupList.find(_group));
}
