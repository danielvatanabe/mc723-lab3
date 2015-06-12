#include <stdio.h>
#include <stdlib.h>

//typedef mutex int*;

//return 1 when gets the lock
int mutex_acquire(int *m) {

	int lock;
	int temp;

	while (*m != 0) {
		temp = 0;
				 														//%0 ouput    %1 input
		asm volatile ("ll %0, 0(%1)" : "=r" (temp) : "r" (m));
																		//%0 output    %1 input
		asm volatile ("sc %0, 0(%1)" : "=r" (lock) : "r" (m));

		if (!temp && lock) {
			//got lock
			return 1;
		} 
		//wait a little bit until ask for mutex again
		int i;
		for (i = 0; i < 100; ++i); 
	}
	
}

int mutex_release(int* m) {
	*m = 0;
}


int main(int argc, char *argv[]){
  int i;
  int m = 0;
  for(i=0;i<10;i++) {
  	mutex_acquire(&m);
    printf("Hi from processor MIPS!\n");
    //mutex_release(&m)
  }

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

