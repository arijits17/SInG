#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>
#include <stdbool.h>

unsigned a, b;
pthread_mutex_t m;
bool cond = true;

unsigned gcdk(unsigned x, unsigned y)
{
	if (x == 0 || y == 0)
		return 0;

	if (x == y)
		return x;

	if (x > y)
		return gcdk(x-y, y);
	return gcdk(x, y-x);
}

void check_gcd(unsigned a_in, unsigned b_in, unsigned gcd)
{
	unsigned guessed_gcd = gcdk(a_in,b_in);

	assert(gcd>=guessed_gcd);
}



void okay_f3(){
	if(a!=b)
	{	
		pthread_mutex_lock(&m);
		if(a>b)
			a=a-b;
		pthread_mutex_unlock(&m);

		if(a==b){cond = false;}
		
	}

	if(cond)
	{	
		pthread_mutex_lock(&m);
		if(a>b)
			a=a-b;
		pthread_mutex_unlock(&m);

		if(a==b){cond = false;}
		
	}
}

void okay_f2(int a, int b){

	okay_f3(a,b);
	
	if(cond)
	{	
		pthread_mutex_lock(&m);
		if(a>b)
			a=a-b;
		pthread_mutex_unlock(&m);

		if(a==b){cond = false;}
		
	}

	if(cond)
	{	
		pthread_mutex_lock(&m);
		if(a>b)
			a=a-b;
		pthread_mutex_unlock(&m);

		if(a==b){cond = false;}
		
	}
}

void okay_f1(int a, int b){

	okay_f3(a,b);
	
	while(cond)
	{	
		pthread_mutex_lock(&m);
		if(a>b)
			a=a-b;
		pthread_mutex_unlock(&m);

		if(a==b){cond = false;}
		
	}

	
}


void* dec_a(void* arg)
{
	(void)arg;
	
	okay_f1(a,b);

	return 0;
}

void* dec_b(void* arg)
{
	(void)arg;

	while(a!=b)
	{
		pthread_mutex_lock(&m);
		if(b>a)
			b=b-a;
		pthread_mutex_unlock(&m);
	}

	return 0;
}



unsigned start(unsigned a_in, unsigned b_in)
{
	a=a_in;
	b=b_in;

	pthread_t t1, t2;

	pthread_create(&t1, 0, dec_a, 0);
	pthread_create(&t2, 0, dec_b, 0);

	pthread_join(t1, 0);
	pthread_join(t2, 0);

	return a;
}



int main()
{
  // for testing with small unwinding bounds
	srand(time(NULL));
  unsigned a_in=rand();//__VERIFIER_nondet_uint(); //=8;
  unsigned b_in=rand();//__VERIFIER_nondet_uint(); //=6;

  // __VERIFIER_assume(a_in>0);
  // __VERIFIER_assume(b_in>0);
  check_gcd(a_in, b_in, start(a_in, b_in));
  return 0;
}