test:
	gcc func.c -o func.o -c -fPIC
	gcc -o libfunc.so func.o -shared
.PHONY:clean
clean:
	rm -rf *.o libfunc.so .*.swp *~
