#include <stdio.h>
#include <stdlib.h>

int m = 0;
int proc = 0;
int k =0;

// MUTEX methods
void mutex_acquire(int *m, int id) {

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


    // printf("after: lock=%d , one=%d, mutex=%d\n\n",lock,one,*m);
        if (!lock && one) {
						  //printf("Hi from processor %d!\n", id);
            //got lock
            return;
        }
        //wait a little bit until ask for mutex again
        int i;

        for (i = 0; i < 10; ++i);
    } while(1);
    
}

void mutex_release(int* m, int id) {
 		
    *m = 0;

}

int main(int argc, char *argv[]){
  unsigned int *cont_addr;
  proc++;
  int id = proc;
  int i;



	printf("Start!!\n");
	int v1[5] = {1,2,3,4,5};
	int v2[5] = {10,20,30,40,50};
  for(i=0;i<5;i++) {
		int *p = &v1[i];

		asm(" \
		sdl %1, %0 \n\
		" \
		: "=m"(v1[i]) \ 
		:  "r"(v2[i]));  

		printf("r = %d\n", v1[i]);

  }

  if (proc == 1) {
    for (i = 1; i < 2; i++) {
        cont_addr = 5242890U + i;
         *cont_addr = 10000U;
    }
  }

	
  printf("Start!!\n");
 
	for (i = 0; i < 10; i++) {
		mutex_acquire(&m,id);
		printf("id=%d , Hi from %d!\n", id,i);
		mutex_release(&m,id);
	}	

	
  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}
