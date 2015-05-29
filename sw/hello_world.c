#include <stdio.h>
#include <stdlib.h>

typedef mutex int *;

//return 1 when gets the lock
int mutex_acquire(mutex m) {

	int lock;
	while (*m != 0) {
     asm (
				//   rt    rs
				"ll  %r7, 0(%0)\n"
				"sc $1, 0(%0)"
				: "r" (m) //input rs %0
				: "=r" (lock)//output %1
			);

			if (lock) {
				//got lock
				return 1;
			} 
	}

}

int mutex_release(mutex m) {
	*m = 0;
}


int main(int argc, char *argv[]){
  int i;
  for(i=0;i<10;i++)
    printf("Hi from processor MIPS!\n");

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

