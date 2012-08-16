#include "Freq.h"
#include <ctime>
#include <cstdio>
#include <allegro5/allegro5.h> // for al_get_time()

Freq :: Freq()
{
    m_ulStartTime = getTicks();
    m_dTimeBetweenTicks = 0.0;
    m_ulTicks = 0;
    m_iLogicTickSpeed = 0;
    m_bPaused = false;
}

unsigned long Freq :: getTicks() const
{
    //timeval time;
    //gettimeofday(&time, NULL);
    //long sec = time.tv_sec;
    //long usec = time.tv_usec;
    //return (sec*1000+usec/1000.0) + 0.5;
    return (unsigned long)(al_get_time() * 1000.0);
}

void Freq :: set(int logicTickSpeed = 60)
{
    if(logicTickSpeed<=0)
        return;
    
    m_iLogicTickSpeed = logicTickSpeed;
    m_dTimeBetweenTicks = 1000.00 / m_iLogicTickSpeed;
    m_ulTicks = 0L;
}

unsigned long Freq :: getElapsedTime() const
{
    return (getTicks() - m_ulStartTime);
}

double Freq :: getElapsedSeconds() const
{
    return (((double)getElapsedTime()) / 1000.00);
}

bool Freq :: tick()
{
    
    if ( getElapsedTime() / m_dTimeBetweenTicks > m_ulTicks )
    {
        ++m_ulTicks;
        return true;
    }
    
    return false;
}

float Freq :: interp() const
{
    float erp = (getElapsedTime() - ((m_ulTicks-1)*(float)m_dTimeBetweenTicks))/(float)m_dTimeBetweenTicks;
    
    if(erp<0.0000)
        return 0.0f;
    if(erp>1.0000)
        return 1.0f;
    return erp;
}

//void Freq :: pause()
//{
//    m_bPaused = true;
//}

//void Freq :: unpause()
//{
//    //m_ulTicks = (getElapsedTime() / m_dTimeBetweenTicks - 1) * 1.0;
//    m_bPaused = false;
//}

