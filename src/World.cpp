#include "World.h"
#include "Object.h"

bool World :: logic(float t)
{
    m_bLocked = true;
    for(std::list<std::shared_ptr<Object>>::iterator itr = m_Objects.begin();
        itr != m_Objects.end();)
    {
        (*itr)->logic(t);
        if((*itr)->invalid())
            itr = m_Objects.erase(itr);
        else
            itr++;
    }
    m_bLocked = false;

    // move spawners to object list
    m_Objects.splice(m_Objects.end(), m_SpawnList);
    return true;
}

void World :: render() const
{
    foreach(auto& obj, m_Objects)
        obj->render();
}

bool World :: add(std::shared_ptr<Object>& obj) {
    //if(m_Objects.find(obj) != m_Objects.end())
    //    return false;
    //if(m_SpawnList.find(obj) != m_SpawnList.end())
    //    return false;
    
    if(m_bLocked)
        m_SpawnList.push_back(obj);
    else
        m_Objects.push_back(obj);
    
    obj->setWorld(this);
    return true;
}

