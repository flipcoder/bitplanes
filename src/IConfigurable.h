#ifndef _ICONFIGURABLE_H
#define _ICONFIGURABLE_H

#include "PropertyList.h"
#include "Filesystem.h"
#include "System.h"

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
            if(Filesystem::hasExtension(fn,"ini")) {
                // assume all inis without fullpaths are inside an imageResources path
                boost::filesystem::path path = System::get().imageResources().resolvePath(fn);
                return m_Properties.open(path.string().c_str());
            }
            return false;
        }

        bool config() const { return m_bConfig; }
        const PropertyList& properties() const { return m_Properties; }
        PropertyList& properties() { return m_Properties; }
};

#endif

