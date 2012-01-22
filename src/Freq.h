#ifndef _FREQ_H
#define _FREQ_H

#include <iostream>
#include "IStaticInstance.h"
#include "math/common.h"

class Freq : public IStaticInstance<Freq>
{
public:

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
			value = t.get();
		}
		static Time seconds(unsigned int s) { return Time(s * 1000);}
		static Time seconds(float s) { return Time((unsigned int)(s * 1000.0f)); }
		static Time minutes(unsigned int m) { return Time(m * 60000);}
		static Time minutes(float m) { return Time((unsigned int)(m * 60000.0f));}
		static Time milleseconds(unsigned int ms) { return Time(ms); }

		unsigned int get() const { return value; }
		//unsigned int milleseconds() { return value; }
	};

	class Alarm
	{
	protected:
	
		Freq* m_pTimer;
		unsigned long m_ulAlarmTime;
		unsigned long m_ulStartTime;

		//todo:add alarm pausing?
	
	public:
	
		Alarm():
			m_ulAlarmTime(0L),
			m_ulStartTime(0L),
			m_pTimer(Freq::ptr())
		{
		}
		Alarm(Freq* timer):
			m_ulAlarmTime(0L),
			m_ulStartTime(0L),
			m_pTimer(timer)
		{
		}
		virtual ~Alarm() {}
		
		bool hasTimer() const { return (m_pTimer!=NULL); }
		
		void assignToTimer(Freq* timerRef)
		{
			m_pTimer = timerRef;
		}
		
		void set(Time t)
		{
			if(m_pTimer)
			{
				m_ulStartTime = m_pTimer->getElapsedTime();
				m_ulAlarmTime = m_ulStartTime+((unsigned long)t.get());
			}
		}

		void setMinutes(unsigned int m)
		{
		   set(Time::minutes(m));
		}
		
		void setSeconds(unsigned int s)
		{
		   set(Time::seconds(s));
		}

		void setMilleseconds(unsigned int ms)
		{
		   set(Time(ms));
		}
		
		unsigned long remainingTime() const
		{
			if(m_pTimer)
			{
				if(!hasElapsed())
				{
					unsigned long t = (m_ulAlarmTime - m_pTimer->getElapsedTime());
					return t;
				}
			}
			return 0L;
		}
		
		unsigned long remainingSeconds() const
		{
			if(m_pTimer)
			{
				unsigned long t = (m_ulAlarmTime - m_pTimer->getElapsedTime()) / 1000;
				return t;
			}
			return 0L;
		}
		
		bool hasElapsed() const
		{
			if(m_pTimer)
				if(m_pTimer->getElapsedTime() >= m_ulAlarmTime)
					return true;
			return false;
		}
		
		float percentElapsed() const
		{
			return 1.0f - percentRemaining();
		}

		float percentRemaining() const
		{
			unsigned long remaining = remainingTime();
			unsigned long range = m_ulAlarmTime - m_ulStartTime;
			if(floatcmp(range, 0.0f))
				return 0.0f;
			return (float)remaining / (float)range;
		}

		unsigned long endTickTime() { return m_ulAlarmTime; }
		
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
        Timed(const T& val) {
            clear(val);
        }
		Timed(Time t, T start, T end) {
			m_Length = Time(t);
			set(t, start, end);
		}
		explicit Timed(Freq* timer) {
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
			m_Start += val;
			m_End += val;
		}
		void finish(){
			m_Start = m_End;
			static_cast<Alarm*>(this)->set(Time(0));
		}
		void reverse(){
			swap(m_Start, m_End);
			static_cast<Alarm*>(this)->set(m_Length);
		}
	};

    unsigned long getTicks() const;

private:

	unsigned long m_ulStartTime;
	unsigned long m_ulTicks;
	
	double m_dTimeBetweenTicks;
	
	int m_iLogicTickSpeed;
	
	bool m_bPaused;
	
public:

	Freq();
	
	void set(int logicTickSpeed);
	
	unsigned long getElapsedTime() const;
	double getElapsedSeconds() const;
	
	unsigned long getElapsedTicks() const;

	// TODO: not yet implemented
	//void pause();
	//void unpause();
	
	bool tick();

	// varies from 0 to 1 based on interval between frames
	float interp() const;
};

#endif

