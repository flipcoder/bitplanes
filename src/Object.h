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
        Sprite m_Sprite;
        Vector2 m_vVel;
        std::vector<std::shared_ptr<Image>> m_vImages;

        void nullify() {
        }


    protected:

        const PropertyList& properties() const { return m_Properties; }
        PropertyList& properties() { return m_Properties; }
        const Sprite& sprite() const { return m_Sprite; }
        Sprite& sprite() { return m_Sprite; }
        const Vector2& vel() const { return m_vVel; }
        Vector2& vel() { return m_vVel; }
        const std::vector<std::shared_ptr<Image>>& images() const { return m_vImages; }
        std::vector<std::shared_ptr<Image>>& images() { return m_vImages; }

    public:

        Object(const std::string& fn);
        virtual ~Object();
        virtual void render() const {
        }
};

#endif

