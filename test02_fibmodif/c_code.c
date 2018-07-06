extern void __VERIFIER_error() __attribute__ ((__noreturn__));

#include <pthread.h>

void __VERIFIER_assert(int expression) { if (!expression) { ERROR: __VERIFIER_error();}; return; }
extern int __VERIFIER_nondet_int(void);

int i=1, j=1;

#define NUM 5

void *
t1(void* arg)
{
	int k = 0;
	int tmp;
	for (k = 0; k < NUM; k++){
	tmp = __VERIFIER_nondet_int();
		if(tmp%2 != 0){
			
			i+=j;
		} else{
			if(tmp%4 != 0){
				i = i-j;
			} else if(tmp%8 != 0){
				i--;
			} else { 
				i++;
			}


		}	
	}
	
}


void *
t2(void* arg)
{
	int k = 0;
	int tmp;
	for (k = 0; k < NUM; k++){
	tmp = __VERIFIER_nondet_int();
		if(tmp%2 != 0){
				j+=i;
		} else{
			if(tmp%4 != 0){
				i = i-j;
			} else if(tmp%8 != 0){
				i--;
			} else { 
				i++;
			}


		}

	}

	
}



int
main(int argc, char **argv)
{
	pthread_t id1, id2;

	pthread_create(&id1, NULL, t1, NULL);
	pthread_create(&id2, NULL, t2, NULL);

	if (i > 144 || j > 144) {
		ERROR: __VERIFIER_error();
	}

	return 0;
}
