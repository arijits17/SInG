#include <pthread.h>
#include <assert.h>

int i=1, j=1;
#define NUM 5

int udon_dummy_t1_l01(int x, int y){return 0;}
int udon_dummy_t1_l02(int x, int y){ return 0;}
int udon_dummy_t2_l01(int x, int y){  return 0;}
int udon_dummy_t2_l02(int x, int y){  return 0;}
int udon_dummy_t1_inloop01(int x, int y){  return 0;}
int udon_dummy_t1_inloop02(int x, int y){  return 0;}
int udon_dummy_t2_inloop01(int x, int y){  return 0;}
int udon_dummy_t2_inloop02(int x, int y){  return 0;}

int read_i()
{
  return i;
}

void write_i(int x)
{
  i = x;
}


int read_j()
{
  return j;
}

void write_j(int x)
{
  j = x;
}


void *t1(void* arg)
{
  int k = 0;
   udon_dummy_t1_l01(i,j);
    write_i(read_i()+read_j());
    write_i(read_i()+read_j());
    udon_dummy_t1_inloop01(i,j);
    write_i(read_i()+read_j());
    // udon_dummy_t1_inloop02(i,j);
    write_i(read_i()+read_j());
    write_i(read_i()+read_j());
  udon_dummy_t1_l02(i,j);

  return NULL;	
}


void *t2(void* arg)
{
  int k = 0;
  // udon_dummy_t2_l01(i,j);

    write_j(read_i()+read_j());
    write_j(read_i()+read_j());
    // udon_dummy_t2_inloop01(i,j);
    write_j(read_i()+read_j());
    write_j(read_i()+read_j());
    write_j(read_i()+read_j());
//  udon_dummy_t2_l02(i,j);




  return NULL;

}

int main(int argc, char **argv)
{
  pthread_t id1, id2;

  pthread_create(&id1, NULL, t1, NULL);
  pthread_create(&id2, NULL, t2, NULL);

  pthread_join(id1, NULL);
  pthread_join(id2, NULL);

  assert(! (i > 144 || j > 144));

  return 0;

}



