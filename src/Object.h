#ifndef _OBJECT_H
#define _OBJECT_H

#include <vector>
#include <memory>
#include "Sprite.h"
#include "FileSystem.h"
#include "World.h"
#include "IConfig.h"
#include "ITaggable.h"
#include "IType.h"

class Object :
    public std::enable_shared_from_this<Object>,
    public IFallible,
    public IRealtime,
    public IRenderable,
    public IConfig,
    public ITaggable,
    public IType
{
    private:

        std::shared_ptr<Sprite> m_spSprite;
        std::map<std::string, std::shared_ptr<Image>> m_Images;
        Vector2 m_vPos;
        World* m_pWorld; // weak
        bool m_bInvalid;

        void nullify() {
            m_bInvalid = false;
        }

        std::string m_sClass;

    protected:
        
        //const Vector2& vel() const { return m_vVel; }
        //Vector2& vel() { return m_vVel; }
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
            m_spSprite->pos() = pos();
            return true;
        }
        virtual void render() const {
            if(!m_spSprite)
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
        Vector2& pos() { return m_vPos; }
        Vector2 size() const { return sprite().image() ? sprite().image()->size() : Vector2(); }
        const Sprite& sprite() const { return *m_spSprite.get(); }
        Sprite& sprite() { return *m_spSprite.get(); }

        virtual bool solid() const { return false; }
        virtual bool collidable() const { return false; }
        //virtual bool handlesCollisionEvent() { return false; }
        virtual void collisionEvent(std::shared_ptr<Object>& obj) {}

};

#endif

