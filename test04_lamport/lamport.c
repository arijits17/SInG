//extern void __VERIFIER_error() __attribute__ ((__noreturn__));

#include <pthread.h>
#include <assert.h>
//#define assert(e) { if(!(e)) { ERROR: __VERIFIER_error();(void)0; } }

int x;
int y;
int b1, b2; // N boolean flags
int X; //variable to test mutual exclusion
int udon_dummy_t1_l01(int a, int b, int c, int d, int e ){return 0;}


void* thr1(void* arg) {
  while (1) {
    b1 = 1;
    x = 1;
    if (y != 0) {
      b1 = 0;
      while (y != 0) {};
      continue;
    }
    y = 1;
    if (x != 1) {
      b1 = 0;
      while (b2 >= 1) {};
      if (y != 1) {
	while (y != 0) {};
	continue;
      }
    }
    break;
  }
  // begin: critical section
  X = 0;
  //assert(X <= 0);
  // end: critical section
  y = 0;
  b1 = 0;

  return 0;
}

void* thr2(void* arg) {
  while (1) {
    b2 = 1;
    x = 2;
    if (y != 0) {
      b2 = 0;
      while (y != 0) {};
      udon_dummy_t1_l01(x,y,b1,b2,X);

      continue;
    }

    y = 2;
    if (x != 2) {
      b2 = 0;
      while (b1 >= 1) {};
      if (y != 2) {
	while (y != 0) {};
	continue;
      }
    }
    break;
  }
  // begin: critical section
  X = 1;
  //assert(X >= 1);
  // end: critical section
  y = 0;
  b2 = 0;

  return 0;
}



int main()
{
  pthread_t t;

  pthread_create(&t, 0, thr1, 0);
  thr2(0);

  return 0;
}

/*
int main()
{
  pthread_t t1, t2;

  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);

  pthread_join(t1, 0);
  pthread_join(t2, 0);
  // thr2(0);

  return 0;
}

*/