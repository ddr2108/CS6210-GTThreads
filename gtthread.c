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
    unsigned stack_size = 0;

    arch_thread_info *pv = calloc(1, sizeof(arch_thread_info));

    _beginthreadex(NULL, stack_size, worker_proxy, pv, CREATE_SUSPENDED, NULL);
    ResumeThread(pv->handle);
    *thread = (pthread_t) pv;
    return 0;

}

/* see man pthread_join(3) */
int  gtthread_join(gtthread_t thread, void **status){
	//Wait for thread to finish
rc = waitone(thread, INFINITE);
    return 0;
}

/* gtthread_detach() does not need to be implemented; all threads should be
 * joinable */

/* see man pthread_exit(3) */
void gtthread_exit(void *retval){
    if (pv != NULL) {
    } else {
        exit(1); /* User should not call pthread_exit in the main thread */
    }
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
    return self();

}