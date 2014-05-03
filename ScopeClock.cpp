/* 
 * File:   ScopeClock.cpp
 * Author: filip
 * 
 * Created on May 3, 2014, 7:37 PM
 */

#include "ScopeClock.h"

ScopeClock::ScopeClock(int *storage) {
    m_storage = storage;
    m_start = clock();
}

ScopeClock::~ScopeClock() {
    *m_storage = clock() - m_start;
}

