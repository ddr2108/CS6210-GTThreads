#ifndef __GTTHREAD_SCHED_H
#define __GTTHREAD_SCHED_H

#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <ucontext.h>

//Node
typedef struct _contextNode{
    ucontext_t node;
    int id;
    struct _contextNode* next;
    int parent;
} contextNode;

//Node Linked List
typedef struct _context{
    contextNode* head;
    contextNode* tail;
} context;

context information;    //Information about linked list
contextNode* current;    //Current context running



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
