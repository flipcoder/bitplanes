#ifndef _AUDIO_H
#define _AUDIO_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <memory>
#include <vector>
#include "IStaticInstance.h"
#include "Util.h"
#include "IFallible.h"
#include "IConfigurable.h"
#include "ResourceCache.h"
#include "IMovable.h"

// Basic 2D positional audio system (no rotational, scaling, etc.)

class Audio:
    public IRealtime,
    public IStaticInstance<Audio>
{
    private:

        // Samples are all cached internally, no visibility needed
        class Sample
        {
            private:
                ALLEGRO_SAMPLE* m_pSample;
                void nullify() {
                    m_pSample = nullptr;
                }
            public:
                Sample(const std::string& fn) {
                    nullify();
                    if(!(m_pSample = al_load_sample(fn.c_str())))
                        throw Failure();
                }
                ~Sample() {
                    if(m_pSample)
                        al_destroy_sample(m_pSample);
                }
                ALLEGRO_SAMPLE* sample() { return m_pSample; }
        };

    public:
        
        class Stream : public IConfigurable
        {
            private:
                ALLEGRO_AUDIO_STREAM* m_pStream;
                void nullify() {
                    m_pStream = nullptr;
                }
            public:
                Stream(const std::string& fn):
                    IConfigurable(fn, "data/audio/")
                {
                    nullify();
                    scoped_dtor<Stream> dtor(this);
                    if(!(m_pStream = al_load_audio_stream(fn.c_str(), 2, 1024 * 4)))
                        throw Failure();
                    dtor.resolve();
                }
                enum Play {
                    REPEAT = BIT(0),
                    CONTINUE = BIT(1)
                };
                void play(unsigned int flags = 0) {
                    al_set_audio_stream_playmode(m_pStream, (flags & REPEAT ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE));
                    //al_attach_audio_stream_to_mixer(m_pStream, al_get_default_mixer());
                    if(!(flags & CONTINUE))
                        stop();
                    al_set_audio_stream_playing(m_pStream, true);
                }
                void stop() {
                    al_set_audio_stream_playing(m_pStream, false);
                    al_rewind_audio_stream(m_pStream);
                }
                void pause() {
                    al_set_audio_stream_playing(m_pStream, false);
                }
                void resume() {
                    al_set_audio_stream_playing(m_pStream, true);
                }
                float pan() const {
                    return al_get_audio_stream_pan(m_pStream);
                }
                void pan(float val) {
                    al_set_audio_stream_pan(m_pStream, val);
                }
                ~Stream() {
                    if(m_pStream)
                        al_destroy_audio_stream(m_pStream);
                }
        };
        
        class Sound :
            public IConfigurable,
            virtual public IMovable
        {
            private:
                std::shared_ptr<Sample> m_spSample; // should be stored in cache
                ALLEGRO_SAMPLE_INSTANCE* m_pSound;
                void nullify() {
                    m_pSound = nullptr;
                    m_bPosition = false;
                }
                bool m_bPosition;
            public:
                Sound(const std::string& fn):
                    IConfigurable(fn, "data/audio/")
                {
                    nullify();
                    m_spSample = Audio::get().samples().cache(fn); // might throw
                    if(!(m_pSound = al_create_sample_instance(m_spSample->sample())))
                        throw Failure();
                    // add scoped_dtor<> if you add any code below here
                }
                ~Sound() {
                    if(m_pSound)
                        al_destroy_sample_instance(m_pSound);
                }
                enum Play {
                    P_REPEAT = BIT(0),
                    P_CONTINUE = BIT(1)
                };
                void play(unsigned int flags = 0) {
                    if(!(flags & P_CONTINUE))
                        al_set_sample_instance_position(m_pSound, 0);
                    al_set_sample_instance_playmode(m_pSound, flags & P_REPEAT ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE);
                    al_play_sample_instance(m_pSound);
                }
                void stop() {
                    al_set_sample_instance_playing(m_pSound, false);
                    al_set_sample_instance_position(m_pSound, 0); // rewind to start
                }
                void resume() {
                    al_set_sample_instance_playing(m_pSound, true);
                    
                }
                void pause() {
                    al_set_sample_instance_playing(m_pSound, false);
                }
                void ambient() {
                    pos(Vector2());
                    m_bPosition = false;
                }
                //float pan() const {
                //    return al_get_sample_instance_pan(m_pSound);
                //}
                //void pan(float val) {
                //    al_set_sample_instance_pan(m_pSound, val);
                //}
        };

        class Listener:
            public IRealtime,
            virtual public IMovable
        {
            public:
                Listener() {}
                virtual ~Listener() {}

                virtual void logic(float t) {
                }
        };


    private:
        
        ResourceCache<Sample> m_Samples;
        std::vector<std::shared_ptr<Listener>> m_Listeners;

    public:

        Audio()
        {
            al_install_audio();
            al_init_acodec_addon();
            al_reserve_samples(16);
            samples().addPath("data/audio/");
        }
        ~Audio() {
            if(al_is_audio_installed())
                al_uninstall_audio();
        }

        virtual void logic(float t) {
            // TODO: update all listeners
        }

        ResourceCache<Sample>& samples() { return m_Samples; }
};

#endif

