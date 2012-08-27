#ifndef _AUDIO_H
#define _AUDIO_H

#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <boost/filesystem.hpp>
#include <memory>
#include <vector>
#include "IStaticInstance.h"
#include "Util.h"
#include "IFallible.h"
#include "IConfigurable.h"
#include "ResourceCache.h"
#include "IMovable.h"

// Basic stereo positional audio system (no rotation, falloff, etc.)
class Audio:
    public IRealtime,
    public IStaticInstance<Audio>
{
    public:

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
                    al_attach_audio_stream_to_mixer(m_pStream, al_get_default_mixer());
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
                Sound(const std::string& fn);
                
                ~Sound() {
                    if(m_pSound)
                        al_destroy_sample_instance(m_pSound);
                }
                enum Play {
                    REPEAT = BIT(0),
                    CONTINUE = BIT(1)
                };
                void play(unsigned int flags = 0) {
                    if(!(flags & CONTINUE))
                        al_set_sample_instance_position(m_pSound, 0);
                    al_set_sample_instance_playmode(m_pSound, flags & REPEAT ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE);
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
                ALLEGRO_SAMPLE_INSTANCE* allegro() {
                    return m_pSound;
                }

                bool positioned() const { return m_bPosition; }
                
                void positioned(bool b){
                    m_bPosition = b;
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
            private:
                float m_fScale;
            public:
                Listener():
                    m_fScale(2.0f)
                {
                }
                virtual ~Listener() {}

                virtual void logic(float t) {
                }
                float scale() const { return m_fScale; }
                void scale(float f) { m_fScale = f; }
        };


    private:
        
        ResourceCache<Sample> m_Samples;
        std::vector<std::weak_ptr<Sound>> m_Sounds;
        std::shared_ptr<Listener> m_Listener;

    public:
        Audio()
        {
            scoped_dtor<Audio> dtor(this);
            if(!al_install_audio())
                throw Failure();
            if(!al_init_acodec_addon())
                throw Failure();
            al_reserve_samples(32);
            samples().addPath("data/audio/");
            dtor.resolve();
            m_Listener.reset(new Listener());
        }
        ~Audio() {
            m_Samples.clear();
            m_Sounds.clear();
            if(al_is_audio_installed())
                al_uninstall_audio();
        }

        virtual void logic(float t) {
            // transform listener into panspace
            float listener_pan = m_Listener->center().x / (m_Listener->scale()/2.0f) - 1.0f;
            for(auto itr = m_Sounds.begin();
                itr != m_Sounds.end(); )
            {
                std::shared_ptr<Sound> snd;
                if(!(snd = itr->lock())) {
                    itr = m_Sounds.erase(itr);
                    continue;
                }
                if(!snd->positioned()) {
                    itr = m_Sounds.erase(itr);
                    continue;
                }
                float snd_pan = snd->center().x / (m_Listener->scale()/2.0f) - 1.0f;
                al_set_sample_instance_pan(snd->allegro(), snd_pan - listener_pan);

                ++itr;
            }
        }

        ResourceCache<Sample>& samples() { return m_Samples; }
        Listener* listener() { return m_Listener.get(); }

        void listen(std::shared_ptr<Sound>& snd) {
            float listener_pan = m_Listener->center().x / (m_Listener->scale()/2.0f) - 1.0f;
            float snd_pan = snd->center().x / (m_Listener->scale()/2.0f) - 1.0f;
            al_set_sample_instance_pan(snd->allegro(), snd_pan - listener_pan);
            m_Sounds.push_back(std::weak_ptr<Sound>(snd));
        }
};

#endif

