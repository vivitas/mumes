#pragma once
#include <time.h>
class ScopeTimer
{
    public:
    ScopeTimer(int *result);
    virtual ~ScopeTimer();
    private:
    int *m_result;
    clock_t m_start_time;
};

