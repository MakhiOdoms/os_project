all:
	gcc -pthread threadpool.c client.c -o threadpool

run:
	./threadpool