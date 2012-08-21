#ifndef _BACKDROP_H
#define _BACKDROP_H
#include "Object.h"
#include "IScriptable.h"

class Backdrop :
    public Object,
    public IScriptable
{
    private:
        //Vector2 m_vVel;

        void nullify() {
            sprite().flags().set(Sprite::F_TILE);
            sprite().depth(100.0f);
        }

    public:
        Backdrop(const std::string& fn): Object(fn) {
            nullify();
        }
        virtual ~Backdrop() {}
        virtual bool logic(float t) {
            move(-world()->vel() * t);
            Object::logic(t);
            return true;
        }
        virtual void render() const {
            Object::render();
        }
        //Vector2& vel() {return m_vVel;}
        //const Vector2& vel() const {return m_vVel;}
};

#endif

