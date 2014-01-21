#ifndef __GTTHREAD_SCHED_H
#define __GTTHREAD_SCHED_H

#include <sys/time.h>
#include <signal.h>

//Node
typedef struct _contextNode{
    ucontext_t node;
    struct _contextNode* next;
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
//      none
//
//Adds context to linked list
//////////////////////////////////
void addContext(ucontext_t newContext){

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



#endif // __GTTHREAD_SCHED_H
