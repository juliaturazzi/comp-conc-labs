//Encontrar o maior e o menor valor de um vetor de numeros reais
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

long long int N; //numero de elementos do vetor
int nthreads; //numero de threads
double *vetor; //vetor de entrada com dimensao N 

double sequencialSmallest, //menor valor do vetor de N elementos (utilizando o programa sequencial)
sequencialHigher; //maior valor do vetor de N elementos (utilizando o programa sequencial)

double concurrentSmallest, //menor valor do vetor de N elementos (utilizando o programa concorrente)
concurrentHigher; //maior valor do vetor de N elementos (utilizando o programa concorente)


//fluxo das threads
void * tarefa(void * arg) {
   long int id = (long int) arg; //identificador da thread
   long int tamBloco = N/nthreads;  //tamanho do bloco de cada thread 
   long int ini = id * tamBloco; //elemento inicial do bloco da thread
   long int fim; //elemento final(nao processado) do bloco da thread
   if(id == nthreads-1) fim = N;
   else fim = ini + tamBloco; //trata o resto se houver

   for(long int i=ini; i<fim; i++){
       if(vetor[i]<concurrentSmallest) 
       concurrentSmallest=vetor[i];
       
       if(vetor[i]>concurrentHigher)
       concurrentHigher=vetor[i];
   }
   
   pthread_exit(NULL); 
}

//fluxo principal
int main(int argc, char *argv[]) {
   double ini, fim; //tomada de tempo
   pthread_t *tid; //identificadores das threads no sistema
   
   //recebe e valida os parametros de entrada (dimensao do vetor, numero de threads)
   if(argc < 3) {
       fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
       return 1; 
   }
   N = atoll(argv[1]);
   nthreads = atoi(argv[2]);
   //aloca o vetor de entrada
   vetor = (double*) malloc(sizeof(double)*N);
   if(vetor == NULL) {
      printf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //preenche o vetor de entrada
   srand(time(NULL));
   for (int i=0; i<N; i++)
       vetor[i] = rand();
  
   //soma sequencial dos elementos
   GET_TIME(ini);
    for(long int i=0; i<N; i++){
      if(vetor[i]>sequencialHigher) sequencialHigher = vetor[i];
      if(vetor[i]<sequencialSmallest) sequencialSmallest = vetor[i];
    }
   GET_TIME(fim);
   printf("\nTempo sequencial:  %lf\n", fim-ini);

   //soma concorrente dos elementos
   GET_TIME(ini);
   tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
   if(tid==NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }
   //criar as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
         printf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   //aguardar o termino das threads
   for(int i=0; i<nthreads; i++) {
      pthread_join(*(tid+i), NULL);
   }
   
   GET_TIME(fim);
   printf("Tempo concorrente:  %lf\n\n", fim-ini);

    if(sequencialHigher != concurrentHigher || sequencialSmallest != concurrentSmallest){
       printf(stderr, "ERRO--resultados sequencial e concorrente diferentes");
   }


   //libera as areas de memoria alocadas
   free(vetor);
   free(tid);

   return 0;
}