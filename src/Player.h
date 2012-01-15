#ifndef _PLAYER_H
#define _PLAYER_H

#include <string>
#include "Object.h"
#include "IControllable.h"
#include "Events.h"

class Player : public Object, public IControllable
{
    private:

        void nullify() {
        }

    public:
        Player(const std::string& fn):Object(fn) {
            nullify();
        }
        virtual ~Player() {}

        virtual bool logic(float t) {
            pos() = Events::get().mousePos() / System::get().scale();
            Object::logic(t);
            return true;
        }
        virtual void render() const {
            this->Object::render();
        }
};

#endif

