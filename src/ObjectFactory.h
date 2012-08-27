#ifndef _OBJECTFACTORY_H
#define _OBJECTFACTORY_H

#include <memory>
#include <string>
class Object;
class World;

class ObjectFactory
{
    private:
        World* m_pWorld;
    public:
        ObjectFactory(World* world):
            m_pWorld(world)
        {}
        virtual ~ObjectFactory() {}
        std::shared_ptr<Object> create(std::string name, std::string type="");
};

#endif

