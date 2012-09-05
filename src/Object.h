#ifndef _OBJECT_H
#define _OBJECT_H

#include <vector>
#include <memory>
#include "Sprite.h"
#include "Filesystem.h"
#include "World.h"
#include "IConfigurable.h"
#include "ITaggable.h"
#include "IType.h"
#include "IMovable.h"
#include "IAudible.h"

class Object :
    public std::enable_shared_from_this<Object>,
    public IFallible,
    public IRealtime,
    public IRenderable,
    public ITaggable,
    public IType,
    public IConfigurable,
    public IAudible,
    virtual public IMovable
{
    private:

        std::shared_ptr<Sprite> m_spSprite;
        std::map<std::string, std::shared_ptr<Image>> m_Images;
        World* m_pWorld; // weak
        bool m_bInvalid;

        void nullify() {
            m_pWorld = nullptr;
            m_bInvalid = false;
        }

    protected:
        
        
        //const std::vector<std::shared_ptr<Image>>& images() const { return m_Images; }
        std::map<std::string,std::shared_ptr<Image>>& images() { return m_Images; }
        std::shared_ptr<Image> image(const std::string& s) {
            if(m_Images.find(s) == m_Images.end())
                return nullptr;
            return m_Images[s];
        }
        bool setImage(const std::string& s) {
            auto img = image(s);
            if(!img)
                return false;
            m_spSprite->setImage(img);
            return true;
        }
        World* world() { return m_pWorld; }
        const World* world() const { return m_pWorld; }
        //Image* image(size_t idx) {
        //    try{
        //        return m_Images.at(idx).get();
        //    }catch(const std::out_of_range& e){
        //        return nullptr;
        //    }
        //}
        //const Image* image(size_t idx) const {
        //    try{
        //        return m_Images.at(idx).get();
        //    }catch(const std::out_of_range& e){
        //        return nullptr;
        //    }
        //}
        
    public:

        Object(const std::string& fn);
        virtual ~Object();
        
        virtual void onAdd() {}
        virtual void onRemove() {}

        //virtual void init() {}
        virtual void logic(float t) {
            IMovable::logic(t);
            //move(vel() * t);
            //move((vel() - world()->vel()) * t);
        }
        virtual void render() const {
            if(!m_spSprite || invalid())
                return;
            m_spSprite->render();
        }

        static const char* type() { return "object"; }

        // (to be called by World) assigns a world pointer to this item
        void setWorld(World* world) {
            m_pWorld = world;
        }

        bool invalid() const { return m_bInvalid; }
        void invalidate(bool b = true) { m_bInvalid = b; }

        Vector2 size() const { return sprite().image() ? sprite().image()->size() : Vector2(); }
        const Sprite& sprite() const { return *m_spSprite.get(); }
        Sprite& sprite() { return *m_spSprite.get(); }

        virtual bool solid() const { return false; }
        virtual bool collidable() const { return false; }
        //virtual bool handlesCollisionEvent() { return false; }
        virtual void collisionEvent(std::shared_ptr<Object>& obj) {}
        
        void updateSprite() {
            m_spSprite->pos(pos());
        }
};

#endif

