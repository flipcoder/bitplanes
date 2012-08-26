#ifndef _FILESYSTEM_H
#define _FILESYSTEM_H

#include <string>
#include "IStaticInstance.h"

// TODO: This file needs massive improvement

namespace Filesystem
{
    std::string getFileName(const std::string& path);
    std::string getPathName(const std::string& path);
    std::string getExtension(const std::string& path);
    std::string cutExtension(const std::string& path);
    std::string getFileNameNoExt(std::string path);
    bool hasExtension(const std::string& path, const std::string& ext);
    bool pathCompare(const std::string& a, const std::string& b);
}

#endif

