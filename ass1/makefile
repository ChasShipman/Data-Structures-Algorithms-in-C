OBJS = integer.o real.o string.o sll.o dll.o stack.o queue.o bst.o heap.o heapsort.o scanner.o
OOPTS = -Wall -Wextra -std=c99 -g -c
LOPTS = -Wall -Wextra -std=c99 -g

all :	heapsort #test-heap test-bst test-sll test-dll test-stack test-queue

test-sll : test-sll.o integer.o real.o string.o sll.o
	gcc $(LOPTS) test-sll.o integer.o real.o string.o sll.o -o test-sll

test-dll : test-dll.o integer.o real.o string.o dll.o
	gcc $(LOPTS) test-dll.o integer.o real.o string.o dll.o -o test-dll

test-stack : test-stack.o integer.o real.o string.o dll.o stack.o
	gcc $(LOPTS) test-stack.o integer.o real.o string.o dll.o stack.o -o test-stack

test-queue : test-queue.o integer.o real.o string.o sll.o queue.o
	gcc $(LOPTS) test-queue.o integer.o real.o string.o sll.o queue.o -o test-queue

test-bst : test-bst.o integer.o real.o string.o bst.o sll.o queue.o
	gcc $(LOPTS) test-bst.o integer.o real.o string.o bst.o sll.o queue.o -o test-bst

test-heap : test-heap.o integer.o real.o string.o heap.o bst.o sll.o dll.o queue.o stack.o
	gcc $(LOPTS) test-heap.o integer.o real.o string.o heap.o bst.o sll.o dll.o queue.o stack.o -o test-heap

heapsort : heapsort.o integer.o real.o string.o heap.o bst.o scanner.o sll.o dll.o queue.o stack.o
	gcc $(LOPTS) heapsort.o integer.o real.o string.o heap.o bst.o scanner.o sll.o dll.o queue.o stack.o -o heapsort

test-sll.o : test-sll.c sll.h integer.h real.h string.h
	gcc $(OOPTS) test-sll.c

test-dll.o : test-dll.c dll.h integer.h real.h string.h
	gcc $(OOPTS) test-dll.c

test-stack.o : test-stack.c stack.h integer.h real.h string.h
	gcc $(OOPTS) test-stack.c

test-queue.o : test-queue.c sll.h queue.h integer.h real.h string.h
	gcc $(OOPTS) test-queue.c

test-bst.o : test-bst.c queue.h bst.h integer.h real.h string.h
	gcc $(OOPTS) test-bst.c

test-heap.o : test-heap.c queue.h stack.h bst.h integer.h real.h string.h
	gcc $(OOPTS) test-heap.c

heap.o : heap.c heap.h bst.h queue.h stack.h
	gcc $(OOPTS) heap.c

bst.o	: bst.c bst.h queue.h
	gcc $(OOPTS) bst.c

stack.o : stack.c stack.h dll.h
	gcc $(OOPTS) stack.c

queue.o : queue.c queue.h sll.h
	gcc $(OOPTS) queue.c

heapsort.o : heapsort.c heap.h bst.h queue.h integer.h string.h real.h 
	gcc $(OOPTS) heapsort.c

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

scanner.o : scanner.c scanner.h
	gcc $(OOPTS) scanner.c

valgrind  : all
	echo testing heapsort
	valgrind ./heapsort file
	echo testing heap
	#valgrind ./test-heap
	#echo testing bst
	#valgrind ./test-bst
#	echo testing singly-linked list
#	valgrind ./test-sll
#	echo
#	echo testing doubly-linked list
#	valgrind ./test-dll
#	echo
#	echo testing stack
#	valgrind ./test-stack
#	echo
#	echo testing queue
#	valgrind ./test-queue
#	echo

leak : all
	echo detailed leak check
	valgrind --leak-check = full ./heapsort file
	#valgrind --leak-check=full ./test-heap
	#echo detailed leak check
	#valgrind --leak-check=full ./test-bst
#	echo Performing detailed leak checks
#	echo
#	echo testing singly-linked list
#	valgrind --leak-check=full ./test-sll
#	echo
#	echo testing doubly-linked list
#	valgrind --leak-check=full ./test-dll
#	echo
#	echo testing stack
#	valgrind --leak-check=full ./test-stack
#	echo
#	echo testing queue
#	valgrind --leak-check=full ./test-queue
#	echo

test : all
	echo testing heap
	./heapsort file
#	test-heap
#	echo testing bst
#	./test-bst
#	echo testing singly-linked list
#	./test-sll
#	echo
#	echo testing doubly-linked list
#	./test-dll
#	echo
#	echo testing stack
#	./test-stack
#	echo
#	echo testing queue
#	./test-queue
#	echo

clean :
	rm -f $(OBJS) test-*.o test-stack test-queue test-sll test-dll test-bst test-heap heapsort 

clear :
	clear
	clear
