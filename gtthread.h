#ifndef __GTTHREAD_H
#define __GTTHREAD_H

#include <stdlib.h>
#include "gtthread_mutex.h"
#include "gtthread_sched.h"

#define MEM 64000

//Thread id structure
typedef unsigned int gtthread_t;	

//////////////////////////////////
//gtthread_init()
//
//parameters: 
//      long period - the RR period
//returns: 
//      none
//
//Initialize threading library
//////////////////////////////////
void gtthread_init(long period);

//////////////////////////////////
//gtthread_create()
//
//parameters: 
//      gtthread_t *thread - thread id
//      void *(*start_routine)(void *) - routine
//      void *arg - arguments
//returns: 
//      int - id
//
//Initialize threading library
//////////////////////////////////
int  gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg);

//////////////////////////////////
//gtthread_join()
//
//parameters: 
//      gtthread_t thread - thread id
//		void **status - 
//returns: 
//      int - success
//
//Join thread with given id
//////////////////////////////////
int  gtthread_join(gtthread_t thread, void **status);

//////////////////////////////////
//gtthread_exit()
//
//parameters: 
//      void *retval - the return val
//returns: 
//      none
//
//Exit thread
//////////////////////////////////
void gtthread_exit(void *retval);

//////////////////////////////////
//gtthread_yield()
//
//parameters: 
//      none
//returns: 
//      none
//
//Change context to next thread
//////////////////////////////////
int gtthread_yield();

//////////////////////////////////
//gtthread_equal()
//
//parameters: 
//      gtthread_t t1 - first thread
//		gtthread_t t2 - second thread
//returns: 
//      none
//
//Change context to next thread
//////////////////////////////////
int  gtthread_equal(gtthread_t t1, gtthread_t t2);

//////////////////////////////////
//gtthread_execute()
//
//parameters: 
//      void *(*start_routine)(void *) - routine
//      void *arg - arguments
//returns: 
//      none
//
//Initialize threading library
//////////////////////////////////
void gtthread_execute(void *(*start_routine)(void *),void *arg);

//////////////////////////////////
//gtthread_cancel()
//
//parameters: 
//      gtthread_t thread
//returns: 
//      int - success
//
//Kill thread with given id
//////////////////////////////////
int  gtthread_cancel(gtthread_t thread);

//////////////////////////////////
//gtthread_self()
//
//parameters: 
//      none
//returns: 
//      gtthread_t - id of thread
//
//Change context to next thread
//////////////////////////////////
gtthread_t gtthread_self();

#endif // __GTTHREAD_H
