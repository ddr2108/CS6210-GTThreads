#include "gtthread.h"

void gtthread_init(long period){
	int i;	
	ucontext_t newContext;	//hold context

	//INitialize threads
	for (i=0;i<MAX_THREADS;i++){
		nodeArray[i].valid = 0;
	}

	information.id = 0;					//Initialize strucutre
	information.head = NULL;
	information.tail = NULL;
	information.RRPeriod = period;		//set period	

	//add Context
	addContext(newContext);
}

void gtthread_execute(void *(*start_routine)(void *),void *arg){
	void *retval=start_routine(arg);
	gtthread_exit(retval);
}


int  gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg){
	
	ucontext_t newContext;	//hold context
	
	//Create Context
	getcontext(&newContext);
	newContext.uc_link=0;
	newContext.uc_stack.ss_sp=malloc(MEM);
	newContext.uc_stack.ss_size=MEM;
	newContext.uc_stack.ss_flags=0;
	makecontext(&newContext, gtthread_execute,2,start_routine,arg);

	//add Context
	*thread=addContext(newContext);

	return 0;
}

int  gtthread_join(gtthread_t thread, void **status){
	int i;	

	//check if thread is dead	
	while(threadDead(thread, gtthread_self())==1){
		gtthread_yield();	//yield to next thread if not
	}

	//Go through each entry
    for (i=0;i<MAX_THREADS;i++){
        if (nodeArray[i].valid == 2 && nodeArray[i].newNode.id == thread && nodeArray[i].newNode.parent == current->id){
            nodeArray[i].valid = 0;     //Set valid
			if (status != NULL){
				*status = nodeArray[i].ret;
			}
			return 0;
        }
    }

    return 1;
}

void gtthread_exit(void *retval){
	setRet(retval);			//Set the return value
    removeContext(current);	//Remove context from linked list
}

int gtthread_yield(){
	changeContext(1);	//Change context
	return 0;       //no error
}

int  gtthread_equal(gtthread_t t1, gtthread_t t2){
	return t1==t2;	//return if they are equal to each other
}

int  gtthread_cancel(gtthread_t thread){
	//Check if trying to cancel itself and call correct function	
	if (thread==getID()){
		removeContext(current);
		return 0;	
	}else{
		return removeID(thread);
	}
}

gtthread_t gtthread_self(){
 	//Return id of thread
    return getID();

}
