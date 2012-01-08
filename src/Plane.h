#ifndef _PLANE_H
#define _PLANE_H

class Plane : public Object, public IRealtime
{
    public:
        Plane(const std::string& fn):Object(fn) {}
        virtual ~Plane();
};

#endif

