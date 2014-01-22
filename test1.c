#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

/* Tests creation.
   Should print "Hello World!" */

int *thr1(void *in) {
    //while(1){
	fprintf(stderr, "Hello\n");
    fflush(stdout);
	gtthread_cancel(1);
	//}	
    return 5;
}

void *thr2(void *in) {
    while(1){
		fprintf(stderr, "World\n");
    	fflush(stdout);
		//gtthread_yield();
	}	
	
    return NULL;
}

int main() {
    gtthread_t t1, t2;

    gtthread_init(50000L);
   	gtthread_create( &t2, thr2, NULL);
	fprintf(stderr, "Hello1\n");
    gtthread_create( &t1, thr1, NULL);
	fprintf(stderr, "Hello2\n");
    while(1){
		fprintf(stderr,"Duh\n");
		//gtthread_yield();
	}
    return EXIT_SUCCESS;
}

//make clean; rm test1; make; gcc -Wall -pedantic -I{...} -o test1 test1.c gtthread.a;clear;  ./test1 

