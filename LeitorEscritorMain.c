#include <stdio.h>
#include "LeitorEscritor.h"

int main(){
	pthread_t T_Escritor[ESCRITORES];
	pthread_t T_Leitor[LEITORES]; 

	pthread_mutex_init(&controleAcessoDocumento, NULL);
	pthread_mutex_init(&controleRegiaoCritica, NULL);

	for(int i = 0; i < ESCRITORES; i++){
		pthread_create(&T_Escritor[i], NULL, &escrevendo, NULL);
	}

	for(int i = 0; i < LEITORES; i++){
		pthread_create(&T_Leitor[i], NULL, &leitura, NULL);
	}

	for(int i = 0; i < ESCRITORES; i++){
		pthread_join(T_Escritor[i], NULL);
	}

	for(int i = 0; i < LEITORES; i++){
		pthread_join(T_Leitor[i], NULL);
	}

	return 0;
}