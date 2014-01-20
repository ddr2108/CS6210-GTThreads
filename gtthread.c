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

tout_val.it_interval.tv_sec = 0;
tout_val.it_interval.tv_usec = 0;
tout_val.it_value.tv_sec = INTERVAL; /* set timer for "INTERVAL (10) seconds */
tout_val.it_value.tv_usec = 0;
setitimer(ITIMER_REAL, &tout_val,0);
signal(SIGALRM,schedule);

linked list of processes
signal -> set, make context
sched_yield -. call alarm to rescehdule

typedef struct{
    ucontext_t node;
    context* next;
} contextNode;

typedef struct{
    contextNode* head = NULL;
    contextNode* tail = NULL;
} context;

context information;
contextNode current;    //Current one to change

ucontext_t T1, T2,Main;
ucontext_t a;

void alarm()
{
    getcontext(&T2);
     T2.uc_link=0;
     T2.uc_stack.ss_sp=malloc(MEM);
     T2.uc_stack.ss_size=MEM;
     T2.uc_stack.ss_flags=0;
     makecontext(&T2, (void*)&fn2, 0);
     swapcontext(&Main, &T2);
    
     sigaction(SIGPROF, &act, &oact);
     // Start itimer
     it.it_interval.tv_sec = 4;
     it.it_interval.tv_usec = 50000;
     it.it_value.tv_sec = 1;
     it.it_value.tv_usec = 100000;
     setitimer(ITIMER_PROF, &it, NULL);

}

void addContext(ucontext_t* newContext){
    if (information.head==NULL){
        information.head = newContext;
        information.tail = newContext;
    }else{
        contextNode* newNode = malloc(sizeof(contextNode));
        information.tail->next =
    }
}

void removeContext(ucontext_t oldContext){
    contextNode* lead= information.head;
    contextNode* trail = NULL;

    while(lead!=NULL){
        if (lead->node==oldContext){
            if (tail!=NULL){
                tail->next = lead->next;
            }else{
                information.head = lead.next;
            }
            free(lead)
            break;
        }
        trail = lead;   //Set trail to previous head
    }
}

http://nitish712.blogspot.com/2012/10/thread-library-using-context-switching.html

/* gtthread_mutex_destroy() and gtthread_mutex_trylock() do not need to be
 * implemented */