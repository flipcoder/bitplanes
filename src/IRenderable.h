#ifndef _IRENDERABLE_H
#define _IRENDERABLE_H

class IRenderable{
    public:
        virtual ~IRenderable() {};
        virtual void render() const {}
};

#endif
