test:
	gcc -o test_code test_code.c \
	./src/ansi_port.c \
	./src/ansi.c \
	./src/nr_micro_shell.c \
	-Wall \
	-I ./inc/ \
	-D NR_MICRO_SHELL_SIMULATOR
.PHONY:clean
clean:
	rm -rf *.o test_code  .*.swp *~
