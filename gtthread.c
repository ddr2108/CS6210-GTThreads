int RRPeriod = 0;


/* Must be called before any of the below functions. Failure to do so may
 * result in undefined behavior. 'period' is the scheduling quantum (interval)
 * in microseconds (i.e., 1/1000000 sec.). */
void gtthread_init(long period){
	RRPeriod = period;	//Initilize time between round robin switching
}

/* see man pthread_create(3); the attr parameter is omitted, and this should
 * behave as if attr was NULL (i.e., default attributes) */
int  gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg){

	//Create stack
	void* stack;
	stack = malloc(attr->stack_size);
	
	//Clone to create new thread
	*thread = (gtthread_t) clone(start_routine, stack+attr->stack_size, CLONE_SIGHAND|CLONE_VM, arg); 

}

/* see man pthread_join(3) */
int  gtthread_join(gtthread_t thread, void **status){
	//Wait for thread to finish
	waitpid(thread, SIGCHLD, __WALL);

	//Kill Thread
	kill(thread, SIGUSR1);
	
    return 0;
}

/* gtthread_detach() does not need to be implemented; all threads should be
 * joinable */

/* see man pthread_exit(3) */
void gtthread_exit(void *retval){
	//Exit
	exit(0);
}

/* see man sched_yield(2) */
int gtthread_yield(void){
        return syscall0(LINUX_SYS_sched_yield);
}

/* see man pthread_equal(3) */
int  gtthread_equal(gtthread_t t1, gtthread_t t2){
	return t1==t2
}

/* see man pthread_cancel(3); but deferred cancelation does not need to be
 * implemented; all threads are canceled immediately */
int  gtthread_cancel(gtthread_t thread){
  result = pthread_kill (thread, 0);

  if (0 != result)
    {
      return result;
    }
cancel_self = pthread_equal (thread, self);
return 0;
}

/* see man pthread_self(3) */
gtthread_t gtthread_self(void);\{
      self = ptw32_new ();
      sp = (ptw32_thread_t *) self.p;
	  sp->threadH = GetCurrentThread ();

}


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

	return 1;

}
int  gtthread_mutex_unlock(gtthread_mutex_t *mutex){
	if (__bionic_atomic_dec(&mutex->value) != 1) {        

        mutex->value = 0;        // Just set to "0"

        __futex_wake_ex(&mutex->value, 0, 1);    // -> This ensures waking other threads.

    }

}

/* gtthread_mutex_destroy() and gtthread_mutex_trylock() do not need to be
 * implemented */