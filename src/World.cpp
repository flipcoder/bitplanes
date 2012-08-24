#include "World.h"
#include "Object.h"
#include "ScriptInterface.h"
#include "IOwnable.h"

World :: World()
{
    nullify();
}

World :: World(const std::string& fn)
{
    nullify();
    m_spScript.reset(new Script(fn));
    m_spFactory.reset(new ObjectFactory(this));
    m_spScript->enable(new ScriptInterface(m_spScript.get(), this,  m_spFactory.get()));
    m_spScript->reset();
}

void World :: logic(float t)
{
    m_WorldTime.logic(t*1000.0f);
    if(m_spScript)
        m_spScript->logic(t*1000.0f);

    // TODO: Add collision checking here for all objects that
    //  obj.collidable()==true
   
    // locking below is not for thread-safety
    // it is just to make sure objects added while inside the loop are not called yet
    m_bLocked = true; 
    for(auto itr = m_Objects.begin();
        itr != m_Objects.end();)
    {
        (*itr)->logic(t);
        if((*itr)->invalid())
            itr = m_Objects.erase(itr);
        else
            ++itr;
    }

    for(auto itr = m_Objects.begin();
        itr != m_Objects.end();
        ++itr)
    {
        // this prevents rechecks
        auto next_itr = itr;
        ++next_itr;

        if(next_itr != m_Objects.end())
            for(auto jtr = next_itr;
                jtr != m_Objects.end();
                ++jtr)
            {
                //if(*itr == *jtr) // this shouldn't happen anymore
                //    continue;
                if((*itr)->collidable() && (*jtr)->collidable())
                    if(collision(*itr, *jtr))
                    {
                        // since we're not rechecking, we'll call both objects' collisionEvents
                        // TODO: (when needed) add a flag to let collisionEvents
                        // know which object was called first
                        (*itr)->collisionEvent(*jtr);
                        (*jtr)->collisionEvent(*itr);
                    }
            }
    }
    m_bLocked = false;

    // move spawners (objects added during loop above) to object list
    m_Objects.splice(m_Objects.end(), m_SpawnList);
}

void World :: render() const
{
    foreach(auto& obj, m_Objects)
        obj->render();
}

bool World :: add(std::shared_ptr<Object> obj) {
    //if(m_Objects.find(obj) != m_Objects.end())
    //    return false;
    //if(m_SpawnList.find(obj) != m_SpawnList.end())
    //    return false;
    
    // locking takes place in World::logic(), so we don't modify the list while iterating and miss object logic calls
    if(m_bLocked)
        m_SpawnList.push_back(obj);
    else
        m_Objects.push_back(obj);
    
    obj->setWorld(this);
    return true;
}

bool World :: pixelCollision(const std::shared_ptr<const Object>& a, const std::shared_ptr<const Object>& b) const
{
    std::vector<const Image*> img(2);
    img[0] = a->sprite().image().get();
    img[1] = b->sprite().image().get();

    // TODO: finish this
    // calc overlap?
    // use image->pixel(x,y); to get Color() and use alpha value

    return true;
}

bool World :: collision(const Box_t& a, const Box_t& b) const
{
    if( (a.x    > b.x + b.w - 1)||
        (a.y    > b.y + b.h - 1)||
        (b.x > a.x    + a.w - 1)||
        (b.y > a.y    + a.h - 1))
    {
        return false;
    }
    return true;
}

bool World :: collision(const std::shared_ptr<const Object>& a, const std::shared_ptr<const Object>& b) const
{
    if(!a || !b || !a->sprite().image() || !b->sprite().image())
        return false;

    Box_t box_a,box_b;
    std::vector<const Image*> img(2);
    img[0] = a->sprite().image().get();
    img[1] = b->sprite().image().get();

    box_a.set(round_int(a->pos().x), round_int(a->pos().y),
        round_int(img[0]->size().x), round_int(img[0]->size().y));
    box_b.set(round_int(b->pos().x), round_int(b->pos().y),
        round_int(img[1]->size().x), round_int(img[1]->size().y));

    if(!collision(box_a,box_b))
        return false;
    
    return pixelCollision(a,b);
}

bool World :: outsideScreen(const Box_t& a) const
{
    return (a.x+a.w < 0) ||
          (a.y+a.h < 0) ||
          (a.x > System::get().w()) ||
          (a.y > System::get().h());
}

bool World :: outsideScreen(const std::shared_ptr<const Object>& a) const
{
    if(!a || !a->sprite().image())
        return false;

    const Image* img = a->sprite().image().get();

    Box_t box_a(
        round_int(a->pos().x),
        round_int(a->pos().y),
        round_int(img->size().x),
        round_int(img->size().y)
    );

    return outsideScreen(box_a);
}

// current screen contain any enemies?
bool World :: hasEnemies() const
{
    foreach(auto& obj, m_SpawnList)
    {
        IOwnable* ownable;
        if(ownable = dynamic_cast<IOwnable*>(obj.get()))
        {
            if(ownable->owner() && ownable->owner() == IOwnable::O_ENEMY)
                return true; // area contains enemey
        }
    }
    foreach(auto& obj, m_Objects)
    {
        IOwnable* ownable;
        if(ownable = dynamic_cast<IOwnable*>(obj.get()))
        {
            if(ownable->owner() && ownable->owner() == IOwnable::O_ENEMY)
                return true; // area contains enemey
        }
    }

    return false;
}

