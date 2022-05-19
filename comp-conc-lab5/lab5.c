#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NTHREADS 5

/* Variaveis globais */
int x = 0;
pthread_mutex_t x_mutex;
pthread_cond_t x_cond;


/* Thread 1: última a executar */
void * thread_1 (void * t) {

  pthread_mutex_lock(&x_mutex);

  while (x < 4) {
    pthread_cond_wait(&x_cond, &x_mutex);
  }

  printf("Volte sempre!\n");

  pthread_mutex_unlock(&x_mutex); 
  
  pthread_exit(NULL);
}

/* Thread 2 */
void * thread_2 (void * t) {
  printf("Fique a vontade.\n");

  pthread_mutex_lock(&x_mutex);
  x++;

  if (x < 1) {
  pthread_cond_wait(&x_cond, &x_mutex);
  }

  if (x == 4) {
    pthread_cond_signal(&x_cond);
  }

  pthread_mutex_unlock(&x_mutex); 
  
  pthread_exit(NULL);
}

/* Thread 3 */
void * thread_3 (void * t) {
  printf("Sente-se por favor.\n");

  pthread_mutex_lock(&x_mutex);
  x++;

  if (x < 1) {
  pthread_cond_wait(&x_cond, &x_mutex);
  }

  if (x == 4) {
    pthread_cond_signal(&x_cond);
  }

  pthread_mutex_unlock(&x_mutex); 
  
  pthread_exit(NULL);
}

/* Thread 4 */
void * thread_4 (void * t) {
  printf("Aceita um copo d’água?\n");

  pthread_mutex_lock(&x_mutex);
  x++;

  if (x < 1) {
  pthread_cond_wait(&x_cond, &x_mutex);
  }

  if (x == 4) {
    pthread_cond_signal(&x_cond);
  }

  pthread_mutex_unlock(&x_mutex); 

  pthread_exit(NULL);
}

/* Thread 5: primeira a executar */
void * thread_5 (void * t) {
  printf("Seja bem-vindo!\n");  //primeira mensagem a aparecer
  
  pthread_mutex_lock(&x_mutex);
  x++;
  
  pthread_cond_broadcast(&x_cond);
  
  pthread_mutex_unlock(&x_mutex); 

  pthread_exit(NULL);
}


/* Funcao principal */
int main(int argc, char *argv[]) {
  int i; 
  pthread_t threads[NTHREADS];

  /* Inicilaiza o mutex (lock de exclusao mutua) e a variavel de condicao */
  pthread_mutex_init(&x_mutex, NULL);
  pthread_cond_init (&x_cond, NULL);

  /* Cria as threads */
  pthread_create(&threads[0], NULL, thread_1, NULL);
  pthread_create(&threads[1], NULL, thread_2, NULL);
  pthread_create(&threads[2], NULL, thread_3, NULL);
  pthread_create(&threads[3], NULL, thread_4, NULL);
  pthread_create(&threads[4], NULL, thread_5, NULL);
  
  /* Espera todas as threads completarem */
  for (i = 0; i < NTHREADS; i++) {
    pthread_join(threads[i], NULL);
  }

  /* Desaloca variaveis e termina */
  pthread_mutex_destroy(&x_mutex);
  pthread_cond_destroy(&x_cond);
}
