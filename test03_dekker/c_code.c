/* Testcase from Threader's distribution. For details see:
   http://www.model.in.tum.de/~popeea/research/threader
*/

#include <pthread.h>
#include <assert.h>
//#define assert(e) if (!(e)) ERROR: goto ERROR;
#define BIG 10

int flag1 = 0, flag2 = 0; // boolean flags
int turn; // integer variable to hold the ID of the thread whose turn is it
int x; // boolean variable to test mutual exclusion

/*
===========================================================================
..thr1():::ENTER
True: thread 1 sees main's init
::flag1 == ::flag2
True: thread 1 sees main's init
::flag1 == ::turn
True: thread 1 sees main's init
::flag1 == ::x
True: thread 1 sees main's init
::flag1 == 0
===========================================================================
..thr1():::EXIT
True: always set but sometimes unset
::flag1 one of { 0, 1 }
True: could be modified by thread2
::flag2 one of { 0, 1 }
True: could be modified by this thread or thread 2
::turn one of { 0, 1 }
True: could be modified by this thread or thread 2
::x one of { 0, 1 }
True: const
return == null
::flag1 <= ::flag2
::flag1 != ::turn
::flag1 >= orig(::flag1)
::flag2 >= ::x
::flag2 >= orig(::flag1)
::turn >= ::x
::turn >= orig(::flag1)
::x >= orig(::flag1)
*/
void *thr1() {
    int count1=0;
    int count2=0;
  flag1 = 1;
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
  // begin: critical section
  x = 0;
  assert(x<=0);
  // end: critical section
  turn = 1;            
  flag1 = 0;
  return NULL;
}

/*
===========================================================================
..thr2():::ENTER
True: x can only be set if thread 2 is running concurrently with thread 1
::flag2 == ::x
::flag1 one of { 0, 1 }
::flag2 == 0
::turn one of { 0, 1 }
::flag1 >= ::flag2
::flag2 <= ::turn
===========================================================================
..thr2():::EXIT
True: can finish before thread 1
::flag1 one of { 0, 1 }
::flag2 one of { 0, 1 }
::turn one of { 0, 1 }
::x one of { 0, 1 }
True: const
return == null
::flag1 >= ::flag2
::flag1 >= orig(::flag2)
::flag2 <= ::turn
::flag2 >= orig(::flag2)
::turn >= ::x
::turn >= orig(::flag2)
::turn >= orig(::turn)
::x >= orig(::flag2)
*/
void *thr2() {
  int count1=0;
  int count2=0;
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
  return NULL;
}

/*
===========================================================================
..main():::ENTER
True: init
::flag1 == ::flag2
True: init
::flag1 == ::turn
True: init
::flag1 == ::x
True: init
::flag1 == 0
===========================================================================
..main():::EXIT
True: const
return == orig(::flag1)
True: const
return == orig(::flag2)
True: const
return == orig(::turn)
True: const
return == orig(::x)
True: depending on the interleaving, each thread will either set or unset their flags
::flag1 one of { 0, 1 }
True: depending on the interleaving, each thread will either set or unset their flags
::flag2 one of { 0, 1 }
True: similar to flags
::turn one of { 0, 1 }
True: similar to flags
::x one of { 0, 1 }
True: const
return == 0
::flag1 >= return
::flag2 <= ::turn
::flag2 >= return
::turn >= ::x
::turn >= return
::x >= return
*/
int main() {
  pthread_t t1, t2;
  //__VERIFIER_assume(0<=turn && turn<=1);
  pthread_create(&t1, 0, thr1, 0);
  pthread_create(&t2, 0, thr2, 0);
  pthread_join(t1, 0);
  pthread_join(t2, 0);
  return 0;
}

/*
 * Daikon Output
 * Num Inv: 39
 * Num true: 10
 * Num false: 29
 *
===========================================================================
 ..main():::ENTER
True: init
::flag1 == ::flag2
True: init
::flag1 == ::turn
True: init
::flag1 == ::x
True: init
::flag1 == 0
===========================================================================
..main():::EXIT
False: could be either 0 or 1
::flag1 == ::flag2
False: could be either 0 or 1
::flag1 == return
False: could be either 0 or 1
::flag1 == orig(::flag1)
False: could be either 0 or 1
::flag1 == orig(::flag2)
False: could be either 0 or 1
::flag1 == orig(::turn)
False: could be either 0 or 1
::flag1 == orig(::x)
False: could be either 0 or 1
::turn == ::x
False: could be either 0 or 1
::flag1 == 0
False: could be either 0 or 1
::turn == 1
===========================================================================
..thr1():::ENTER
True: see's main init
::flag1 == ::flag2
True: see's main init
::flag1 == ::turn
True: see's main init
::flag1 == ::x
True: see's main init
::flag1 == 0
===========================================================================
..thr1():::EXIT
False: flag1 could be 1
::flag1 == ::flag2
False: flag1 could be 1 and not-equal to x (x could be zero or 1, irrespective
of flag1)
::flag1 == ::x
False: flag1 could be 1,
::flag1 == orig(::flag1)
False: flag1 could be 1,
::flag1 == orig(::flag2)
False: flag1 could be 1,
::flag1 == orig(::turn)
False: flag1 could be 1
::flag1 == orig(::x)
False: flag1 could be 1
::flag1 == 0
False: could be zero
::turn == 1
True: const
return == null
===========================================================================
..thr2():::ENTER
False: flag1 could be 1
::flag1 == ::flag2
False: flag1 could be 1
::flag1 == ::x
False: flag1 could be 1
::flag1 == 0
False: could be zero
::turn == 1
===========================================================================
..thr2():::EXIT
False: could be zero or one
::flag1 == ::flag2
False: could be zero or one
::flag1 == orig(::flag1)
False: could be zero or one
::flag1 == orig(::flag2)
False: could be zero or one
::flag1 == orig(::x)
False: could be zero or one
::turn == ::x
False: could be zero or one
::turn == orig(::turn)
False: could be zero or one
::flag1 == 0
False: could be zero or one
::turn == 1
True: const
return == null
*/
