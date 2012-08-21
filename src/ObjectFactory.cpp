#include "ObjectFactory.h"
#include "Enemy.h"
#include "Particle.h"
#include "Backdrop.h"

std::shared_ptr<Object> ObjectFactory :: create(const std::string& name)
{
    // create an Object class as a prototype to open config file of above name
    std::unique_ptr<Object> prototype;
    
    PropertyList properties;
    if(!properties.open(name.c_str()))
        return std::shared_ptr<Object>();
    std::string type = properties.getString("default", "type", "");
    if(type.empty())
        return std::shared_ptr<Object>();

    try{
        std::shared_ptr<Object> object;
        // add more object types to this list
        if(type == "enemy")
            object.reset(new Enemy(name));
        else if(type == "particle")
            object.reset(new Particle(name));
        else if(type == "backdrop")
            object.reset(new Backdrop(name));
        else
            return std::shared_ptr<Object>();

        m_pWorld->add(object);
        return object;
    } catch(const Failure& f){
    }

    // check the type of the object
    // dispatch pattern by object type, return Object pointer
    return std::shared_ptr<Object>();
}

