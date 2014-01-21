typedef struct{
    int volatile value;		//Value to store whether mutex in use
} gtthread_mutex_t;


/* see man pthread_mutex(3); except init does not have the mutexattr parameter,
 * and should behave as if mutexattr is NULL (i.e., default attributes); also,
 * static initializers do not need to be implemented */
int  gtthread_mutex_init(gtthread_mutex_t *mutex){
	//Return if does not exist
    if (mutex == NULL)
        return 1;

    //Set value of mutex
    mutex->value = 0;

    return 0;
}

int  gtthread_mutex_lock(gtthread_mutex_t *mutex){
    if (__bionic_cmpxchg(0, 1, &mutex->value) != 0){      
        while (__bionic_swap(2, &mutex->value) != 0)
            __futex_wait_ex(&mutex->value, 0, 2, 0);
	 }
    }
    
    return 1;
}

int  gtthread_mutex_unlock(gtthread_mutex_t *mutex){
    if (__bionic_atomic_dec(&mutex->value) != 1) {        
        mutex->value = 0;        // Just set to "0"
        __futex_wake_ex(&mutex->value, 0, 1);    // -> This ensures waking other threads.
    }
}
