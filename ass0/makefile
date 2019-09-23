OBJS = integer.o real.o string.o sll.o dll.o stack.o queue.o
OOPTS = -Wall -Wextra -g -c
LOPTS = -Wall -Wextra -g

all :	test-sll test-dll test-stack test-queue

test-sll : test-sll.o integer.o sll.o
	gcc $(LOPTS) test-sll.o integer.o sll.o  -o test-sll

test-dll : test-dll.o integer.o dll.o
	gcc $(LOPTS) test-dll.o integer.o dll.o -o test-dll

test-stack : test-stack.o integer.o dll.o stack.o
	gcc $(LOPTS) test-stack.o integer.o dll.o stack.o -o test-stack

test-queue : test-queue.o integer.o sll.o queue.o
	gcc $(LOPTS) test-queue.o integer.o sll.o queue.o -o test-queue

test-sll.o : test-sll.c sll.h integer.h
	gcc $(OOPTS) test-sll.c

test-dll.o : test-dll.c dll.h integer.h
	gcc $(OOPTS) test-dll.c

test-stack.o : test-stack.c stack.h integer.h
	gcc $(OOPTS) test-stack.c

test-queue.o : test-queue.c queue.h integer.h
	gcc $(OOPTS) test-queue.c

stack.o : stack.c stack.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h dll.h
	gcc $(OOPTS) queue.c


sll.o : sll.c sll.h
	gcc $(OOPTS) sll.c

dll.o : dll.c dll.h
	gcc $(OOPTS) dll.c

integer.o : integer.c integer.h
	gcc $(OOPTS) integer.c

real.o : real.c real.h
	gcc $(OOPTS) real.c

string.o : string.c string.h
	gcc $(OOPTS) string.c

valgrind  : all
	echo testing singly-linked list
	valgrind ./test-sll
	echo
	echo testing doubly-linked list
	valgrind ./test-dll
	echo
	echo testing stack
	valgrind ./test-stack
	echo
	echo testing queue
	valgrind ./test-queue
	echo

leak : all
	echo Performing detailed leak checks
	echo
	echo testing singly-linked list
	valgrind --leak-check=full ./test-sll
	echo
	echo testing doubly-linked list
	valgrind --leak-check=full ./test-dll
	echo
	echo testing stack
	valgrind --leak-check=full ./test-stack
	echo
	echo testing queue
	valgrind --leak-check=full ./test-queue
	echo

test : all
	echo testing singly-linked list
	./test-sll
	echo
	echo testing doubly-linked list
	./test-dll
	echo
	echo testing stack
	./test-stack
	echo
	echo testing queue
	./test-queue
	echo

clean :
	rm -f $(OBJS) test-*.o test-stack test-queue test-sll test-dll

clear :
	clear
	clear
