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

        void nullify() {
        }

    protected:

        const PropertyList& properties() const { return m_Properties; }
        PropertyList& properties() { return m_Properties; }

    public:

        Object(const std::string& fn);
        virtual ~Object();

        virtual void render() const {
        }
};

#endif

