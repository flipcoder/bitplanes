#ifndef _ICONFIGURABLE_H
#define _ICONFIGURABLE_H

#include <boost/filesystem/path.hpp>
#include "PropertyList.h"
#include "Filesystem.h"
#include "System.h"

class IConfigurable
{
    private:
        PropertyList m_Properties;
        bool m_bConfig;
        boost::filesystem::path m_path;

    public:
        
        //IConfigurable() {
        //    assert(false);
        //}

        explicit IConfigurable(const std::string& fn, const std::string& path = "") {
            m_bConfig = open(fn, path);
        }
        virtual ~IConfigurable() {}

        bool open(const std::string& fn, const std::string& path = "") {
            if(Filesystem::hasExtension(fn,"ini")) {
                // TODO: use something broader than imageResources()
                //  this needs to work for audio paths also (see new path param)
                m_path = System::get().imageResources().resolvePath(fn);
                return m_Properties.open(m_path.string().c_str());
            }
            return false;
        }

        bool config() const { return m_bConfig; }
        const PropertyList& properties() const { return m_Properties; }
        PropertyList& properties() { return m_Properties; }
};

#endif

