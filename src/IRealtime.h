#ifndef _IREALTIME_H
#define _IREALTIME_H

#include "IFallible.h"

class IRealtime
{
    public:
        virtual ~IRealtime() {}
        virtual void logic(float t) = 0;
};

#endif

