#include "gtthread_mutex.h"

int  gtthread_mutex_init(gtthread_mutex_t *mutex){
    //Return if does not exist
    if (mutex == NULL)
        return 1;

    //Set value of mutex
    mutex->value = 0;

    return 0;
}

int  gtthread_mutex_lock(gtthread_mutex_t *mutex){
    //Attempt to change valu eof mutex to 1 when was 0 perviously
	while (__sync_lock_test_and_set(&mutex->value, 1)==1){
    	raise(SIGPROF);	//Change context
	}

    return 0;
}

int  gtthread_mutex_unlock(gtthread_mutex_t *mutex){
    //Change value of mutex to 0
	__sync_lock_release(&mutex->value);
    
    return 0;
}
