#include <stdio.h>
#include <stdlib.h>

#define MAXN 10000
#define NUM_CORES 8

int proc = 0;
int v1[MAXN], v2[MAXN];
int tam;
int m = 0;
int res = 0;

void mutex2_ac() {
  do {
    if (m == 0) {
      m = 1;
      return;
    }
    
    // printf("---- %d\n", proc);  
    int i;
		for (i = 0; i < 10; ++i); 
  } while(1);
}

void mutex2_rl() {
  m = 0;
  return;
}

// MUTEX methods:
void mutex_acquire(int *m) {
  int lock;
  int one;
  int *p = &one;
  
  do {
    one = 1;
    asm (" \
    ll %0, %3 \n\
    sc %1, %2 \n\
    " \
    : "=r"(lock),"=r"(m) , "=m"(*p) \
    : "m"(*m));
    //: "=r"(one), "=m"(*m) \ //output operands
    //: "r"(lock) ); // inputs

    if (!lock && one) {
      //got lock
      return;
    }
    
    //wait a little bit and ask for mutex again
    int i;
    for (i = 0; i < 100; ++i);
  } while (1);
}

void mutex_release(int* m) {
  *m = 0;
}

// Soma de dois vetores em paralelo (8 cores)
// O resultado eh guardado no primeiro vetor
int main(int argc, char *argv[]) {
  proc++;
  unsigned int *cont_addr;
  int i;
  
  // Instrucoes executadas apenas pelo core pai
  if (proc == 1) {
    FILE *fp;

    if (argc<2) {
      fprintf(stderr, "Usage: soma_vetores <filename>\n");
    }
    fp = fopen(argv[1],"r");
    
    // Leitura dos parametros de entrada
    fscanf(fp, "%d", &tam);
    for (i = 0; i < tam; i++) {
      fscanf(fp, "%d", &v1[i]);
    }
    for (i = 0; i < tam; i++) {
      fscanf(fp, "%d", &v2[i]);
    }
    
    fclose(fp);
    
    // Ativa os outros cores para iniciar a soma em paralelo
    for (i = 1; i < NUM_CORES; i++) {
        cont_addr = 5242890U + i;
         *cont_addr = 10000U;
    }
  }

  // Realiza soma de parte do vetor
  int ini = 0;
  for (i = 0;i < proc-1; i++)
    ini = ini + (tam / NUM_CORES);
  // ini = ini * (proc - 1);
  int fim = 0;
  for (i = 0;i < proc; i++)
    fim = fim + (tam / NUM_CORES);
  if (proc == NUM_CORES) fim += tam % NUM_CORES;
  // int ini = 0, fim = tam;
  for (i = ini; i < fim; i++) {
    v1[i] = v1[i] + v2[i];
  }

  // Imprime resultados obtidos com o mutex
  mutex2_ac();
  // printf("Valores para [%d - %d]:\n", ini, fim-1);
  for (i = ini; i < fim; i++) {
  //  printf("%d ", v1[i]);
    res += v1[i];
  }
  // printf("\n\n");
  mutex2_rl();
  
  /*
  for (i = 0; i < 1000; i++);
  
  if (k == NUM_CORES) {
    for (i = 0; i < tam; i++) {
      printf("%d ", v1[i]);
    }
    printf("\n\n");
    
    for (i = NUM_CORES; i < 8; i++) {
      cont_addr = 5242890U + i;
      *cont_addr = 10000U;
    }
  }*/
  
  // printf("**%d\n",res);
  exit(0); 
  return 0; 
}

