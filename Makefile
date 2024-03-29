CC   = cc
OBJS = DoubleLL.o bitwise_f.o font-12x8.o

CFLAGS = -I./h -O3 -g3 -Wall -Wextra -Werror=format-security -Werror=implicit-function-declaration \
         -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Wconversion

all: main

%.o: %.c
	${CC} $(CFLAGS) -c -o $@ $<

main: $(OBJS) main.o
	${CC} -o $@ $^

run: main
	./main

clean:
	rm -f *.o main

DoubleLL.o: DoubleLL.c DoubleLL.h
bitwise_f.o: bitwise_f.c bitwise_f.h font-12x8.o
font-12x8.o: font-12x8.c
main.o: main.c DoubleLL.h bitwise_f.h

