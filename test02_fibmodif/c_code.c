// extern void __VERIFIER_error() __attribute__ ((__noreturn__));

#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
// void __VERIFIER_assert(int expression) { if (!expression) { ERROR: __VERIFIER_error();}; return; }
// extern int __VERIFIER_nondet_int(void);


int udon_dummy_t1_l01(int x, int y){return 0;}
int udon_dummy_t1_l02(int x, int y){ return 0;}
int udon_dummy_t1_l03(int x, int y){  return 0;}
int udon_dummy_t1_l04(int x, int y){  return 0;}

int i=1, j=1;

#define NUM 5

void *
t1(void* arg)
{
	int k = 0;
	int tmp;
	// tmp = __VERIFIER_nondet_int();

	udon_dummy_t1_l01(i,j);

	srand((unsigned)time(NULL));

	tmp = rand();
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


	tmp = rand();
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

	udon_dummy_t1_l02(i,j);


	tmp = rand();
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

	tmp = rand();
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

	tmp = rand();
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

	udon_dummy_t1_l03(i,j);

	return NULL;


	
}


void *
t2(void* arg)
{
	int k = 0;
	int tmp;
	// tmp = __VERIFIER_nondet_int();
	srand((unsigned)time(NULL));

	for (k = 0; k < NUM; k++){
	tmp = rand();
	printf("%d\n", tmp);
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

	
	return NULL;

}



int
main(int argc, char **argv)
{
	pthread_t id1, id2;

	pthread_create(&id1, NULL, t1, NULL);
	pthread_create(&id2, NULL, t2, NULL);

	pthread_join(id1,0);
	pthread_join(id2,0);
//assert(!	 (i > 144 || j > 144));

	return 0;
}
 