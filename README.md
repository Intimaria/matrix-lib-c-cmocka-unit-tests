# Welcome to Matrix Library App
=============================

C Language


_Author - Inti Tidball 2020/2021 for C Language Seminar, UNLP_

# Sections:

- [Using the Program](#using-the-program)

- [How to format your files](#file-formatting)

- [How to compile](#compiling-the-program-on-your-terminal)

- [Debugging](#debugging)

- [Operating with Matrices](#operations-between-matrices)



## Using the program 

This is a program to operate with float/double 
value matrices mathematically.

Matrices are read from files. The files are written with
a special format.

In order to use this program you must input at  
least one input file, one operation instruction, and one file for output. 
Add two input files for operations between two matrices.

## File formatting

_The following is a descripcion of the format you must use in your matrix file_

*first line* : M1 or M2, this is  the format of matrix (M1 is ASCII, M2 is binary)

*second line* : comments are preceded by a # (numeral)

*third line* : Dimensions: int values indicating ROW and COLUMN size of matrix

*fourth or more lines* : the data values, these may be ASCII or binary,
and they can be stored formatted as a matrix or as a single array. 

Example:

```
M1 
# this is a comment  
2 3 
1.2 4.5 6.5  
5.6 4.3 3.4  
```

## Compiling the program on your terminal

To compile the main program:

```
make clean 
make 
./main (args)
```

If you would like to compile tests with assert:

```
make clean 
make test
./test 
```

If you would like to compile tests with cmocka:
(must install cmocka first, please see docs/documentation.md for more info)
```
make clean 
make cmocka
./test 
```
## Debugging 

In valgrind:

`valgrind --leak-check=full -v ./main (args) [or ./test] `

debugging in gdb:

`gdb --args ./main [or ./test]`

then when in gbd type:

`(gdb) run`


Operations between matrices 
==================================================== 

If you would like to use a menu from terminal instead of running the instructions yourself,
please run the bash script included with the program. 

```
./run.sh
```

Always execute ` make ` before doing so, 
or it will not work.

Otherwise, follow the instructions below.

### The following are input and output file instructions: 

Generic instruction format is: [--in1 FILE --in2 FILE --op OP --o FILE]
further details below.

*Input file 1*: 
Receives first matrix. Use the operator `-1` or `--in1`, then file name; for instance "matrix1.txt". 

`[-1 | --in1]  [FILE 1 location/name]`

*Input file 2*: 
If necessary, receives second matrix. Use the operator `-2` or `--in2`, then file name; for instance "matrix2.txt".

`[-2 | --in2]  [FILE 2 location/name]`

*Output*: 
Writes resulting matrix to file. Use the operator `-o` or `--out`, then file name; for instance "Result.txt".

 `[-o | --out]  [FILE out location/name]`
 

### The following are valid operations: 

*dup*: Duplicate a matrix.	
```[-p | --op]  [dup]```

*trans*: Transpose a matrix.	
```[-p | --op]  [trans]```

*null*: Creates a null matrix (uses the row and column value of input file). 	
```[-p | --op]  [null]```

*idty*: Creates an identity matrix (uses the column value of input file). 		
```[-p | --op]  [idty]```
 

*mult_scalar*: Multiply a matrix by a scalar value.
```[-p | --op]  [mult_scalar] [-s | --scalar] [double value]```	


*cmp*: Compares a matrix with another. Requires two input files.	
```[-p | --op]  [cmp]```


*mult or sum*:Multiply or sum two matrices. Requires two input files and compatible matrixes. 
```[-p | --op]  [mult | sum]```	



### Examples of valid input :

```
[--in1 file_in_1] [--op operation type] [--out file_out]
(optional..) [--in2 file_in_2]
```

for duplicating, transposing, creating null or identity matrix:
```
[--in1|-1  file_in_1] [--op|-p dup|trans|null|idty] [--out|-o file_out]
```

for multiplication by scalar value:
```
[--in1|-1  file_in_1] [--op|-p mult_scalar] [--scalar|-s value] [--out|-o file_out]
```

for multiplying, summing or comparing two matrixes, use two input files:
```
[--in1|-1  file_in_1] [--op|-p mult|sum|cmp] [--in2|-2 file_in_2] [--out|-o file_out]
```

*WARNING*: Matrixes must be compatible 
in size in order to be multipled or added.

For multiplication, ensure that Matrix A is 
`rows:N by columns:M` whereas Matrix B is `rows:M by columns:H`.
The resulting Matrix C will be of size `rows:N by columns:H`.

In other words, the first matrix __must__ have a column size __equal__ 
to the second matrix's row size, (order is important here). 
The resulting matrix will have a row size which equal to the first matrix's, 
and a column size equal to the second matrix's. 

For sums ensure that Matrix A is equal in size to Matrix B: `rows:N by cols:M`.
The resulting Matrix C will be of the same size `rows:N by cols:M`.

