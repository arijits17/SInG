/*
 * See the bottom of this file for the result of running daikon on this
 * example. Note: the result are non-determinate!
 */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


static int iSet = 2;
static int iCheck = 2;

static int a = 0;
static int b = 0;

void *setThread(void *param);
void *checkThread(void *param);
void set();
int check();


void *checkThread(void *param) {
    if(a == 1 & b == -1) {
        assert(1);
    }
    return NULL;
}


void *setThread(void *param) {
    a = 1;
    b = -1;

    return NULL;
}



int main(int argc, char *argv[]) {
    int i, err;

    pthread_t setPool[iSet];
    pthread_t checkPool[iCheck];

    for (i = 0; i < iSet; i++) {
        if (0 != (err = pthread_create(&setPool[i], NULL, &setThread, NULL))) {
            fprintf(stderr, "Error [%d] found creating set thread.\n", err);
        }
    }

    for (i = 0; i < iCheck; i++) {
        if (0 != (err = pthread_create(&checkPool[i], NULL, &checkThread,
                                       NULL))) {
            fprintf(stderr, "Error [%d] found creating check thread.\n", err);
        }
    }

    for (i = 0; i < iSet; i++) {
        if (0 != (err = pthread_join(setPool[i], NULL))) {
            fprintf(stderr, "pthread join error: %d\n", err);
        }
    }

    for (i = 0; i < iCheck; i++) {
        if (0 != (err = pthread_join(checkPool[i], NULL))) {
            fprintf(stderr, "pthread join error: %d\n", err);
        }
    }

    return 0;
}
        
/*
===========================================================================
..setThread():::ENTER
iSet and iCheck are never modified
::iSet == ::iCheck
initially, a and b are both zero
::a == ::b
::iSet == 2
::a == 0
function is always passed NULL
param == null
===========================================================================
..setThread():::EXIT
::iSet == ::iCheck
::iSet == orig(::iSet)
::iSet == orig(::iCheck)
returns NULL always
return == orig(param)
::iSet == 2
a and b are both set 
::a == 1
::b == -1
return == null
*/

/*
 *
===========================================================================
..checkThread():::ENTER
::iSet == ::iCheck
::iSet == 2
Depending on if setThread runs first a or b will be either 0 or one of these values
::a one of { 0, 1 }
::b one of { -1, 0 }
always called with null
param == null
true. iSet is 2
::iSet > ::a
::iSet > ::b
::a >= ::b
===========================================================================
..checkThread():::EXIT
iset and check are constant in this function
::iSet == ::iCheck
::iSet == orig(::iSet)
::iSet == orig(::iCheck)
always retuns null
return == orig(param)
::iSet == 2
::a one of { 0, 1 }
::b one of { -1, 0 }
return == null
True, iSet is 2
::iSet > ::a
::iSet > ::b
::iSet > orig(::a)
::iSet > orig(::b)
::a >= ::b
::a >= orig(::a)
::a >= orig(::b)
::b <= orig(::a)
::b <= orig(::b)
*/

/*
 * Daikon output
 * Number of invariants: 48
 * Number of false invariants: 8
 * Number of correct invariants: 40
===========================================================================    
..checkThread():::ENTER
True: these are constants
::iSet == ::iCheck
True: constant
::iSet == 2
False: a can either be 0 or 1 depending on if setThread() runs first
::a == 1
False: b can either be 0 or 1 depending on if setThread() runs first
::b == -1
True: param is always NULL
param == null
===========================================================================
..checkThread():::EXIT
True: const
::iSet == ::iCheck
True: const
::iSet == orig(::iSet)
True: const
::iSet == orig(::iCheck)
False: setThread can modify the valaue of `a` during this function
::a == orig(::a)
False: setThread can modify the valaue of `b` during this function
::b == orig(::b)
True: return is always NULL
return == orig(param)
True: const
::iSet == 2
False: could be either 0 or 1
::a == 1
False: could be either 0 or -1
::b == -1
True: always returns NULL
return == null
===========================================================================
..main():::ENTER
True: const
::iSet == ::iCheck
True: initialized to zero
::a == ::b
True; initialized
::iSet == 2
True: initialized
::a == 0
True: 
argc == 1
True: 
argv has only one value
===========================================================================
..main():::EXIT
True: const
::iSet == ::iCheck
True: const
::iSet == orig(::iSet)
True: const
::iSet == orig(::iCheck)
True, a is set to 1
::a == orig(argc)
True: returns 0
return == orig(::a)
True: returns 0
return == orig(::b)
True: const
::iSet == 2
True: setThread()
::a == 1
True: setThread()
::b == -1
True: const
return == 0
===========================================================================
..setThread():::ENTER
::iSet == ::iCheck
::iSet == 2
False: should always be zero
::a one of { 0, 1 }
False: should always be zero
::b one of { -1, 0 }
True: const
param == null
===========================================================================
..setThread():::EXIT
True: const
::iSet == ::iCheck
True: const
::iSet == orig(::iSet)
True: const
::iSet == orig(::iCheck)
True: const
return == orig(param)
True: const
::iSet == 2
True: set by thread
::a == 1
True: set by thread
::b == -1
True: const
return == null
*/