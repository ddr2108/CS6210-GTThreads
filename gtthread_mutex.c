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
int  gtthread_mutex_init(gtthread_mutex_t *mutex){
    //Return if does not exist
    if (mutex == NULL)
        return 1;

    //Set value of mutex
    mutex->value = 0;

    return 0;
}

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
int  gtthread_mutex_lock(gtthread_mutex_t *mutex){
    //Attempt to change valu eof mutex to 1 when was 0 perviously
    if (__bionic_cmpxchg(0, 1, &mutex->value) != 0){      
        while (__bionic_swap(2, &mutex->value) != 0)
            __futex_wait_ex(&mutex->value, 0, 2, 0);
	 }
    }
    
    return 1;
}

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
int  gtthread_mutex_unlock(gtthread_mutex_t *mutex){
    //Change value of mutex to 0
    if (__bionic_atomic_dec(&mutex->value) != 1) {        
        mutex->value = 0;        // Just set to "0"
        __futex_wake_ex(&mutex->value, 0, 1);    // -> This ensures waking other threads.
    }
    
    return 1;
}
