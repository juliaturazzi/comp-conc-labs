/* Multiplicacao de matrizes (considerando matrizes quadradas) */
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include <time.h>
#include "timer.h"

float *matrixA; ////matriz A de entrada
float *matrixB; //matriz B de entrada

float *sequentialResult; //vetor de saída sequencial
float *concurrentResult; //vetor de saída concorrente

int nthreads; //numero de threads
pthread_t *tid;

typedef struct{
   int id; //identificador do elemento que a thread ira processar
   int dim; //dimensao das estruturas de entrada
} tArgs;

//funcao executada de forma sequencial
void matrixMultiplication(int dim) {
   for(int i=0; i<dim; i++)
      for(int j=0; j<dim; j++)
        for(int k=0; k<dim; k++)
         sequentialResult[i*dim+j] += matrixA[i*dim+k] * matrixB[i*dim+j];
}

//funcao executada de forma concorrente (pelas threads)
void * threadMatrixMultiplication(void *arg) {
   tArgs *args = (tArgs*) arg;
   
   for(int i=args->id; i<args->dim; i+=nthreads)
      for(int j=0; j<args->dim; j++)
        for(int k=0; k<args->dim; k++)
         concurrentResult[i* (args->dim) + j] += matrixA[i* (args->dim) + k] * matrixB[i* (args->dim) + j];

   pthread_exit(NULL);
}

 //criacao das matrizes 
void matrixCreation(int dim) { 
  srand(time(NULL));
   for (int i=0; i<dim; i++){
      for (int j=0; j<dim; j++){
         sequentialResult[i * dim + j] = 0;
         concurrentResult[i * dim + j] = 0;
         matrixA[i*dim+j] = rand() % 10;
         matrixB[i*dim+j] = rand() % 10;
      }
   }
}

//fluxo principal
int main(int argc, char* argv[]) {
   int dim; //dimensao da matrixAriz de entrada
   pthread_t *tid; //identificadores das threads no sistema
   tArgs *args; //identificadores locais das threads e dimensao
   double inicio, fim, concurrentDelta, sequentialDelta;
   
   if(argc<3) {
      printf("Digite: %s <dimensao da matrixAriz> <numero de threads>\n", argv[0]);
      return 1;
   }

   dim = atoi(argv[1]);
   nthreads = atoi(argv[2]);

   //alocacao de memoria para as estruturas de dados
    matrixA = (float *) malloc(sizeof(float) * dim * dim);
   if (matrixA == NULL){printf("ERRO--malloc\n"); return 2;}

   matrixB = (float *) malloc(sizeof(float) * dim * dim);
   if (matrixB == NULL){printf("ERRO--malloc\n"); return 2;}

   sequentialResult = (float *) malloc(sizeof(float) * dim * dim);
   if (sequentialResult == NULL){printf("ERRO--malloc\n"); return 2;}

   concurrentResult = (float *) malloc(sizeof(float) * dim * dim);
   if (concurrentResult == NULL){printf("ERRO--malloc\n"); return 2;}  

   matrixCreation(dim);   //criacao das matrizes que serao utilizadas

   GET_TIME(inicio);
   matrixMultiplication(dim);  //multiplicacao sequencial

   GET_TIME(fim);
   sequentialDelta = fim - inicio;   //calculo do tempo para a execucao do programa sequencial
   printf("Tempo de multiplicacao sequencial: %.3f segundos.\n", sequentialDelta);
  
    //alocacao das estruturas
   tid = (pthread_t*) malloc(sizeof(pthread_t)*nthreads);
   if(tid==NULL) {printf("ERRO--malloc"); return 1;}
   args = (tArgs*) malloc(sizeof(tArgs)*nthreads);
   if(args==NULL) printf("ERRO--malloc");


   GET_TIME(inicio);
    //criacao das threads
   for(int i=0; i<nthreads; i++) {
      (args+i)->id = i;
      (args+i)->dim = dim;
      if(pthread_create(tid+i, NULL,threadMatrixMultiplication, (void *) (args+i))){   //criacao da thread e execucao da multiplicacao concorrente
         printf("ERRO--pthread_create"); 
         exit(-1);
      }
   } 
  
   //espera pelo termino das threads
   for(int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), NULL) ) {
          printf("ERRO--pthread_join");
          exit(-1);
      }
   }

   GET_TIME(fim)   
   concurrentDelta = fim - inicio;    //calculo do tempo para a execucao do programa concorrente
   printf("Tempo de multiplicacao concorrente com %d thread(s): %.3f segundos.\n\n", nthreads, concurrentDelta);

   printf("Desempenho: %.3f", (sequentialDelta/ concurrentDelta));

   //verifica se as matrizes sao iguais
   for (int i=0; i<dim; i++)
      for (int j=0; j<dim; j++)
         if(sequentialResult[i* dim + j] != concurrentResult[i* dim + j]){
            printf("ERRO--multiplication funccions");
            break;
         }

   //liberacao da memoria
   free(matrixA);
   free(matrixB);
   free(sequentialResult);
   free(concurrentResult);
   free(args);
   free(tid);
   
   return 0;
}