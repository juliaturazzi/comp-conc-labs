#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>

#define NELEMENTS 10000   // numero de elementos armazenados no vetor
#define NTHREADS 2   // total de threads a serem criadas

int elementsArray[NELEMENTS];

// funcao executada pelas threads
void * square (void * arg) {
  
    int tid_sistema, i, j;
    
    tid_sistema =  * (int *) arg;
    i = ((NELEMENTS - 1)/(tid_sistema));  // 9999 posicoes no vetor, divididas para cada threads
    j = 0;
    
    while(j != 5000){
        elementsArray[i] = (i * i);   // realiza o quadrado do numero
        j++; i--;
    }

    pthread_exit(NULL);
}

// funcao principal do programa
int main() {

    pthread_t tid_sistema[NTHREADS];   // identificadores das threads no sistema
    int thread [NTHREADS];   // variavel auxiliar

    // alocando os elementos no vetor
    for (int i = 0; i < NELEMENTS; i++) {
      elementsArray[i] = i;
    }

    // cria as threads
    for (int i = 1; i <= NTHREADS; i++) { 
      thread[i-1] = i; 

      if (pthread_create (&tid_sistema[i-1], NULL, square, (void *) &thread[i-1])) 
        printf ("--ERRO: pthread_create()\n");
    }
     
    // espera todas as threads terminarem
    for (int i = 0; i < NTHREADS; i++) {
       if (pthread_join (tid_sistema[i], NULL)) 
          printf ("--ERRO: pthread_join()\n");  // sinaliza que há erro no join (main terminando o programa antes do termino de todas as threads)
    }

    // testa se os elementos do vetor estao sendo elevados a 2 (se a funcao square funciona)
    for (int i = 0; i < 10000; i++) {
      if (elementsArray [i] == (i * i)) 
          break;
      
      printf("--ERRO: square()\n");   // sinaliza que há erro na funcao square
    }  

    return 0;
}
