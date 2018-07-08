# SInG
Experiment on Sound Invariant Generation in Concurrent Programs.


The folder names starting with `test_` contains different testcases.
- Inside the folder, the file `c_code.c` is the initial code which is the instrumented version on unwinding of main code named `main.c`. This instrumentation makes the `c_code.c` able to generate invariants at different places or block of `main.c`.
- The file `daikon_result` is the listing of udon generated invarints.
- The file `new_c_code.c` is instrumented C code that contains the invarints as assertions. This is given to CBMC for verification.

We tried to instrument the code so that we get transition invariants at different part of code. The main code has gone through unwindings or broken into blocks for this.

The python code `instrumentor.py` is the tool to instrument the original code with udon invariants. `friend.py` is a header to this.
