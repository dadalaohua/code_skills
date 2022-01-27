test:
	gcc -o test_code test_code.c efsmt.c ./state_startup/*.c ./state_online/*.c ./state_offline/*.c -I./  -lpthread -Wall
.PHONY:clean
clean:
	rm -rf *.o test_code  .*.swp *~
