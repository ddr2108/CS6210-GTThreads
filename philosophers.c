#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

//Global threading variables
gtthread_t t1,t2,t3,t4,t5;
gtthread_mutex_t stick1,stick2,stick3,stick4,stick5;


void philosopherTask(void *arg){
    gtthread_mutex_t* first, *second;
    int r; 
    
    //Figure out which chopsitcks they should pick up
    switch ((int)arg){
        case 1:
            second = &stick5;
            first = &stick1;
            break;
        case 2:
            first = &stick1;
            second = &stick2;
            break;
        case 3:
            first = &stick2;
            second = &stick3;
            break;
        case 4:
            first = &stick3;
            second = &stick4;
            break;      
        case 5:
            first = &stick4;
            second = &stick5;
            break;
    }

    //Do acquiring and releasing of chopsticks
    while(1){
        //Acquire
        printf("Philosopher %d Hungry\n", (int)arg);
        printf("Philosopher %d Acquiring First Chopstick\n", (int)arg);
        gtthread_mutex_lock(first);
        printf("Philosopher %d Acquiring Second Chopstick\n", (int)arg);
        gtthread_mutex_lock(second);        
        printf("Philosopher %d Eating\n", (int)arg);
        
        //Eat
        r=rand()%500000;
        while(r-->0);
        
        //Release
        printf("Philosopher %d Done Eating\n", (int)arg);
        printf("Philosopher %d Releasing Second Chopstick\n", (int)arg);
        gtthread_mutex_unlock(second);
        printf("Philosopher %d Acquiring First Chopstick\n", (int)arg);
        gtthread_mutex_unlock(first);        
        printf("Philosopher %d Thinking\n", (int)arg);

        //Think
        r=rand()%500000;
        while(r-->0);
    }
}


int main(){

    //Initialize threading
    gtthread_init(5);

    //Initialize mutex
    gtthread_mutex_init(&stick1);
    gtthread_mutex_init(&stick2);
    gtthread_mutex_init(&stick3);
    gtthread_mutex_init(&stick4);
    gtthread_mutex_init(&stick5);
    
    //Create threads
    gtthread_create(&t1, philosopherTask, (void*)1);
    gtthread_create(&t2, philosopherTask, (void*)2);
    gtthread_create(&t3, philosopherTask, (void*)3);
    gtthread_create(&t4, philosopherTask, (void*)4);
    gtthread_create(&t5, philosopherTask, (void*)5);

	while(1);

	return 0;
}

//make clean; rm test1; make; gcc -Wall -pedantic -I{...} -o philosophers philosophers.c gtthread.a;clear;  ./philosophers
