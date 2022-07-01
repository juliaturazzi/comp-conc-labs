#include <stdio.h>
#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>

#define NTHREADS 5

/* Variaveis globais */
int x = 0; //variavel compartilhada entre as threads
sem_t condt2, condt3;


/* Thread 1: última a executar */
void * t1 (void * threadid) {
  while (x < 4) sem_wait(&condt3); //espera todas as threads executarem
  
  printf("Volte sempre!\n");
  
  pthread_exit(NULL);
}


/* Thread 2 */
void * t2 (void * threadid) {
  printf("Fique a vontade.\n");
  
  sem_wait(&condt2); //permite que a thread execute
  x++;

  if (x < 1) sem_wait(&condt2); 

  if (x == 4) sem_post(&condt3);
  
  pthread_exit(NULL);
}

/* Thread 3 */
void * t3 (void * threadid) {
  printf("Sente-se por favor.\n");
  
  sem_wait(&condt2); //permite que a thread execute
  x++;

  if (x < 1) sem_wait(&condt2); 

  if (x == 4) sem_post(&condt3); 
  
  pthread_exit(NULL);
}

/* Thread 4 */
void * t4 (void * threadid) {
  printf("Aceita um copo d’água?\n");
  
  sem_wait(&condt2); //permite que a thread execute
  x++;

  if (x < 1) sem_wait(&condt2); 

  if (x == 4) sem_post(&condt3);

  pthread_exit(NULL);
}

/* Thread 5: primeira a executar */
void * t5 (void * threadid) {
  printf("Seja bem-vindo!\n");  //primeira mensagem a aparecer
  
  x = 1;
  sem_post(&condt2); //permite que as threads 2, 3 e 4 executem

  pthread_exit(NULL);
}


/* Funcao principal */
int main(int argc, char *argv[]) {
  pthread_t tid[NTHREADS];
  int *id[5], t;

  for (t=0; t<NTHREADS; t++) {
    //aloca espaco para o identificar da thread
    if ((id[t] = malloc(sizeof(int))) == NULL) {
       pthread_exit(NULL); return 1;
    }
    *id[t] = t+1;
  }

  //inicia os semaforos
  sem_init(&condt2, 0, 0);
  sem_init(&condt3, 0, 0);

  //cria as tres threads
  if (pthread_create(&tid[0], NULL, t5, (void *)id[0])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[1], NULL, t4, (void *)id[1])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[2], NULL, t3, (void *)id[2])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[3], NULL, t2, (void *)id[0])) { printf("--ERRO: pthread_create()\n"); exit(-1); }
  if (pthread_create(&tid[4], NULL, t1, (void *)id[0])) { printf("--ERRO: pthread_create()\n"); exit(-1); }

  //--espera todas as threads terminarem
  for (t=0; t<NTHREADS; t++) {
    if (pthread_join(tid[t], NULL)) {
         printf("--ERRO: pthread_join() \n"); exit(-1); 
    } 
    free(id[t]);
  } 
  pthread_exit(NULL);
}
