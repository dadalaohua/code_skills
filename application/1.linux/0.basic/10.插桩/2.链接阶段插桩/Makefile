test:
	gcc -o test_code test_code.c func_wrap.c -Wall -I./lib -L./lib -lfunc -Wl,--rpath=./lib -Wl,--wrap,magicfunc
.PHONY:clean
clean:
	rm -rf *.o test_code  .*.swp *~
