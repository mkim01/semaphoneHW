all: user.o control.o
	gcc -o control control.o
	gcc -o write user.o

user.o: user.c control.h
	gcc -c user.c control.h

control.o: control.c control.h
	gcc -c control.c

clean:
	rm output *.o *.gch
