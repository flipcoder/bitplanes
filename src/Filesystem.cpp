#include "Filesystem.h"
#include <string>
#include "Util.h"
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
using namespace std;

namespace FS
{

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
	return stringEndsWith<std::string>(boost::to_upper_copy(path), boost::to_upper_copy(ext));
}

bool pathCompare(const std::string& a, const std::string& b)
{
	return boost::filesystem::equivalent(
			boost::filesystem::path(a),
			boost::filesystem::path(b));
	//return a==b;
}

};//namespace FS

