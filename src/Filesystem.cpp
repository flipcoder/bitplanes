#include "Filesystem.h"
#include <string>
#include "Util.h"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
using namespace std;

namespace Filesystem {

// takes an absolute or relative path and returns the file name (including ext)
std::string getFileName(const std::string& path)
{
    size_t split_point;
    if((split_point = path.find_last_of("\\/")) != string::npos)
        return path.substr(split_point+1);
    return path;
}

std::string getPathName(const std::string& path)
{
    size_t split_point;
    if((split_point = path.find_last_of("\\/")) != string::npos)
        return path.substr(0,split_point+1);
    return "";
}

std::string getExtension(const std::string& path)
{
    size_t split_point;
    if((split_point = path.find_last_of(".")) != string::npos)
        return path.substr(split_point+1);
    return "";
}

std::string cutExtension(const std::string& path)
{
    size_t split_point;
    if((split_point = path.find_last_of(".")) != string::npos)
        return path.substr(0, split_point);
    return "";
}

std::string getFileNameNoExt(std::string path)
{
    size_t split_point;
    if((split_point = path.find_last_of("\\/")) != string::npos)
        return path.substr(split_point+1);
    return cutExtension(path);
}

bool hasExtension(const std::string& path, const std::string& ext)
{
    return stringEndsWith<std::string>(boost::to_lower_copy(path), boost::to_lower_copy(ext));
}

bool hasExtension(const std::string& path)
{
    size_t dot, pathsep;

    if(std::string::npos == (dot = path.find_last_of("."))) // get dot location
        return false; // no dot = no extension
    if(std::string::npos == (pathsep = path.find_last_of("\\/")))
        return true; // dot + no pathsep = has extension

    return dot > pathsep; // last dot comes after last pathsep?
}

bool pathCompare(const std::string& a, const std::string& b)
{
    return boost::filesystem::equivalent(
            boost::filesystem::path(a),
            boost::filesystem::path(b));
    //return a==b;
}

}

