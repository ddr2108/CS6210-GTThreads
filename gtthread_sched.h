#ifndef __GTTHREAD_SCHED_H
#define __GTTHREAD_SCHED_H

#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <ucontext.h>

#define DONE 888

//Node
typedef struct _contextNode{
    ucontext_t node;
    int id;
    int parent;
    struct _contextNode* next;
} contextNode;

//Node Linked List
typedef struct _context{
    contextNode* head;
    contextNode* tail;
	struct _context *next;
} context;

context information;    //Information about linked list
contextNode* current;    //Current context running

contextNode* dead;


//////////////////////////////////
//addContext()
//
//parameters: 
//      ucontext_t newContext - 
//             new threads context
//returns: 
//      int - id
//
//Adds context to linked list
//////////////////////////////////
int addContext(ucontext_t newContext);

//////////////////////////////////
//removeContext()
//
//parameters: 
//      none
//returns: 
//      none
//
//Remove context from linked list
//////////////////////////////////
void removeContext();


//////////////////////////////////
//removeThread()
//
//parameters: 
//      int id - id of thread to kill
//returns: 
//      int - success
//
//Kill Thread with given id
//////////////////////////////////
int removeThread(int id);

//////////////////////////////////
//threadDead()
//
//parameters: 
//      int id - id of thread to kill
//		int parent - id of parent
//returns: 
//      int - 0 if dead
//
//Find if thread with is dead
//////////////////////////////////
int threadDead(int id, int parent);

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
//setRR()
//
//parameters: 
//      long period - time of RR
//returns: 
//      none
//
//Set period
//////////////////////////////////
void setRR(long period);

#endif // __GTTHREAD_SCHED_H
