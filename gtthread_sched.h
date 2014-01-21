#ifndef __GTTHREAD_SCHED_H
#define __GTTHREAD_SCHED_H

//Node
typedef struct{
    ucontext_t node;
    contextNode* next;
} contextNode;

//Node Linked List
typedef struct{
    contextNode* head = NULL;
    contextNode* tail = NULL;
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
