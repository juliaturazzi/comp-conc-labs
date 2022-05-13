#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include "timer.h"

long long int variavel = 0; 
long long int dim;

int NTHREADS;
int *vetorInicial;

float *vetorSaidaSequencial;
float *vetorSaidaConcorrente;

pthread_mutex_t mutex;

//funcao utilizada para definir se um numero e primo
int numeroPrimo (long long int numero) {
  double raiz = sqrt(numero);   //raiz quadrada
  
  if(numero < 2)   return 0;

  for(int i = 2; i <= (raiz); i++)
    if(numero % i == 0)    return 0;
  
  return 1;
}

//funcao executada de forma sequencial
void funcaoSequencial (long long int dim, int * vetorInicial) {
  for(long long int i = 0; i < dim; i++){
    if(numeroPrimo(vetorInicial[i]))   vetorSaidaSequencial[i] = sqrt(vetorInicial[i]);
    
    vetorSaidaSequencial[i] = vetorInicial[i];
  }
}

//funcao executada pelas threads (concorrente)
void *processaPrimos () {
  pthread_mutex_lock(&mutex);
  int variavel_threads = variavel;
  variavel++;
  pthread_mutex_unlock(&mutex);

  while(variavel_threads < dim){
    if(numeroPrimo(vetorInicial[variavel_threads]))    vetorSaidaConcorrente[variavel_threads] = sqrt(vetorInicial[variavel_threads]);
    
    vetorSaidaConcorrente[variavel_threads] = vetorInicial[variavel_threads];

    pthread_mutex_lock(&mutex);
    variavel_threads = variavel;
    variavel++;
    pthread_mutex_unlock(&mutex);
  }

  pthread_exit(NULL);
}

//funcao principal
int main (int argc, char *argv[])
{
  pthread_t *tid;
    
  double ini, fim;
  double tempoConcorrente, tempoSequencial;

  if(argc < 3){
    fprintf(stderr, "Digite: %s <dimensao do vetor> <numero threads>\n", argv[0]);
    return 3;
  }
    
  dim = atoll(argv[1]);
  NTHREADS = atoi(argv[2]);

  //aloca memoria
  vetorInicial = (int *)malloc(sizeof(int) * dim);
    
  vetorSaidaConcorrente = (float *)malloc(sizeof(float) * dim);
  vetorSaidaSequencial = (float *)malloc(sizeof(float) * dim);

  //preenchimento do vetor
  srand(time(NULL));
  for(long int i = 0; i < dim; i++){
    vetorInicial[i] = rand() % 100000;
  }

  //chamada da funcao sequencial
  GET_TIME(ini);
  funcaoSequencial(dim, vetorInicial);
    
  GET_TIME(fim);
  tempoSequencial = fim - ini;

  //funcao executada de forma concorrente
  GET_TIME(ini);
  pthread_mutex_init(&mutex, NULL);

  tid = (pthread_t *)malloc(sizeof(pthread_t) * NTHREADS);
    
  if(tid == NULL){
    fprintf(stderr, "ERRO--malloc\n");
    return 2;
  }

  //criacao das threads
  for(int i = 0; i < NTHREADS; i++){
    if(pthread_create(tid + i, NULL, processaPrimos, NULL)){
      printf("--ERRO: pthread_create()\n");
      
      exit(-1);
    }
  }

  //aguarda o termino das threads
  for(int i = 0; i < NTHREADS; i++){
    if(pthread_join(*(tid + i), NULL)){
      printf("--ERRO: pthread_join() \n");
      
      exit(-1);
    }
  }
  
  pthread_mutex_destroy(&mutex);

  GET_TIME(fim);
  tempoConcorrente = fim - ini;
 
  //verifica se os vetores "saída", sequencial e concorrente, são iguais
  for(int i = 0; i < dim; i++){
    if(vetorSaidaSequencial[i] != vetorSaidaConcorrente[i]){
      printf("--ERRO: vetores \n");
      break;
    }
  }

  printf("Tempo sequencial = %lf\n", fim - ini);
  printf("Tempo concorrente = %lf\n\n", tempoConcorrente);
  printf("Ganho de desempenho =  %lf\n", tempoSequencial / tempoConcorrente);

  free(vetorSaidaSequencial);
  free(vetorSaidaConcorrente);
  free(tid);
  return 0;
}
