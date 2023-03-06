#include <stdio.h>
#include "LeitorEscritor.h"


void *leitura(){
	int i = 0;
	while (i < X_REPS){
		pthread_mutex_lock(&controleRegiaoCritica);
		contador_Leitores++;
		
		inicio_Lendo();
		//printf("Existem %d leitores\n", contador_Leitores);
		if(contador_Leitores == 1)
			pthread_mutex_lock(&controleAcessoDocumento);
		
		pthread_mutex_unlock(&controleRegiaoCritica);
		
		printf("Lendo...\n");
		sleep(T_SLEEP);
		
		pthread_mutex_lock(&controleRegiaoCritica);
		contador_Leitores--;
		final_Lendo();
		
		if(contador_Leitores == 0) 
			pthread_mutex_unlock(&controleAcessoDocumento);
		
		pthread_mutex_unlock(&controleRegiaoCritica);

		++i;
	}
}

void *escrevendo(){
	int i = 0;
	int tid;
	while(i < X_REPS){
		pthread_mutex_lock(&controleAcessoDocumento);
		inicio_Escrevendo();
		printf("Escrevendo...\n");
		sleep(T_SLEEP);
		final_Escrevendo();
		pthread_mutex_unlock(&controleAcessoDocumento);
		++i;
	}
}

void inicio_Lendo(){
	int tid;
	tid = syscall(SYS_gettid);
	printf("Leitor: Thread %d, entra e começa a ler. Total de %d leitores lendo agora.\n",tid, contador_Leitores);
	sleep(T_SLEEP);
}

void final_Lendo(){
	int tid;
	tid = syscall(SYS_gettid);
	printf("Leitor: Thread %d, terminando de ler. Total de %d leitores lendo agora.\n",tid, contador_Leitores);
	sleep(T_SLEEP);
}

void inicio_Escrevendo(){
	int tid;
	tid = syscall(SYS_gettid);
	printf("Escritor: Thread %d começa a escrever\n", tid);
	sleep(T_SLEEP);
}

void final_Escrevendo(){
	int tid;
	tid = syscall(SYS_gettid);
	printf("Escritor: Thread %d terminando de escrever\n", tid);
	sleep(T_SLEEP);
}