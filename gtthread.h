#ifndef __GTTHREAD_H
#define __GTTHREAD_H

#include <stdlib.h>
#include "gtthread_sched.h"
#include "gtthread_mutex.h"

typedef struct
{
    uint32_t flags;
    void * stack_base;
    size_t stack_size;
    size_t guard_size;
    int32_t sched_policy;
    int32_t sched_priority;
} gtthread_attr_t;

typedef unsigned int gtthread_t;

int RRPeriod = 0;


/* Must be called before any of the below functions. Failure to do so may
 * result in undefined behavior. 'period' is the scheduling quantum (interval)
 * in microseconds (i.e., 1/1000000 sec.). */
void gtthread_init(long period);

/* see man pthread_create(3); the attr parameter is omitted, and this should
 * behave as if attr was NULL (i.e., default attributes) */
int  gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg);

/* see man pthread_join(3) */
int  gtthread_join(gtthread_t thread, void **status);

/* gtthread_detach() does not need to be implemented; all threads should be
 * joinable */

/* see man pthread_exit(3) */
void gtthread_exit(void *retval);

/* see man sched_yield(2) */
int gtthread_yield(void);

/* see man pthread_equal(3) */
int  gtthread_equal(gtthread_t t1, gtthread_t t2);

/* see man pthread_cancel(3); but deferred cancelation does not need to be
 * implemented; all threads are canceled immediately */
int  gtthread_cancel(gtthread_t thread);

/* see man pthread_self(3) */
gtthread_t gtthread_self(void);

#endif // __GTTHREAD_H
