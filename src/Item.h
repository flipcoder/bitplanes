#ifndef _ITEM_H
#define _ITEM_H

#include "Object.h"
#include "IScriptable.h"

class Item:
    public Object,
    public IScriptable
{
    private:

    public:

        void nullify() {
        }

        Item(const std::string& fn):
            Object(fn)
        {
            // check config for event scripts
        }
        ~Item() {}

        virtual void logic(float t) {}
        virtual void render() const {
            Object::render();
        }
        const char* type() const { return "item"; }
        virtual void collisionEvent(std::shared_ptr<Object>& obj) {
            // if collision with player, execute item event script on player
        }
};

#endif

