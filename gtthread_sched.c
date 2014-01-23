#include "gtthread_sched.h"

unsigned int addContext(ucontext_t newContext){
    //Create new node
    contextNode* newNode = (contextNode*) malloc(sizeof(contextNode));
	//Set parts
    newNode->node = newContext;				//Set context
	newNode->id = information.id++;			//Set id

    //Add node to linked list
    if (information.head==NULL){			//if it is the main thread
        information.head = newNode;			//Set the pointers
        information.tail = newNode;
		newNode->next = information.head;
		newNode->prev = information.tail;
		current = newNode;					//Set this thread to be currently running
		newNode->parent = -1;				//Mark as no parent
		initialContext();					//Start context
    }else{									//if it is a child thread
		information.tail->next = newNode;	//Fix pointers
		information.head->prev = newNode;
		newNode->next = information.head;
		newNode->prev = information.tail;
        information.tail = newNode;
		newNode->parent = current->id;      //Get parent id based on currently running thread  
    }

	return newNode->id;					//return the id
}

void removeContext(contextNode* toDelete){
	//Fix pointers
	toDelete->prev->next = toDelete->next;
	toDelete->next->prev = toDelete->prev;

	//Fix head if needed
	if (toDelete==information.head){
		cleanMemory();
		free(toDelete);
		exit(0);
	}

	//Change context if removing current context
	if (toDelete==current){
		current = current->next;
		free(toDelete);
		changeContext(DONE);
	}

	free(toDelete);	//Free allocated memory
}

int removeID(unsigned int id){
    //Pointers to thread
    contextNode* thread = findThread(id);

	//if thread found, remove
	if (thread!=NULL){
		removeContext(thread);
		return 0;
    }
	return 1;	//if none match, return 1
}

void initialContext(){
	//Set timer
	setTimer();

    //Set current context
    current = information.head;
}

void changeContext(int sig)
{
	contextNode* prev; 		//The node to switch into

    //Swap context
	if (sig==DONE){		//a thread just finished
		current = current;
		prev = &dead;	
	}else{
		prev = current;
    	current = current->next;
	}
    
	//Set timer
	setTimer();

	//Swap COntext
    swapcontext(&prev->node, &current->node);
}

int threadDead(unsigned int id, int parent){
    //Pointers to thread
    contextNode* thread = findThread(id);

	//if thread found, return 1
	if (thread!=NULL && thread->parent==parent){
		return 1;
    }

	return 0;	//if none match, return 0
}

contextNode* findThread(unsigned int id){
    //Pointers to nodes
    contextNode* thread = information.head;
    
    do{ //Search through all threads

		//Check for a match
        if (thread->id==id){
			return thread;
        }
		//Go to next thread
        thread = thread->next;

    }while(thread!=information.head && thread!=NULL);

	return NULL;	//if can't find any
}

void setTimer(){
    struct itimerval it;       		//Structure to hold time info
    struct sigaction act, oact;     //Structure for signal handler
    
    //Set signal handler
    act.sa_handler = changeContext;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGPROF, &act, &oact); 

    // Start itimer
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = information.RRPeriod;
    it.it_value.tv_sec = 0;
    it.it_value.tv_usec = information.RRPeriod;
    setitimer(ITIMER_PROF, &it, NULL);

}

int getID(){
	//Get id and return
	return current->id;
}

void setRet(void* retval){

	//Set the array
	killed[indexKilled].id = current->id;
	killed[indexKilled].parent = current->parent;
	killed[indexKilled].ret = retval;
	killed[indexKilled++].valid = 1;
}

void* getRet(unsigned int id){
	int i;	
	//Go through each entry
	for (i = 0; i<KILL_ARRAY; i++){
		//if ids match
		if(killed[i].id == id && killed[i].parent == current->id  && killed[i].valid == 1){
			killed[i].valid = 0;			
			return killed[indexKilled].ret;
		}
		
	}

	return NULL;
}

void cleanMemory(){
    contextNode* thread = information.head->next;
    
	//Remove data associated with each thread	
    while(thread!=information.head && thread!=NULL){
		removeID(thread->id);
	}
}
