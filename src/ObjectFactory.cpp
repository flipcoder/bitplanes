#include "ObjectFactory.h"
#include "Enemy.h"
#include "Particle.h"
#include "Backdrop.h"
#include "Filesystem.h"
#include "Item.h"

std::shared_ptr<Object> ObjectFactory :: create(std::string name, std::string type)
{
    // create an Object class as a prototype to open config file of above name
    std::unique_ptr<Object> prototype;

    if(!Filesystem::hasExtension(name))
        name += ".ini";
    
    // deduce type from ini
    if(type.empty())
    {
        // trying to deduce type of object without extension is impossible
        if(!Filesystem::hasExtension(name, "ini"))
        {
            assert(false);
            return std::shared_ptr<Object>();
        }

        PropertyList properties;
        boost::filesystem::path path = System::get().imageResources().locate(name);
        name = path.string();

        if(!properties.open(name.c_str()))
        {
            assert(false);
            return std::shared_ptr<Object>();
        }
        type = properties.getString("default", "type", "");
        if(type.empty())
        {
            assert(false);
            return std::shared_ptr<Object>();
        }
    }   

    //// locate an object
    //if(Filesystem::hasExtension("ini"))
    //{
    //    std::vector<boost::filesystem::path> search_paths;
    //    if(type == "backdrop")
    //        search_paths.push_back(boost::filesystem::path("data/backdrops/"));
    //    else
    //        search_paths.push_back(boost::filesystem::path("data/objects/"));
    //    std::vector<std::string> extensions;

    //    extensions.push_back("ini"); // load as image

    //    boost::filesystem::path found = Filesystem::locate(name, search_paths, extensions);
    //    if(found)
    //        name = found.string();
    //}

    // dispatch pattern by object type, return Object pointer
    try{
        std::shared_ptr<Object> object;
        // add more object types to this list
        if(type == "enemy")
            object.reset(new Enemy(name));
        else if(type == "particle")
            object.reset(new Particle(name));
        else if(type == "backdrop")
            object.reset(new Backdrop(name));
        else if(type == "item")
            object.reset(new Item(name));
        else
            return std::shared_ptr<Object>();

        if(object)
            m_pWorld->add(object);
        return object;
    } catch(const Failure& f){
        assert(false);
    }

    return std::shared_ptr<Object>();
}

