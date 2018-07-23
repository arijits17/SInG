#include <pthread.h>
#include <assert.h>

int i=1, j=1;
int ct = 0;
pthread_mutex_t m;

int read_i1()
{
  int tmp = __CPROVER_nondet_int();
  pthread_mutex_lock(&m);
  ct++;
  pthread_mutex_unlock(&m);
  return tmp;
}


int read_j1()
{
  int tmp = __CPROVER_nondet_int();

  pthread_mutex_lock(&m);
  ct++;
  pthread_mutex_unlock(&m);
  return tmp;
}

int read_i2()
{
  int tmp = __CPROVER_nondet_int();

  pthread_mutex_lock(&m);
  ct++;
  pthread_mutex_unlock(&m);
  return tmp;
}


int read_j2()
{
  int tmp = __CPROVER_nondet_int();

  pthread_mutex_lock(&m);
  ct++;
  pthread_mutex_unlock(&m);
  return tmp;
}

void *t1(void* arg)
{
  
  i = read_i1() + read_j1();

  return NULL;	
}


void *t2(void* arg)
{

  j = read_i2() + read_j2();


  return NULL;

}

int main(int argc, char **argv)
{
  pthread_t id1, id2;

  pthread_create(&id1, NULL, t1, NULL);
  pthread_create(&id2, NULL, t2, NULL);

  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

  assert(i < 3);

  return 0;

}



