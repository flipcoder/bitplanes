#ifndef MUSIC_H
#define MUSIC_H

#include "Audio.h"
#include "IConfigurable.h"

class Music : public IConfigurable, public IAudible
{
    public:
        Music();
        virtual ~Music();
};

#endif

