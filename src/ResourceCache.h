#ifndef _RESOURCECACHE_H
#define _RESOURCECACHE_H

#include <map>
#include <vector>
#include <memory>
#include <algorithm>
#include <boost/filesystem.hpp>

template<class T>
class ResourceCache
{
public:

    //enum eFlags {
    //    F_PASS_NAME = BIT(0),
    //};

private:

    std::map<std::string, std::shared_ptr<T>> m_Resources;
    std::vector<std::string> m_Extensions;
    std::vector<boost::filesystem::path> m_Paths;

public:

    ResourceCache() {}
    virtual ~ResourceCache() {}

    unsigned int size() const { return m_Resources.size(); }
    bool empty() const { return m_Resources.empty(); }

    bool addExtension(std::string ext) {
        if(std::find(m_Extensions.begin(), m_Extensions.end(), ext) == m_Extensions.end())
            return false;
        m_Extensions.push_back(ext);
        return true;
    }
    bool removeExtension(std::string ext) {
        return m_Extensions.erase(
            std::find(m_Extensions.begin(),
            m_Extensions.end(), ext)
        ) != m_Extensions.end();
    }
    bool addPath(boost::filesystem::path path) {
        // path does not need to exist (its just a search point)
        for(auto itr = m_Paths.begin();
            itr != m_Paths.end();
            ++itr)
            if(boost::filesystem::equivalent(*itr, path))
                return false;
        m_Paths.push_back(path);
        return true;
    }
    bool removePath(boost::filesystem::path path) {
        for(auto itr = m_Paths.begin();
            itr != m_Paths.end();
            ++itr)
            if(boost::filesystem::equivalent(*itr, path)) {
                m_Paths.erase(itr);
                return true;
            }
        return false;
    }

    //bool add(std::string name, T* resource) {
    //    if(m_Resources.find(name) == m_Resources.end()){
    //        m_Resources[name].reset(resource);
    //        return true;
    //    }
    //    return false;
    //}

    //T* ensure(std::string name) {
    //    typename std::map<std::string, std::shared_ptr<T>>::iterator itr;
    //    if((itr = m_Resources.find(name)) == m_Resources.end()) {
    //        T* r = new T();
    //        m_Resources[name].reset(r);
    //        return r;
    //    }
    //    return itr->second.get();
    //}
    //
    boost::filesystem::path resolvePath(std::string name) {
        boost::filesystem::path path;
        foreach(auto& search_path, m_Paths) {
            //Log::get().write(search_path.string());
            path = search_path / name;
            //Log::get().write(path.string());

            if(path.extension().empty()) {
                foreach(auto& ext, m_Extensions) { // each extenion
                    boost::filesystem::path temp_path = path;
                    temp_path.replace_extension("."+ext);
                    if(boost::filesystem::exists(temp_path))
                        return temp_path;
                }
            }
            else if(boost::filesystem::exists(path))
                return path;
        }
        return boost::filesystem::path(); // empty
    }

    std::shared_ptr<T> cache(std::string name) {
        // if name has extension
        //   search for a specific file in the path with only the specific extension
        // else
        //   search for any file that matches

        // if a path is given, treat it as the actual path, instead of searching
        if(name.find('/') == std::string::npos &&
            name.find('\\') == std::string::npos &&
            name.find(":") == std::string::npos // ignore path resolution for interfile resources
            )
        {
            boost::filesystem::path path = resolvePath(name);
            if(path.empty())
                return std::shared_ptr<T>();
            name = path.string();
        }

        typename std::map<std::string, std::shared_ptr<T>>::iterator itr;
        if((itr = m_Resources.find(name)) == m_Resources.end()) {
            //T* r = (flags & F_PASS_NAME) ? new T(name) : new T(); // might throw
            m_Resources[name].reset(new T(name));
            return m_Resources[name];
        }
        return itr->second;
    }

    void remove(std::string name) {
        for(auto itr = m_Resources.begin();
            itr != m_Resources.end();
            ++itr)
        {
            if(itr->first == name) {
                //delete itr->second;
                m_Resources.erase(itr);
                break;
            }
        }
    }

    //T* get(std::string name) {
    //    typename std::map<std::string, std::shared_ptr<T>> itr;
    //    if((itr = m_Resources.find(name)) == m_Resources.end())
    //        return NULL;
    //    return itr->second.get();
    //}

    std::shared_ptr<T> get_shared(std::string name) {
        typename std::map<std::string, std::shared_ptr<T>> itr;
        if((itr = m_Resources.find(name)) == m_Resources.end())
            return NULL;
        return itr->second;
    }

    void clear(){
        //for(auto itr = m_Resources.begin();
        //    itr != m_Resources.end();
        //    ++itr)
        //{
        //    delete itr->second;
        //}
        m_Resources.clear();
    }
    void optimize() {
        for(auto itr = m_Resources.begin();
            itr != m_Resources.end();)
        {
            if(itr->count() == 1)
                itr = m_Resources.erase(itr);
            else
                ++itr;
        }
    }
};

#endif

