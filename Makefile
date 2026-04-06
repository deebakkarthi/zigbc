MAKEFLAGS += -r
CC = gcc-15

.PHONY: clean all
.DEFAULT: all

%: %.o mtrace.o
	#${CC}  $< mtrace.o -ldl -o $@
	${CC}  $< -o $@

mtrace.o: mtrace.c
	${CC} -c $< -o $@

%.o: %.c
	${CC}  -c $< -o $@

all:

clean:
	find . -depth -maxdepth 1 -type f -executable -exec rm {} \;
	rm -rf *.o
