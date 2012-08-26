#ifndef _FREQ_H
#define _FREQ_H

#include <iostream>
#include "IStaticInstance.h"
#include "math/common.h"
#include "Util.h"
//#include "IRealtime.h"

class Freq : public IStaticInstance<Freq>/*,public IRealtime*/
{
public:

    class Accumulator/*: public IRealtime */{
        private:
            //unsigned long m_ulAccumulatedTime;
            unsigned long m_ulAccumulatedTime;
            //unsigned int m_uiLastAdvance;
            float m_fSpeed;
        public:
            Accumulator():
                m_ulAccumulatedTime(0L),
                m_fSpeed(1.0f)
            {}
            virtual ~Accumulator() {}
            virtual unsigned long milliseconds() const {
                return m_ulAccumulatedTime;
            }
            virtual float seconds() const {
                return m_ulAccumulatedTime / 1000.0f;
            }
            
            /*virtual */unsigned int logic(unsigned int a) { // milliseconds
                float advance = a * m_fSpeed;
                //m_uiLastAdvance = round_int(advance);
                m_ulAccumulatedTime += round_int(advance);
                return round_int(advance);
            }
            float logic(float a) { // seconds
                float advance = a * m_fSpeed;
                //m_uiLastAdvance = round_int(advance);
                m_ulAccumulatedTime += round_int(advance * 1000.0f);
                return advance;
            }
            //unsigned int advance() const { return m_uiLastAdvance; }

            void speed(float s) {
                m_fSpeed = s;
            }
            float speed() const {
                return m_fSpeed;
            }
            void pause() {
                m_fSpeed = 0.0f;
            }
            void resume(float speed = 1.0f) {
                m_fSpeed = speed;
            }
            void reset() {
                m_ulAccumulatedTime = 0L;
                m_fSpeed = 1.0f;
            }
    };

    // eventually migrate to chrono
    class Time
    {
    public:
        unsigned int value;
        Time():
            value(0) {}
        explicit Time(unsigned int ms) {
            value = ms;
        }
        Time(const Time& t) {
            value = t.getInternal();
        }
        unsigned int getInternal() const { return value; }
        static Time seconds(unsigned int s) { return Time(s * 1000);}
        static Time seconds(float s) { return Time((unsigned int)(s * 1000.0f)); }
        static Time minutes(unsigned int m) { return Time(m * 60000);}
        static Time minutes(float m) { return Time((unsigned int)(m * 60000.0f));}
        static Time milliseconds(int ms) { return Time(ms); }

        float seconds() const { return value / 1000.0f; }
        unsigned int milliseconds() const { return value; }
    };

    class Alarm
    {
    protected:
    
        //Freq* m_pTimer;
        Accumulator* m_pTimer;
        unsigned long m_ulAlarmTime;
        unsigned long m_ulStartTime;

        //todo:add alarm pausing?
    
    public:
    
        Alarm():
            m_ulAlarmTime(0L),
            m_ulStartTime(0L),
            m_pTimer(Freq::get().accumulator())
        {
            assert(m_pTimer);
        }

        explicit Alarm(Accumulator* timer):
            m_ulAlarmTime(0L),
            m_ulStartTime(0L),
            m_pTimer(timer)
        {
            assert(m_pTimer);
        }

        explicit Alarm(Time t, Accumulator* timer = NULL):
            m_pTimer(timer ? timer : Freq::get().accumulator())
        {
            assert(m_pTimer);
            set(t);
        }

        virtual ~Alarm() {}
        
        bool hasTimer() const { return (m_pTimer!=NULL); }
        
        void assignToTimer(Accumulator* timerRef)
        {
            assert(timerRef);
            m_pTimer = timerRef;
        }
        
        void set(Time t)
        {
            assert(m_pTimer);
            m_ulStartTime = m_pTimer->milliseconds();
            m_ulAlarmTime = m_ulStartTime + t.milliseconds();
        }

        void delay(Time t) {
            assert(m_pTimer);
            m_ulAlarmTime += ((unsigned long)t.milliseconds());
        }

        Freq::Time pause() {
            return Freq::Time(m_ulAlarmTime - m_ulStartTime);
        }

        void minutes(unsigned int m)
        {
           set(Time::minutes(m));
        }
        
