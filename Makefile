# -*- Makefile -*-

CC = gcc #compiler 

CFLAGS = -Wall -g  #compiler flags

OBJFLAGS =  -c -fPIC -Wall -I ./includes/ #compiler flags for library

BINARIES = main test cmocka

LIBS = -L./cmocka-1.1.5/build/src -lcmocka 

all : main.o params.o matlib.so
	$(CC) $(CFLAGS) -o main src/main.c src/params.c  matlib.so

test: test_all_matrix_library.o matrix_test.o matlib.so 
	$(CC) $(CFLAGS) -o test tests/test_all_matrix_library.c tests/matrix_test.c matlib.so

cmocka : cmocka_unit_tests.o matlib.so
	$(CC) $(LIBS) -o cmocka tests/cmocka_unit_tests.c matlib.so

matlib.so: matrix.o help.o error.o list.o 
	$(CC) -shared -o matlib.so src/matrix.c src/help.c src/error.c src/list.c 

cmocka_unit_tests.o: tests/cmocka_unit_tests.c
	$(CC) -I/cmocka-1.1.5/include -c tests/cmocka_unit_tests.c

test_all_matrix_library.o: tests/test_all_matrix_library.c
	$(CC) -c tests/test_all_matrix_library.c

matrix_test.o: tests/matrix_test.c
	$(CC) -c tests/matrix_test.c
	
main.o: src/main.c
	$(CC) -c src/main.c

params.o: src/params.c
	$(CC) -c src/params.c 

matrix.o: src/matrix.c
	$(CC) $(OBJFLAGS) src/matrix.c 

help.o: src/help.c
	$(CC) $(OBJFLAGS) src/help.c
	
error.o: src/error.c
	$(CC) $(OBJFLAGS) src/error.c
	
list.o: src/list.c
	$(CC) $(OBJFLAGS) src/list.c

.PHONY: clean
clean:
	-rm -f *.o *.so $(BINARIES) 
