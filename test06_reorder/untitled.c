/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader
*/

#include <pthread.h>
#include <assert.h>
#include <stdio.h>
//#define assert(e) if (!(e)) ERROR: goto ERROR;
#define BIG 10

int flag1 = 0, flag2 = 0; // boolean flags
int opu_flag2 = flag2,opu_flag1 = flag1,mjo;
int turn; // integer variable to hold the ID of the thread whose turn is it
int opu_turn = turn,mjo;
int x; // boolean variable to test mutual exclusion
int opu_x = x,mjo;


void okay_dummy_f3(int count1, int count2)
{
assert(turn <= count1);
assert(flag2 <= count1);
assert(flag2 >= turn);
assert(flag1 >= flag2);
assert(flag2 ==0 || flag2 ==1 );
assert(turn == count2);
assert(turn == x);
  printf("Maahi maar raha hyay\n");
int opu_count1 = count1;
int opu_count2 = count2;
  while (flag2 >= 1) {
    if(count1++>BIG) return ;
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) { 
        if(count2++>BIG) return ;
      }
      flag1 = 1;
    }
  }
assert(turn <= opu_count1);
assert(turn <= opu_flag2);
assert(flag2 >= turn);
assert(flag1 >= opu_flag2);
assert(flag1 >= flag2);
assert(flag2 ==0 || flag2 ==1 );
assert(turn == opu_count2);
assert(turn == opu_x);
assert(turn == opu_turn);
assert(turn == x);
assert(flag1 == opu_flag1);

}





void okay_dummy_f2(int count1, int count2)
{
assert(turn <= count1);
assert(flag2 <= count1);
assert(flag2 >= turn);
assert(flag1 >= flag2);
assert(count1 ==0 || count1 ==1 || count1 ==2 );
assert(flag2 ==0 || flag2 ==1 );
assert(turn == count2);
assert(turn == x);
  if (flag2 >= 1) {
int opu_count1 = count1;
int opu_count2 = count2;
    if(count1++>BIG) return;
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) { 
        if(count2++>BIG) return;
      }
      flag1 = 1;
    }
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
  }

assert(turn <= opu_count1);
assert(turn <= opu_flag2);
assert(flag2 >= turn);
assert(flag1 >= opu_flag2);
assert(flag1 >= flag2);
assert(flag2 ==0 || flag2 ==1 );
assert(turn == opu_count2);
assert(turn == opu_x);
assert(turn == opu_turn);
assert(turn == x);
assert(flag1 == opu_flag1);
  okay_dummy_f3(count1, count2);
}


void okay_dummy_f1(int count1, int count2)
{
assert(flag2 >= turn);
assert(flag1 >= flag2);
assert(flag2 ==0 || flag2 ==1 );
assert(turn == count2);
assert(turn == count1);
assert(turn == x);
  if (flag2 >= 1) {
int opu_count1 = count1;
int opu_count2 = count2;

    if(count1++>BIG) return;
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) { 
        if(count2++>BIG) return;
      }
      flag1 = 1;
    }
  }
  if (flag2 >= 1) {
    if(count1++>BIG) return ;
    if (turn != 0) {
      flag1 = 0;
      while (turn != 0) { 
        if(count2++>BIG) return;
      }
      flag1 = 1;
    }
  }

  okay_dummy_f2(count1, count2);

assert(turn <= opu_flag2);
assert(flag2 >= opu_flag2);
assert(flag2 >= turn);
assert(flag1 >= opu_flag2);
assert(flag1 >= flag2);
assert(flag2 ==0 || flag2 ==1 );
assert(turn == opu_count2);
assert(turn == opu_count1);
assert(turn == opu_x);
assert(turn == opu_turn);
assert(turn == x);
assert(flag1 == opu_flag1);

}



void *thr1() 
{
assert(flag1 == x);
assert(flag1 == turn);
assert(flag1 == flag2);
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
assert(turn >= x);
assert(flag2 >= x);
assert(flag2 <= turn);
assert(flag1 <= x);
assert(flag1 <= flag2);
assert(x ==0 || x ==1 );
assert(flag2 ==0 || flag2 ==1 );
assert(flag1 == opu_x);
assert(flag1 == opu_turn);
assert(flag1 == opu_flag2);
assert(flag1 == opu_flag1);
  return NULL;
}



void *thr2()
 {
assert(flag2 <= turn);
assert(flag1 >= flag2);
assert(turn ==0 || turn ==1 );
assert(flag1 ==0 || flag1 ==1 );
assert(flag2 == x);
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
 assert(x>=1);
  // end: critical section
 turn = 1;
 flag2 = 0;
assert(x >= opu_flag2);
assert(turn >= opu_turn);
assert(turn >= opu_flag2);
assert(turn >= x);
assert(flag2 >= opu_flag2);
assert(flag2 <= opu_flag1);
assert(flag2 <= turn);
assert(flag1 >= opu_flag2);
assert(flag1 <= opu_flag1);
assert(flag1 != x);
assert(flag1 >= flag2);
assert(x ==0 || x ==1 );
assert(turn ==0 || turn ==1 );
assert(flag2 ==0 || flag2 ==1 );
assert(flag1 ==0 || flag1 ==1 );
 return NULL;
}


int main() 
{
assert(flag1 == x);
assert(flag1 == turn);
assert(flag1 == flag2);
  pthread_t t1, t2;
  //__VERIFIER_assume(0<=turn && turn<=1);
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
assert(turn >= x);
assert(flag2 <= turn);
assert(flag1 <= x);
assert(flag1 <= flag2);
assert(x ==0 || x ==1 );
assert(flag2 ==0 || flag2 ==1 );
assert(flag1 == opu_x);
assert(flag1 == opu_turn);
assert(flag1 == opu_flag2);
assert(flag1 == opu_flag1);
  return 0;
}
