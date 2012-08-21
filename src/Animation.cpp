#ifndef _ANIMATION_H
#define _ANIMATION_H

#include <memory>
#include <functional>
#include <vector>
#include <cmath>
#include "Freq.h"
#include "math/common.h"
template<class T> class Animation;

struct LinearInterpolation
{
    template<class T>
    T operator()(const T& a, const T& b, float t) const {
        return a * (1.0f - t) + b * t;
    }
};

struct CosineInterpolation
{
    template<class T>
    T operator()(const T& a, const T& b, float t) const {
        float ft = (1.0f - cos(M_PI * t)) * 0.5f;
        return a + (b - a) * ft;
    }
};

struct SquareRootInterpolation
{
    template<class T>
    T operator()(const T& a, const T& b, float t) const {
        return a + (b - a) * std::sqrt(t);
    }
};

struct NoInterpolation
{
    template<class T>
    T operator()(const T& a, const T& b, float t) const {
        return a;
    }
};

// TODO requirements: should work with vectors and orthogonal matrices
template<class T>
class Waypoint
{
    private:
        
        // TODO: execution callback?
        // TODO: expiry callback?
        // TODO: interpolative callback?
        T m_Position;

        unsigned long m_ulStartTime; // transition start time
        unsigned long m_ulAlarmTime; // transition end time

        std::function<T (const T&, const T&, float)> m_Interpolation;

        Animation<T>* m_Animation;

    public:
        
        Waypoint(T position, Freq::Time time, Animation<T>* nav):
            m_Position(position),
            m_ulStartTime(0L),
            m_ulAlarmTime(0L),
            m_Animation(nav)
        {
            m_ulStartTime = Freq::get().getElapsedTime(); //ms
            m_ulAlarmTime = m_ulStartTime + time.get();
        }

        virtual ~Waypoint() {}
        
        virtual void poll() {
            // TODO: not necessary, but trigger callbacks if possible
        }

        virtual bool elapsed() {
            poll();
            return Freq::get().getElapsedTime() >= m_ulAlarmTime;
        }

        // may be negative
        long remaining() {
            return m_ulAlarmTime - Freq::get().getElapsedTime();
        }

        void setTimer(Freq::Time time) {
            
        }

        T& position() {
            return m_Position;
        }

        void interp(std::function<T (const T&, const T&, float)> func) {
            m_Interpolation = func;
        }
};

template<class T>
class Animation
{
    private:

        std::vector<Waypoint<T>> m_Waypoints;
        T m_default;
        float m_fSpeed;
        
    public:

        Animation(
            Waypoint<T> initial,
            T default_value=T(),
            Freq::Accumulator* accum = Freq::get().accumulator()
        ):
            m_default(default_value),
            m_fSpeed(1.0f)
        {
            m_Waypoints.push_back(std::move(initial));
        }

        virtual ~Animation() {}

        void addWaypoint(T position, Freq::Time time) {
            m_Waypoints.push_back(Waypoint<T>(std::move(position), time, this));
        }

        void clear(T position) {
            m_Waypoints.clear();
            m_Waypoints.push_back(Waypoint<T>(position, Freq::Time(0)));
        }

        T get() {
            for(auto itr = m_Waypoints.begin();
                itr != m_Waypoints.end();
                )
            {
                if(itr->elapsed())
                    itr = itr->erase();
                else
                    ++itr;
            }
            return m_Waypoints.front().position();
        }

        bool empty() {
            return m_Waypoints.size() <= 1;
        }

        void speed(float s) {
            m_fSpeed = s;
        }
        float speed() const {
            return m_fSpeed;
        }
};

#endif

