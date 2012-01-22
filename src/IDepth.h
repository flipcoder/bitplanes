#ifndef _IDEPTH_H
#define _IDEPTH_H

#include <memory>
#include "IRenderable.h"

class IDepth : public IRenderable, public std::enable_shared_from_this<IDepth>
{
    private:
        float m_fDepth;
        void nullify() {
            m_fDepth = 0.0f;
        }
    public:

        IDepth() {
            nullify();
        }
        virtual ~IDepth() {}
        //virtual void enqueue() const {}
        virtual float depth() const {return m_fDepth;}
        void depth(float f) { m_fDepth = f; }
};

#endif

