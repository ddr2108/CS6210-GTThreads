#include <stdio.h>
#include <stdlib.h>
#include "gtthread.h"

/* Tests creation.
   Should print "Hello World!" */
int thr2(void *in) {
int i;
int j = 0;
//int *k = (int*) in;
    for(i = 0; i<5; i++){
	fprintf(stderr, "World\n");
    //fflush(stdout);
	//gtthread_cancel(1);
	}	
	
    return 125;
}

int thr1(void *in) {
int i;
int j = 0;
int k = 5;
int *a; 
    gtthread_t t1, t2;
   	gtthread_create( &t2, thr2, 5);    
for(i = 0; i<3; i++){
	fprintf(stderr, "Hello\n");
    //fflush(stdout);
	//gtthread_cancel(1);
	}	


    return 5;
}



int main() {
    gtthread_t t1, t2;
int *a; 
int *b;
int c;
    gtthread_init(50000L);
   	gtthread_create( &t1, thr1, NULL);
   	gtthread_create( &t2, thr2, 5);    
c=gtthread_join(1, &a);

c=gtthread_join(2, &b);

				//a = (int*) killed[0].ret;
				printf("a:%d", a);
				printf("b:%d", b);
		//gtthread_yield();

    return EXIT_SUCCESS;
}

//make clean; rm test1; make; gcc -Wall -pedantic -I{...} -o test1 test1.c gtthread.a;clear;  ./test1 

