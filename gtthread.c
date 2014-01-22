#include "gtthread.h"
#include <stdio.h>
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
void gtthread_init(long period){
	ucontext_t newContext;	//hold context

	setRR(period);		//Initilize time between round robin switching
	
	dead = (contextNode*) malloc(sizeof(contextNode));	//set up some variables
	
	//add Context
	 addContext(newContext);
}

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
void gtthread_execute(void *(*start_routine)(void *),void *arg){
	void *retval=start_routine(arg);
	gtthread_exit(retval);
}

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
	return addContext(newContext);
}

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
int  gtthread_join(gtthread_t thread, void **status){
	//check if thread is dead	
	while(threadDead(thread, gtthread_self())==1){
		gtthread_yield();	//yield to next thread
	}
    return 0;   //success

	//FIX: status
}


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
void gtthread_exit(void *retval){
    removeContext();	//Remove context from linked list
}

//////////////////////////////////
//gtthread_yield()
//
//parameters: 
//      none
//returns: 
//      int - success
//
//Change context to next thread
//////////////////////////////////
int gtthread_yield(){
	changeContext(1);	//Change context
        
	return 0;       //no error
}

//////////////////////////////////
//gtthread_equal()
//
//parameters: 
//      gtthread_t t1 - first thread
//	gtthread_t t2 - second thread
//returns: 
//      int - whether equal
//
//Change context to next thread
//////////////////////////////////
int  gtthread_equal(gtthread_t t1, gtthread_t t2){
	return t1==t2;	//return if they are equal to each other
}

//////////////////////////////////
//gtthread_cancel()
//
//parameters: 
//      gtthread_t thread - thread id
//returns: 
//      int - success
//
//Kill thread with given id
//////////////////////////////////
int  gtthread_cancel(gtthread_t thread){
	//Check if trying to cancel itself and call correct function	
	if (thread==getID()){
		removeContext();
		return 0;	
	}else{
		return removeThread(thread);
	}
}

//////////////////////////////////
//gtthread_self()
//
//parameters: 
//      none
//returns: 
//      gtthread_t - id of thread
//
//Get ID of current thread
//////////////////////////////////
gtthread_t gtthread_self(){
 	//Return id of thread
    return getID();

}
