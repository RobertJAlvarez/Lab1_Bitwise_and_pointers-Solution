CC   = cc
MY_OBJS = my_DoubleLL.o my_bitwise_f.o my_font-12x8.o
S_OBJS = ./o/DoubleLL.o ./o/bitwise_f.o ./o/font-12x8.o

CFLAGS = -I./h -O3 -g3 -Wall -Wextra -Werror=format-security -Werror=implicit-function-declaration \
         -Wshadow -Wpointer-arith -Wcast-align -Wstrict-prototypes -Wwrite-strings -Wconversion

all: main

%.o: %.c
	${CC} $(CFLAGS) -c -o $@ $<

main: $(MY_OBJS) my_main.o
	${CC} -o $@ $^

test: $(MY_OBJS) $(S_OBJS) test.o
	${CC} -o $@ $^

run: main
	./main

clean:
	(cd student && make clean)
	rm -rf ./h
	rm -rf ./o
	rm -f *.o main test

my_DoubleLL.o: my_DoubleLL.c my_DoubleLL.h
my_bitwise_f.o: my_bitwise_f.c my_bitwise_f.h my_font-12x8.o
my_font-12x8.o: my_font-12x8.c
my_main.o: my_main.c my_DoubleLL.h my_bitwise_f.h
test.o: test.c my_bitwise_f.h my_DoubleLL.h ./h/bitwise_f.h ./h/DoubleLL.h

$(S_OBJS):
	mkdir ./h
	mkdir ./o
	(cd student && make)
	(cd student && cp *.h ../h)
	(cd student && mv *.o ../o)

