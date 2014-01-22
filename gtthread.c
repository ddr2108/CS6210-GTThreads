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
	setRR(period);		//Initilize time between round robin switching
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
	//Wait for thread to finish
//rc = waitone(thread, INFINITE);
    return 0;

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

	//FIX: Make it return value
}

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
int gtthread_yield(){
	changeContext(1);	//Change context
        
	return 1;
}

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

	return removeThread(thread);
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
