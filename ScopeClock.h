/* 
 * File:   ScopeClock.h
 * Author: filip
 *
 * Created on May 3, 2014, 7:37 PM
 */

#ifndef SCOPECLOCK_H
#define	SCOPECLOCK_H

#include <time.h>

class ScopeClock {
public:
    ScopeClock(int* storage);
    virtual ~ScopeClock();
private:
    int* m_storage;
    clock_t m_start;
};

#endif	/* SCOPECLOCK_H */

