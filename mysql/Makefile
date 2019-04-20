a.out: int_main.o
	gcc int_main.o -lmysqlclient -o a.out

int_main.o: int_main.c
	gcc -g -c -Wall -I/usr/include/mysql int_main.c 

clean:
	rm -rf *.o
	rm -rf a.out
