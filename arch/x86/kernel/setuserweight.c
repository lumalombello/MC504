#include <linux/unistd.h>
#include <linux/linkage.h>
#include <linux/unistd.h>
#include <linux/linkage.h>
#include <linux/cred.h>
#include <linux/sched/user.h>
#include <linux/syscalls.h>
#include <linux/user_namespace.h>

asmlinkage long sys_setuserweight(int uid, int weight) {

	kuid_t k_usr_id;
	
	//Verifica se root
	if(from_kuid_munged(current_user_ns(), current_uid()) != 0) {
		return EACCES;
	}
	
	//Verifica validade do uid e do peso
	if(weight <= 0 || uid < -1 || uid > 65535) { 
		return EINVAL;
	}
	
	//Caso de owner fazendo a chamada 
	if(uid == -1){
		uid = from_kuid_munged(current_user_ns(), current_uid());
	}
	
	//Verifica que o usuario existe
	k_usr_id.val = uid;
	if(find_user(k_usr_id) == NULL){
		return -1;
	}
	
	//Define novo valor para o peso desse usuario
	find_user(k_usr_id)->weight = weight;
	
	return 0;
}




