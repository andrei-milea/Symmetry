#ifndef _TIMER_H
#define _TIMER_H


#ifdef WINDOWS

class HRTimer
{
public:
    HRTimer();
    
    LONGLONG GetFrequency();

    void StartTimer() ;

    LONGLONG StopTimer();

private:
    LARGE_INTEGER m_StartTime;
    LARGE_INTEGER m_StopTime;
    LONGLONG m_Frequency;

};

HRTimer::HRTimer()
: m_StartTime(),
m_StopTime(),
m_Frequency()
{
    m_Frequency = this->GetFrequency();
}

LONGLONG HRTimer::GetFrequency()
{
    LARGE_INTEGER proc_freq;

    if (!::QueryPerformanceFrequency(&proc_freq)) throw ;

    return proc_freq.QuadPart;
}

void HRTimer::StartTimer()
{
    DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    if(!::QueryPerformanceCounter(&m_StartTime))  throw;

    ::SetThreadAffinityMask(::GetCurrentThread(), oldmask);
}

LONGLONG HRTimer::StopTimer()
{
    DWORD_PTR oldmask = ::SetThreadAffinityMask(::GetCurrentThread(), THREAD_PRIORITY_TIME_CRITICAL);

    if(!::QueryPerformanceCounter(&m_StopTime))   throw;

    ::SetThreadAffinityMask(::GetCurrentThread(), oldmask);

    return (m_StopTime.QuadPart - m_StartTime.QuadPart)/m_Frequency;
}

#else   //unix-linux version

#include <time.h>

class HRTimer
{
public:
    HRTimer();

    double GetFrequency();

    void StartTimer() ;
    double StopTimer();

    double GetElapsedSec()const;
    double GetElapsedNanoS()const;


private:
    struct timespec m_StartTime,m_StopTime, m_Frequency;

};

HRTimer::HRTimer()
: m_StartTime(),
m_StopTime(),
m_Frequency()
{
   GetFrequency();
}

double HRTimer::GetFrequency()
{
    
    if(clock_getres(CLOCK_PROCESS_CPUTIME_ID, &m_Frequency)) throw;

    return m_Frequency.tv_nsec;
}

void HRTimer::StartTimer()
{
    if(clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_StartTime)) throw;
}

double HRTimer::StopTimer()
{
    if(clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &m_StopTime)) throw;

    return (m_StopTime.tv_sec - m_StartTime.tv_sec);
}

double HRTimer::GetElapsedNanoS()const
{

    return (m_StopTime.tv_nsec - m_StartTime.tv_nsec);
}

double HRTimer::GetElapsedSec()const
{

    return (m_StopTime.tv_sec - m_StartTime.tv_sec);
}


#endif

#endif
