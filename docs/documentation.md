# **DOCUMENTATION**

## Making a dynamic library 

Following this [guide](https://www.cs-fundamentals.com/c-programming/static-and-dynamic-linking-in-c)

First of all, run these commands: 
```
gcc -I . -c -fPIC src/matrix.c -Wall
gcc -I . -c -fPIC src/error.c -Wall
gcc -I . -c -fPIC src/help.c -Wall
gcc -I . -c -fPIC src/list.c -Wall
gcc -shared -o matlib.so matrix.o help.o list.o
```
- -I tells the linker to look for the header files in . directory
- -c creates object files 
- -o links the object files
- see fPIC & other options: 
https://gcc.gnu.org/onlinedocs/gcc/Code-Gen-Options.html

To compile or recompile only the .so, run `make matlib.so` and
copy the library matlib.so into /usr/lib 
and run `sudo ldconfig` 
(must do this everytime you recompile the dyamic lib)

Then run `make` which consists of the following:
```
gcc -c src/main.c src/params.c 
gcc -o main main.o params.o matlib.so
```
* to see library dependencies run `ldd main`.

**After testing this works locally.
Makefile calls dynamic library in the local directory for now for portability. 

Running any of the ```make``` options will compile the library automatically.


## Using assert.h to unit test

Developing tests for each function in the library. Each function is 
tested using null matrixes (should fail), small matrixes and large
matrixes, incompatible matrixes for functions with two inputs and 
other edge cases.

Each set of tests for a function has it's own file. There is one 
master header file with which you can call all the different tests
which is contemplated in the Makefile ('make test') or if you want
you can test each function individually. 

Assert library is used in this manner: 
```
all_test_definitions.c 
bool test_my_function(mystruct_t *m, size_t n, double d){
	if ((e = my_function(&m, m1, n, n, d)) == E_OK){
	return true;
	}
	error_help(stderr, e);
	return false;
}
----
all_test_declarations.h 
bool test_sum_matrix(matrix_t *m1, matrix_t *m2);
----
call_my_unit_test.c
assert (test_my_function(&first_input, num1, num2) && "my function error");	
----
call_all_my_unit_tests.c 
assert (test_my_function_ONE(&first_input, num1, num2) && "my function error");	
assert (test_my_function_TWO(&first_input, num1, num2) && "my function error");
....	
assert (test_my_function_N(&first_input, num1, num2) && "my function error");	
```

## Using CMOCKA

Using [this tutorial](https://www.wfbsoftware.de/c-unit-testing-with-cmocka/)

The tar file is included in the main directory.

The tests are contained in a single file.
It contains the obligatory inserts for cmocka, plus the library header files. 
Defined Set up & Tear down for groups and for individual tests. 
Created a helper function to create generic matrixes.
Defined a main which calls the tests & defines the tests.

Compilation (assumes cmocka-5.1.1 folder is in same directory - again for portability)
```
tar xz cmocka-1.1.5
cd cmocka-1.1.5
mkdir build 
cd build 
cmake -DCMAKE_INSTALL_PREFIX=/usr -DCMAKE_BUILD_TYPE=Debug ..
make
sudo make install
```
After that all is cool!

Run the following to compile (this has been added to makefile)
``` 
gcc -c tests_cmocka.c -I/cmocka-1.1.5/include
gcc -c src/matrix.c
gcc -c src/list.c
gcc -c src/help.c
gcc -c src/error.c
gcc -L./cmocka-1.1.5/build/src -o cmocka ./cmocka_unit_tests.o ./matrix.o ./help.o ./list.o -lcmocka
```

You may run ```make cmocka``` if installing cmocka from within the local directory.
Otherwise you will have to compile in the commandline, or modify the makefile 
accordingly. 
At the moment this isn't working cross platform unfortunately,
because it installs differently in different platforms and I did not have time to optimise this. 

You will need to change lines 11 & 26 in the makefile to reflect where the library is installed in your system.


**TODO**  
- write more tests including more edge cases 

**OPTIMIZATION**
- Make generic, define data_t type, change pointers to void (etc). Make sure to include list, etc. Unlikely for now.

**DONE**
- cmocka unit tests in ./tests/ updated Makefile, use `make cmocka`
- added shared object library into makefile 
- made dynamic library & linked
- updated directory structure to one which is consistent to c standard libraries as per [pitchfork project](https://api.csswg.org/bikeshed/?force=1&url=https://raw.githubusercontent.com/vector-of-bool/pitchfork/develop/data/spec.bs). 
- changed all double pointers to single pointers and fixed inconsistencioes throughout project. 
- fixed error issues - now all errors in stdout are accurate & friendly to user. 
- assign all pointers to NULL after freeing, which corrected some errors.
- fixed some memory allocation redundancies in matrix functions. 
- refactored code to move all parameter parsing out of main and into params.c. 
- fixed some issues with file handling in params which fixed some memory bugs
- run style conventions on the code 
- updated the comments to meet standards
- changed names to make them more compliant to naming standards and easy to read
- used the Assert library to create tests for all functions including timing time complexity of mult function 
- There is error checking in main if input is in unimplemented files format, with correct valgrind performance. 
- Finished making binary read and write functions as expected for M2 format.
- Files -> at first I read matrices in1 and in2 while parsing, I have now moved all read & write matrix calls to main. I only send the matrices already read, and I send read matrixes to "sort and call" function. I now call write matrix after "sort and call" function in main. 
- Added allocate matrix and free matrix in matrix.c as separate functions.
- Checked strncasecmp() function in params.c. Reverted to strncmp() as is not cross-platform. 
- Comprehensive help message in main 
- Modularized parameter validation in params.c and params.h
- modularized op sorting and flag setting into params.h
- Create Makefile 
