/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader
*/

#include <pthread.h>
#include <assert.h>
#include <stdio.h>
#include <stdbool.h>
//#define assert(e) if (!(e)) ERROR: goto ERROR;
#define BIG 10

int flag1 = 0, flag2 = 0; // boolean flags
int opu_flag2 = flag2,opu_flag1 = flag1,mjo;
int turn; // integer variable to hold the ID of the thread whose turn is it
int opu_turn = turn,mjo;
int x; // boolean variable to test mutual exclusion
int opu_x = x,mjo;
bool cond = true;



void okay_dummy_f3(int count1, int count2)
{
int opu_count1 = count1, tmptmp;
int opu_count2 = count2;
  if (flag2 >= 1) {
    if(count1++>BIG) return;
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) { 
        if(count2++>BIG) return;
      }
      flag1 = 1;
    }
    if (!(flag2 >= 1)) {cond = false;} 
  }
  if (cond) {
    if(count1++>BIG) return ;
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) { 
        if(count2++>BIG) return;
      }
      flag1 = 1;
    }
    if (!(flag2 >= 1)) {cond = false;} 
  }

//tmptmp=flag2;
//assert(tmptmp==0 || tmptmp==1);
  __CPROVER_atomic_begin0:
assert(flag2 ==0 || flag2 ==1 );
__CPROVER_atomic_end0: ;
//assert(flag2==0);
 // assert(flag2<2 && flag2>=0);


}



void okay_dummy_f2(int count1, int count2)
{
int opu_count1 = count1;
int opu_count2 = count2;
  okay_dummy_f3(count1, count2);

  if (cond) {
    if(count1++>BIG) return;
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) { 
        if(count2++>BIG) return;
      }
      flag1 = 1;
    }
    if (!(flag2 >= 1)) {cond = false;} 

  }
  if (flag2 >= 1) {
    if(count1++>BIG) return;
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) { 
        if(count2++>BIG) return;
      }
      flag1 = 1;
    }
    if (!(flag2 >= 1)) {cond = false;} 
  }

}


void okay_dummy_f1(int count1, int count2)
{
int opu_count1 = count1;
int opu_count2 = count2;
  okay_dummy_f2(count1, count2);
  
  while (cond) {
    if(count1++>BIG) return ;
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) { 
        if(count2++>BIG) return ;
      }
      flag1 = 1;
    }
    if (!(flag2 >= 1)) {cond = false;} 
  }

}




void *thr1() {
  int count1=0;
  int count2=0;
int opu_count2 = count2,mjo;
  flag1 = 1;
  okay_dummy_f1(count1, count2);
  /*
    //Replace this part with a function

  while (flag2 >= 1) {
    if(count1++>BIG) return NULL;
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) { 
         if(count2++>BIG) return NULL;
     }
     flag1 = 1;
 }
}

*/
  // begin: critical section
  x = 0;
  //assert(x<=0);
  // end: critical section
  turn = 1;            
  flag1 = 0;
  return NULL;
}



void *thr2() {
  int count1=0;
  int count2=0;
int opu_count2 = count2,mjo;
  flag2 = 1;
  while (flag1 >= 1) {
    if(count1++>BIG) return NULL;
    if (turn != 1) {
      flag2 = 0;
      while (turn != 1) {
       if(count2++>BIG) return NULL;
     }
     flag2 = 1;
   }
 }
  // begin: critical section
 x = 1;
 // assert(x>=1);
  // end: critical section
 turn = 1;
 flag2 = 0;
 return NULL;
}


int main() {
  pthread_t t1, t2;
  //__VERIFIER_assume(0<=turn && turn<=1);
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  return 0;
}
