#ifndef _ICONFIGURABLE_H
#define _ICONFIGURABLE_H

#include "PropertyList.h"
#include "Filesystem.h"

class IConfigurable
{
    private:
        PropertyList m_Properties;
        bool m_bConfig;

    public:
        IConfigurable(const std::string& fn) {
            m_bConfig = open(fn);
        }
        virtual ~IConfigurable() {}

        bool open(const std::string& fn) {
            if(Filesystem::hasExtension(fn,"ini"))
                return m_Properties.open(fn.c_str());
            return false;
        }

        bool config() const { return m_bConfig; }
        const PropertyList& properties() const { return m_Properties; }
        PropertyList& properties() { return m_Properties; }
};

#endif

