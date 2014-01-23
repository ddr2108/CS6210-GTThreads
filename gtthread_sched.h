#ifndef __GTTHREAD_SCHED_H
#define __GTTHREAD_SCHED_H

#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <ucontext.h>



/////////////////STRUCTURES/////////////////////////////////////////////
//Node
typedef struct _contextNode{
    ucontext_t node;				//Context
    unsigned int id;				//ID
    unsigned int parent;			//ID of parent
    struct _contextNode* next;		//Pointers to other nodes
    struct _contextNode* prev;
} contextNode;

//Node Linked List
typedef struct _context{
	long RRPeriod;		//Period associated with Round robin				
	unsigned int id;			//ID of next thread 
    contextNode* head;	//pointers to context nodes
    contextNode* tail;
} context;

//////////GLOBAL VARIABLES/////////////////////////////////////////////
#define DONE 888

context information;    //Information about linked list
contextNode* current;    //Current context running

contextNode* dead;

///////////////////FUNCTION PROTOTYPES///////////////////////////////////

//////////////////////////////////
//addContext()
//
//parameters: 
//      ucontext_t newContext - 
//             new threads context
//returns: 
//      unsigned int - id
//
//Adds context to linked list
//////////////////////////////////
unsigned int addContext(ucontext_t newContext);

//////////////////////////////////
//removeContext()
//
//parameters: 
//      currentNode* toDelete - node
//					to delete
//returns: 
//      none
//
//Remove context from linked list
//////////////////////////////////
void removeContext(contextNode* toDelete);

//////////////////////////////////
//removeID()
//
//parameters: 
//      unsigned int id - id of thread to kill
//returns: 
//      int - success
//
//Kill Thread with given id
//////////////////////////////////
int removeID(unsigned int id);

//////////////////////////////////
//initialContext()
//
//parameters: 
//      none
//returns: 
//      none
//
//Set initial context
//////////////////////////////////
void initialContext();

//////////////////////////////////
//changeContext()
//
//parameters: 
//      int sig - type of signal
//returns: 
//      none
//
//Set alarm, switch context based 
//on next in linked list
//////////////////////////////////
void changeContext(int sig);

//////////////////////////////////
//threadDead()
//
//parameters: 
//      unsigned int id - id of thread to kill
//		int parent - id of parent
//returns: 
//      int - 0 if dead
//
//Find if thread with is dead
//////////////////////////////////
int threadDead(unsigned int id, int parent);

//////////////////////////////////
//findThread()
//
//parameters: 
//      unsigned int id - id of thread to find
//returns: 
//      contextNode* - pointer to node
//
//Adds context to linked list
//////////////////////////////////
contextNode* findThread(unsigned int id);

//////////////////////////////////
//setTimer()
//
//parameters: 
//      none
//returns: 
//      none
//
//Set timer
//////////////////////////////////
void setTimer();

//////////////////////////////////
//getID()
//
//parameters: 
//      none
//returns: 
//      int - id of currently running
//
//Return id of self
//////////////////////////////////
int getID();

//////////////////////////////////
//cleanMemory()
//
//parameters: 
//      none
//returns: 
//      none
//
//Clean all memory
//////////////////////////////////
void cleanMemory();

#endif // __GTTHREAD_SCHED_H
