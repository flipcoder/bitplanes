#ifndef _IDEPTH_H
#define _IDEPTH_H

#include <memory>
#include "IRenderable.h"

class IDepth : public IRenderable, public std::enable_shared_from_this<IDepth>
{
    public:

        virtual ~IDepth() {}
        virtual void enqueue() const {}
        virtual float depth() const {return 0.0f;}
};

#endif

