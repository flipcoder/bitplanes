#ifndef _ICONFIGURABLE_H
#define _ICONFIGURABLE_H

#include "PropertyList.h"
#include "FileSystem.h"

class IConfigurable
{
    private:
        PropertyList m_Properties;

    public:
        IConfigurable(const std::string& fn) {
            open(fn);
        }
        virtual ~IConfigurable() {}

        bool open(const std::string& fn) {
            if(FileSystem::hasExtension(fn,"ini"))
                return m_Properties.open(fn.c_str());
            return false;
        }

        const PropertyList& properties() const { return m_Properties; }
        PropertyList& properties() { return m_Properties; }
};

#endif

