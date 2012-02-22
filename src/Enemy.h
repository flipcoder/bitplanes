#ifndef _ENEMY_H
#define _ENEMY_H

#include <memory>
#include "math/vector2.h"
#include "Object.h"
#include "Freq.h"
#include <boost/optional/optional.hpp>

class Enemy : public Object
{
    private:
        Vector2 m_vVel;
        void nullify() {}

    public:
        Enemy(const std::string& fn):
            Object(fn)
        {
            nullify();
            sprite().depth(-50.0f);
        }
        virtual ~Enemy() {}

        virtual bool logic(float t) {
            pos() += (m_vVel - world()->vel()) * t;
            Object::logic(t);
            //if(world()->outsideScreen(shared_from_this())) {
            if(pos().x < -size().x/2.0f) {
                m_vVel.x = std::fabs(m_vVel.x);
                pos().x = -size().x/2.0f;
            }else if (pos().x > System::get().w()-size().x/2.0f) {
                m_vVel.x = -std::fabs(m_vVel.x);
                pos().x = System::get().w()-size().x/2.0f;
            }
            if(pos().y < 0.0f && m_vVel.y < 0.0f)
                invalidate();
            if(pos().y > System::get().h())
                invalidate();

            return true;
        }
        virtual void render() const {
            Object::render();
        }

        // temp velocity methods
        void vel(Vector2 v) { m_vVel = v; }
        const Vector2& vel() const { return m_vVel; }

        virtual bool collidable() { return true; }
};

#endif