        void seconds(unsigned int s)
        {
           set(Time::seconds(s));
        }

        void milliseconds(unsigned int ms)
        {
           set(Time(ms));
        }
        
        unsigned long milliseconds() const
        {
            assert(m_pTimer);
            if(!hasElapsed())
            {
                unsigned long t = (m_ulAlarmTime - m_pTimer->milliseconds());
                return t;
            }
            return 0L;
        }
        
        float seconds() const
        {
            assert(m_pTimer);
            float t = (m_ulAlarmTime - m_pTimer->milliseconds()) / 1000.0f;
            return t;
        }
        
        bool elapsed() const
        {
            assert(m_pTimer);
            return (m_pTimer->milliseconds() >= m_ulAlarmTime);
        }
        bool hasElapsed() const { return elapsed(); }
        
        float percentElapsed() const
        {
            return 1.0f - remaining();
        }

        float remaining() const
        {
            unsigned long remaining = milliseconds();
            unsigned long range = m_ulAlarmTime - m_ulStartTime;
            if(floatcmp(range, 0.0f))
                return 0.0f;
            return (float)remaining / (float)range;
        }

        //unsigned long endTickTime() { return m_ulAlarmTime; }
    };

    template<class T>
    class Timed : public Freq::Alarm
    {
    protected:
        Time m_Length;
        T m_Start;
        T m_End;
    public:
        Timed():
            Alarm()
        {
            m_Length = Time(0);
        }
        Timed(Time t, T start, T end) {
            m_Length = Time(t);
            set(t, start, end);
        }
        explicit Timed(Accumulator* timer) {
            m_Length = Time(0);
            assignToTimer(timer);
        }
        //Timed(const Timed<T>& t) {
        //    m_Start = t.start();
        //    m_End = t.end();
        //    m_Length = t.length();
        //}
        virtual ~Timed() {}
        T get() const{
            return m_Start + (m_End - m_Start) * percentElapsed();
        }
        T inverse() const {
            return m_End - (m_End - m_Start) * percentElapsed();
        }
        T start() const{
            return m_Start;
        }
        T end() const {
            return m_End;
        }
        T diff() const {
            return m_End - m_Start;
        }
        void restart(Time t) {
            static_cast<Alarm*>(this)->set(m_Length);
        }
        void set(Time t, T start, T end) {
            m_Start = start;
            m_End = end;
            m_Length = Time(t);
            static_cast<Alarm*>(this)->set(t);
        }
        void clear(T val) {
            m_Start = m_End = val;
            m_Length = Time(0);
            static_cast<Alarm*>(this)->set(Time(m_Length));
        }
        void shift(T val){
            //m_Start = m_End = (m_End + val);
            //m_Length = Time(0);
            //static_cast<Alarm*>(this)->set(Time(m_Length));

            m_Start += val;
            m_End += val;
        }
        void finish(){
            m_Start = m_End;
            static_cast<Alarm*>(this)->set(Time(0));
        }
        void reverse(){
            std::swap(m_Start, m_End);
            static_cast<Alarm*>(this)->set(m_Length);
        }
    };

private:

    Accumulator m_globalAccumulator;
    //unsigned long m_uiLastMark;
    unsigned long m_ulStartTime;
    unsigned int m_uiMinTick;
    
public:

    Freq():
        m_ulStartTime(getTicks()),
        m_uiMinTick(0L)
    {}
    
    unsigned long getTicks() const;
    
    // TODO: not yet implemented
    //void pause();
    //void unpause();
    
    //bool tick();

    // accumulates time passed, until enough has passed to advance forward
    // may advance more than 1 frame's worth of time
    // returns # of milliseconds to advance
    /* virtual */Freq::Time tick() {
        unsigned long ticks = getTicks() - m_ulStartTime;
        unsigned int advance = (unsigned int)(ticks - m_globalAccumulator.milliseconds());
        if(advance >= m_uiMinTick) {
            m_globalAccumulator.logic(advance);
            return Freq::Time::milliseconds(advance);
        }
        return Freq::Time::milliseconds(0);
    }

    Accumulator* accumulator() { return &m_globalAccumulator; }

    // varies from 0 to 1 based on interval between frames
    //float interp() const;
};

#endif

