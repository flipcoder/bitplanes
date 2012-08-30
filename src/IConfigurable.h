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
                std::vector<boost::filesystem::path> search_paths;
                if(!path.empty()) {
                    search_paths.push_back(boost::filesystem::path(path));
                    m_path = Filesystem::locate(fn, search_paths);
                } else {
                    // use system imageResources path as default
                    m_path = System::get().imageResources().locate(fn);
                }
                if(m_path.empty())
                    return false;
                return m_Properties.open(m_path.string().c_str());
            }
            return false;
        }

        bool config() const { return m_bConfig; }
        const PropertyList& properties() const { return m_Properties; }
        PropertyList& properties() { return m_Properties; }
};

#endif

