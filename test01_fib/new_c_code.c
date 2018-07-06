#include <pthread.h>
#include <assert.h>

int i=1, j=1;
int opu_i = i,opu_j = j,mjo;
#define NUM 5


int read_i()
{
  return i;
}

void write_i(int x)
{

int opu_x = x;
  i = x;
}


int read_j()
{
  return j;
}

void write_j(int x)
{
int opu_x = x;
  j = x;
}


void *t1(void* arg)
{
  int k = 0;
int opu_k = k,mjo;
assert(i <= j);
assert(j == opu_j);
assert(i == opu_i);
assert(i <= j);
assert(j == 1 || j == 2);
    write_i(read_i()+read_j());
    write_i(read_i()+read_j());
    write_i(read_i()+read_j());
assert(i != j);
assert(i == 3 || i == 5);
assert(j == opu_j);
assert(i == opu_i);
assert(i != j);
assert(i == 3 || i == 5);
    write_i(read_i()+read_j());
    write_i(read_i()+read_j());

assert(i != j);
assert(j == opu_j);
assert(i == opu_i);
assert(i != j);
assert(j >= opu_i);
assert(i > opu_i);
assert(i != j);
  return NULL;	
}


void *t2(void* arg)
{

  int k = 0;
int opu_k = k,mjo;





  return NULL;

}

int main(int argc, char **argv)
{
int opu_argc = argc;
  pthread_t id1, id2;

  pthread_create(&id1, NULL, t1, NULL);
  pthread_create(&id2, NULL, t2, NULL);

  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

//  assert(! (i > 144 || j > 144));

  return 0;

}



