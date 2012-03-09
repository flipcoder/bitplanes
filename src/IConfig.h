#ifndef _ICONFIG_H
#define _ICONFIG_H

#include "PropertyList.h"
#include "FileSystem.h"

class IConfig
{
    private:
        PropertyList m_Properties;

    public:
        IConfig(const std::string& fn) {
            open(fn);
        }
        virtual ~IConfig() {}

        bool open(const std::string& fn) {
            if(FileSystem::hasExtension(fn,"ini"))
                return m_Properties.open(fn.c_str());
			return false;
        }

        const PropertyList& properties() const { return m_Properties; }
        PropertyList& properties() { return m_Properties; }
};

#endif

