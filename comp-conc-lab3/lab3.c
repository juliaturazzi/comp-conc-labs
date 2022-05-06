//Encontra o maior e o menor valor de um vetor de numeros reais
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include "timer.h"

long long int N; //numero de elementos do vetor
int nthreads; //numero de threads
double *vetor; //vetor de entrada com dimensao N

double sequential_m; //menor valor sequencial
double sequential_M; //maior valor sequencial

double concurrent_m; //menor valor concorrente
double concurrent_M; //maior valor concorrente

//fluxo das threads
void * tarefa(void * arg) {
   long int id = (long int) arg; //identificador da thread
   long int tamBloco = N/nthreads;  //tamanho do bloco de cada thread 
   long int ini = id * tamBloco; //elemento inicial do bloco da thread
   long int fim; //elemento final(nao processado) do bloco da thread
   
   if(id == nthreads-1) fim = N; 

   else fim = ini + tamBloco; //trata o resto se houver
   
   //modifica o elemento do vetor na posicao i para cada valor concorrente (menor e maior)
   concurrent_m = vetor[0];
   concurrent_M = vetor[0];
   
   for(long int i=0; i<N; i++) {
      if(vetor[i] > concurrent_M) concurrent_M = vetor[i];
      if(vetor[i] < concurrent_m) concurrent_m = vetor[i];
   }
   pthread_exit(NULL);
}

void vetorCreation(int N) { 
  srand(time(NULL));
   for (int i=0; i<N; i++)  vetor[i] = rand() % 100000000000000;
   }


//fluxo principal
int main(int argc, char *argv[]) {
   double ini, fim; //tomada de tempo
   pthread_t *tid; //identificadores das threads no sistema
   
   double sequential_time, concurrent_time; //recebe o tempo obtido (sequencial e concorrente)
   
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
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }

   vetorCreation(N);
 
   GET_TIME(ini);
   sequential_m = vetor[0];
   sequential_M = vetor[0];
   
   for(long int i=0; i<N; i++) {
      if(vetor[i] < sequential_m) sequential_m = vetor[i];
      if(vetor[i] > sequential_M) sequential_M = vetor[i];
   }

   GET_TIME(fim);
   sequential_time = fim-ini;
   printf("Tempo sequencial:  %lf\n",sequential_time);

   //maior e o menor valor do vetor (concorrente)
   GET_TIME(ini);
   tid = (pthread_t *) malloc(sizeof(pthread_t) * nthreads);
   if(tid == NULL) {
      fprintf(stderr, "ERRO--malloc\n");
      return 2;
   }

   //criar as threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_create(tid+i, NULL, tarefa, (void*) i)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   
   //aguardar o termino das threads
   for(long int i=0; i<nthreads; i++) {
      if(pthread_join(*(tid+i), NULL)){
         fprintf(stderr, "ERRO--pthread_create\n");
         return 3;
      }
   }
   
   GET_TIME(fim);
   concurrent_time = fim-ini;
   printf("Tempo concorrente:  %lf\n\n", concurrent_time);

   //verifica se os valores acessados são iguais no sequencial e concorrente
   if(sequential_m != concurrent_m) {
       fprintf(stderr, "ERRO--vetor\n");
   }

   if(sequential_M != concurrent_M) {
       fprintf(stderr, "ERRO--vetor\n");
   }

   //exibir os resultados
   printf("Menor sequencial:  %.12lf\nMaior sequencial:  %.12lf\n\n", sequential_m, sequential_M);
   printf("Menor concorrente: %.12lf\nMaior concorrente: %.12lf\n\n", concurrent_m, concurrent_M);

   printf("Desempenho: %.12lf\n\n\n", sequential_time/ concurrent_time);

   //libera as areas de memoria alocadas
   free(vetor);
   free(tid);

   return 0;
}
