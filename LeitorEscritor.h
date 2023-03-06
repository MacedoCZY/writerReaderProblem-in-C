#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <linux/unistd.h>
#include <sys/types.h>
#include <syscall.h>

#define LEITORES 20
#define ESCRITORES 20    
#define T_SLEEP 0
#define X_REPS 2

pthread_mutex_t controleAcessoDocumento;
pthread_mutex_t controleRegiaoCritica;      
int contador_Leitores;   

void *leitura();
void *escrevendo();
void inicio_Lendo();
void final_Lendo();
void inicio_Escrevendo();
void final_Escrevendo();