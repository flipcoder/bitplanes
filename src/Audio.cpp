#include "Audio.h"

Audio::Sound :: Sound(const std::string& fn):
    IConfigurable(fn, "data/audio/")
{
    nullify();
    scoped_dtor<Sound> dtor(this);
    //m_spSample = sample;
    m_spSample = Audio::get().samples().cache(fn); // might throw
    if(!(m_pSound = al_create_sample_instance(m_spSample->sample())))
        throw Failure();
    al_attach_sample_instance_to_mixer(m_pSound, al_get_default_mixer());

    // disambiguate the overloaded positioned() accessor
    callbackOnMove(std::bind((void(Audio::Sound::*)(bool))&Audio::Sound::positioned, this, true));
    dtor.resolve();
}

