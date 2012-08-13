#ifndef _AUDIO_H
#define _AUDIO_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "IStaticInstance.h"
#include "Util.h"

class IAudible
{
    public:
        virtual ~IAudible() {}
};

class Audio : public IStaticInstance<Audio>
{
    private:
        
    public:
        Audio()
        {
            al_install_audio();
            al_init_acodec_addon();
        }
        ~Audio() {
            if(al_is_audio_installed())
                al_uninstall_audio();
        }
};

#endif

