#ifndef _AUDIO_H
#define _AUDIO_H

#include "Audio.h"
#include "IConfigurable.h"

class Sound : public IConfigurable, public IAudible
{
    public:
        Sound(const std::string& fn);
        ~Sound();
};

#endif

