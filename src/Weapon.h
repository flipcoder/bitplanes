#ifndef _WEAPON_H
#define _WEAPON_H

#include "IConfig.h"
#include "Freq.h"

class Weapon: public IConfig
{
    public:
        Weapon(const std::string& fn) {}
        virtual ~Weapon() {}
};

#endif

