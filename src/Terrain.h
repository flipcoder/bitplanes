#ifndef _TERRAIN_H
#define _TERRAIN_H

class Terrain : public Object
{
    private:
        Vector2 m_vVel;

        void nullify() {
            m_vVel = Vector2(0.0f, 50.0f);
            
        }
    public:
        Terrain(const std::string& fn): Object(fn) {
            nullify();
        }
        virtual ~Terrain() {}
        virtual bool logic(float t) {
            pos() += (m_vVel * t);
            Object::logic(t);
            return true;
        }
        virtual void render() const {
            Object::render();
        }
        Vector2& vel() {return m_vVel;}
        const Vector2& vel() const {return m_vVel;}

        virtual float depth() const {return -10.0f;}
};

#endif

