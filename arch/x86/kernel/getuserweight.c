#include <linux/unistd.h>
#include <linux/linkage.h>
#include <linux/unistd.h>
#include <linux/linkage.h>
#include <linux/cred.h>
#include <linux/sched/user.h>
#include <linux/syscalls.h>
#include <linux/user_namespace.h>

asmlinkage long sys_getuserweight(int uid) {

	kuid_t k_usr_id;
	
	//Verifica validade do uid
	if(uid < -1 || uid > 65535) { 
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

	return find_user(k_usr_id)->weight;
}


