#ifndef __GTTHREAD_MUTEX_H
#define __GTTHREAD_MUTEX_H

//Mutex
typedef struct{
    int volatile value;		//Value to store whether mutex in use
} gtthread_mutex_t;

//////////////////////////////////
//gtthread_mutex_init()
//
//parameters: 
//      gtthread_mutex_t *mutex - 
//             mutex to modify
//returns: 
//      int - success of creation
//
//Initializes a mutex
//////////////////////////////////
int  gtthread_mutex_init(gtthread_mutex_t *mutex);

//////////////////////////////////
//gtthread_mutex_lock()
//
//parameters: 
//      gtthread_mutex_t *mutex - 
//             mutex to modify
//returns: 
//      int - success of locking
//
//Locks a mutex
//////////////////////////////////
int  gtthread_mutex_lock(gtthread_mutex_t *mutex);

//////////////////////////////////
//gtthread_mutex_unlock()
//
//parameters: 
//      gtthread_mutex_t *mutex - 
//             mutex to modify
//returns: 
//      int - success of unlocking
//
//Unlocks a Mutex
//////////////////////////////////
int  gtthread_mutex_unlock(gtthread_mutex_t *mutex);

#endif // __GTTHREAD_MUTEX_H
