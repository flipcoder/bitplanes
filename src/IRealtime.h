#ifndef _IREALTIME_H
#define _IREALTIME_H

#include "IFallible.h"

class IRealtime : public IFallible
{
    public:
        virtual ~IRealtime() {}
        virtual bool logic(unsigned int advance) {return false;}
        virtual void render() const {}
};

#endif

