#include "Log.h"

#include <boost/circular_buffer.hpp>
#include <iostream>
#include <fstream>
using namespace std;

const int LOG_LENGTH = 256;
const std::string LOG_FILE = "log.txt";

Log::Log()
{
    m_cbLog.set_capacity(LOG_LENGTH);
    m_bStdOut = false;
    m_LogFile.open(LOG_FILE, ios_base::trunc);
}


Log::~Log()
{
}

void Log::write(const std::string& s, Log::Message::eLoggingLevel lev)
{
    m_cbLog.push_back(Message(s,lev));

    if(m_bStdOut)
    {
        if(lev == Message::LL_WARNING)
            cout << "[WARNING] ";
        else if(lev == Message::LL_ERROR)
            cout << "[ERROR] ";
        else if(lev == Message::LL_DEBUG)
            cout << "[DEBUG] ";
        cout << s << endl;
    }

    if(m_LogFile.is_open())
    {
        if(lev == Message::LL_WARNING)
            m_LogFile << "[WARNING] ";
        else if(lev == Message::LL_ERROR)
            m_LogFile << "[ERROR] ";
        else if(lev == Message::LL_DEBUG)
            m_LogFile << "[DEBUG] ";
        m_LogFile << s << endl;
    }
}

