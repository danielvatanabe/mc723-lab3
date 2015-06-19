#include <stdio.h>
#include <stdlib.h>

int proc = 0;

int main(int argc, char *argv[]){
  int i;
  
  // Ativar o periferico (controller) para os proximos processadores utilizando enderecos de memoria especiais
  // Comando: ative o processador x, desligue o processador y.
  // No boot inicial, ativar apenas um processador.
  
  // Variavel global indica quantas vezes cada processador passou por aqui
  
  printf("Hi from %d\n", proc);

  unsigned int *cont_addr;
  proc++;
  cont_addr = 5242890U + proc;
  // Ativa o proximo e desativa o atual
  if (proc < 8) {
      *cont_addr = 10000U;
      cont_addr = 5242910U + proc - 1;
      *cont_addr = 10000U;
  } else {
    // Ativa todos novamente
    for (proc = 0; proc < 7; proc++) {
        cont_addr = 5242890U + proc;
         *cont_addr = 10000U;
    }
  }

  exit(0); // To avoid cross-compiler exit routine
  return 0; // Never executed, just for compatibility
}

