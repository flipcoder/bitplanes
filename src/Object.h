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

class Object :
    public std::enable_shared_from_this<Object>,
    public IFallible,
    public IRealtime,
    public IRenderable,
    public IConfigurable,
    public ITaggable,
    public IType
{
    private:

        std::shared_ptr<Sprite> m_spSprite;
        std::map<std::string, std::shared_ptr<Image>> m_Images;
        Vector2 m_vPos;
        Vector2 m_vVel;
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
            m_spSprite->setImage(image(s));
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
        virtual void init() {}
        virtual bool logic(float t) {
            m_vPos += ((m_vVel - world()->vel()) * t);
            m_spSprite->pos(m_vPos);
            return true;
        }
        virtual void render() const {
            if(!m_spSprite || invalid())
                return;
            m_spSprite->render();
        }
        virtual float depth() const { return 0.0f; }

        static const char* type() { return "object"; }

        // (to be called by World) assigns a world pointer to this item
        void setWorld(World* world) {
            m_pWorld = world;
            init();
        }

        bool invalid() const { return m_bInvalid; }
        void invalidate(bool b = true) { m_bInvalid = b; }

        const Vector2& pos() const { return m_vPos; }

        void pos(float x, float y) {
            m_vPos = Vector2(x,y);
        }
        void pos(const Vector2& pos) {
            m_vPos = pos;
            if(m_spSprite)
                m_spSprite->pos(m_vPos);
        }
        void move(const Vector2& rel) {
            m_vPos += rel;
            if(m_spSprite)
                m_spSprite->pos(m_vPos);
        }
        Vector2 size() const { return sprite().image() ? sprite().image()->size() : Vector2(); }
        const Sprite& sprite() const { return *m_spSprite.get(); }
        Sprite& sprite() { return *m_spSprite.get(); }

        virtual bool solid() const { return false; }
        virtual bool collidable() const { return false; }
        //virtual bool handlesCollisionEvent() { return false; }
        virtual void collisionEvent(std::shared_ptr<Object>& obj) {}

        const Vector2& vel() const { return m_vVel; }
        Vector2& vel() { return m_vVel; }
        void vel(const Vector2& v) { m_vVel = v; }
};

#endif

