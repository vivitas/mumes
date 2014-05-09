#include "ScopeTimer.h"


ScopeTimer::ScopeTimer(int *result)
{
    *m_result = *result;
    m_start_time = clock();
}


ScopeTimer::~ScopeTimer()
{
    *m_result = clock() - m_start_time;
}
