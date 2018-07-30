#include <pthread.h>
#include <stdio.h>

int b = 0; 

void* dec_a(void* arg)
{	
	static int count = 0;
	while(b==0)
		printf("Routine Keeps me in Line %d\n", count++);
}


void* dec_b(void* arg)
{
	b = 1;
	assert(b==1);
}



int main()
{

	pthread_t t1, t2;

	pthread_create(&t1, 0, dec_a, 0);
	pthread_create(&t2, 0, dec_b, 0);

	pthread_join(t1, 0);
	pthread_join(t2, 0);

	return 0;
}