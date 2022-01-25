test:
	gcc -o test_code test_code.c func_wrap.c -Wall -I./ -L./lib -lfunc -Wl,--rpath=./lib
.PHONY:clean
clean:
	rm -rf *.o test_code  .*.swp *~
