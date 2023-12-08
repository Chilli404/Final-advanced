CC=gcc
CFLAGS=-ggdb -g -fopenmp -I.
DEPS = stuffs.h
OBJ = hash.o heap.o tree.o main.o

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	\rm -f *.o main
