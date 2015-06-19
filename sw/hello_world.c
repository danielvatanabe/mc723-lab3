#include <stdio.h>
#include <stdlib.h>

//typedef mutex int*;

//return 1 when gets the lock
int mutex_acquire(int *m) {

	int lock;
	int one;
	int *p = &one;	

	do{
		one = 1;
		//printf("before: lock=%d , one=%d, mutex=%d\n",lock,one,*m);
		asm (" \
		ll %0, %3 \n\
		sc %1, %2 \n\
		" \
		: "=r"(lock),"=r"(m) , "=m"(*p) \ 
		:  "m"(*m));  
		//: "=r"(one), "=m"(*m) \  //output operands
		//: "r"(lock) );   // inputs


		//printf("after: lock=%d , one=%d, mutex=%d\n\n",lock,one,*m);
		if (!lock && one) {
			//got lock
			return 1;
		} 
		//wait a little bit until ask for mutex again
		int i;
		for (i = 0; i < 100; ++i); 
	} while(1);
	
}

int mutex_release(int* m) {
	*m = 0;
}

int main(int argc, char *argv[]){
  int i;
  int m = 0;
  printf("Start!!\n");
  for(i=0;i<10;i++) {
  	mutex_acquire(&m);
    printf("Hi from processor MIPS!\n");

    mutex_release(&m);
  }

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

