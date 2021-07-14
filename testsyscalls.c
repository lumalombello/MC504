#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

	int func_get = 384;
	int func_set = 385;
	int uid = 0;
	
	//Pegando o valor do peso
	int get_weight = syscall(func_get, uid); 
	printf("Peso para o id %d: %d \n", uid, get_weight);
	
	//Mudando o valor do peso
	int set_weight = syscall(func_set, uid, 3);
	if(set_weight == 0){
		get_weight = syscall(func_get, uid); 
		printf("Peso para o id %d: %d \n", uid, get_weight);
	}
	else{
		printf("Erro! Valor de peso incorreto\n");
	}
	
	//Testando ids invalidos
	uid = -35;
	get_weight = syscall(func_get, uid); 
	printf("Retorno da funcao get para o id %d: %d\n", uid, get_weight);
	
	uid = 66000;
	get_weight = syscall(func_get, uid); 
	printf("Retorno da funcao get para o id %d: %d\n", uid, get_weight);
	
	//Testando peso invalido
	uid = 0;
	set_weight = syscall(func_set, uid, -98);
	if(set_weight == 0){
		get_weight = syscall(func_get, uid); 
		printf("Peso para o id %d: %d \n", uid, get_weight);
	}
	else{
		printf("Erro! Valor de peso incorreto\n");
	}
	
	printf("Funcoes para get e set de pesos testadas!\nBye :)\n");
	return 0;
}
