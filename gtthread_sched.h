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
#define KILL_ARRAY 2000
#define MAX_THREADS 3000

context information;    //Information about linked list
contextNode* current;    //Current context running

// Array for easier allocation
struct _allocContext{
    contextNode newNode;
	int valid;
	void* ret;			//return value				
} nodeArray[MAX_THREADS];

contextNode dead;


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
//      void* retval - return Value
//returns: 
//      none
//
//Sets return value
//////////////////////////////////
void setRet(void* retval);

//////////////////////////////////
//cleanMemory()
//
//parameters: 
//      unsigned int id - id of thread
//returns: 
//      void* - return value
//
//Gets return Value
//////////////////////////////////
void* getRet(unsigned int id);

//////////////////////////////////
//getNode()
//
//parameters: 
//      none
//returns: 
//      contextNode* - new node
//
//Gets return Value
//////////////////////////////////
contextNode* getNode();

//////////////////////////////////
//removeNode()
//
//parameters: 
//      contextNode* toDelete - node delete
//returns: 
//      none
//
//Gets return Value
//////////////////////////////////
void removeNode(contextNode* toDelete);

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
