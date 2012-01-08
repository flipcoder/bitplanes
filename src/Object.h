#ifndef _OBJECT_H
#define _OBJECT_H

#include <vector>
#include <memory>
#include "Sprite.h"
#include "PropertyList.h"

class Object : public IFallible
{
    private:

        PropertyList m_Properties;
        Sprite m_Sprite;

        void nullify() {
        }

    protected:

        // TODO: Property List Accessors

    public:

        Object(const std::string& fn);
        virtual ~Object();
};

#endif

