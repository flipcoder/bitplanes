#ifndef _OBJECT_H
#define _OBJECT_H

#include <vector>
#include <memory>
#include "Sprite.h"
#include "PropertyList.h"

class Object : public IFallible, public IRealtime, public IDepth
{
    private:

        PropertyList m_Properties;
        std::shared_ptr<Sprite> m_spSprite;
        std::vector<std::shared_ptr<Image>> m_vImages;
        Vector2 m_vPos;

        void nullify() {
        }


    protected:

        const PropertyList& properties() const { return m_Properties; }
        PropertyList& properties() { return m_Properties; }
        const Sprite& sprite() const { return *m_spSprite.get(); }
        Sprite& sprite() { return *m_spSprite.get(); }
        //const Vector2& vel() const { return m_vVel; }
        //Vector2& vel() { return m_vVel; }
        const std::vector<std::shared_ptr<Image>>& images() const { return m_vImages; }
        std::vector<std::shared_ptr<Image>>& images() { return m_vImages; }
        Image* image(size_t idx) {
            try{
                return m_vImages.at(idx).get();
            }catch(const std::out_of_range& e){
                return nullptr;
            }
        }
        const Image* image(size_t idx) const {
            try{
                return m_vImages.at(idx).get();
            }catch(const std::out_of_range& e){
                return nullptr;
            }
        }
        const Vector2& pos() const { return m_vPos; }
        Vector2& pos() { return m_vPos; }

    public:

        Object(const std::string& fn);
        virtual ~Object();
        virtual bool logic(float t) {
            m_spSprite->pos() = pos();
            return true;
        }
        virtual void render() const {
            if(!m_spSprite)
                return;
            m_spSprite->render();
        }
};

#endif

