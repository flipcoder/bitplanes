#ifndef _PLANE_H
#define _PLANE_H

#include <string>
#include "Object.h"

class Plane : public Object
{
    public:
        Plane(const std::string& fn):Object(fn) {
        }
        virtual ~Plane() {}

        virtual bool logic(float t) {}
        virtual void render() const {
        }
};

#endif

