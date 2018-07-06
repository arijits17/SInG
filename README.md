# SInG
Experiment on Sound Invariant Generation in Concurrent Programs.


The folder names starting with `test_` contains different testcases.
- Inside the folder, the file `c_code.c` is the initial code which is the unwinding of main code named `main.c`. 
- The file `daikon_result` is the listing of udon generated invarints.
- The file `new_c_code.c` is instrumented C code that contains the invarints as assertions. This is given to CBMC for verificaation.
