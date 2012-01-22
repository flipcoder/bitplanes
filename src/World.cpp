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

bool World :: collision(const Box_t& a, const Box_t& b) const
{
    return false;
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
    
    // TODO: Pixel-perfect collision here
    
    return true;
}

bool World :: outsideScreen(const Box_t& a) const
{
    return true;
    //return (a.x+a.w < 0) ||
    //       (a.y+a.h < 0) ||
    //       (a.x > System::get().w()) ||
    //       (a.y > System::get().h());

}

bool World :: outsideScreen(const std::shared_ptr<const Object>& a) const
{
    if(!a || a->sprite().image())
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

