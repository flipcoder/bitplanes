#ifndef _IDEPTHSORTABLE_H
#define _IDEPTHSORTABLE_H

#include <memory>
#include "IRenderable.h"

class IDepthSortable:
    virtual public IRenderable,
    public std::enable_shared_from_this<IDepthSortable>
{
    private:
        float m_fDepth;
        void nullify() {
            m_fDepth = 0.0f;
        }
    public:

        IDepthSortable() {
            nullify();
        }
        virtual ~IDepthSortable() {}
        //virtual void enqueue() const {}
        virtual float depth() const {return m_fDepth;}
        void depth(float f) { m_fDepth = f; }
};

#endif

