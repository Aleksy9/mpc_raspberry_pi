LIBS  = -lm -g
CFLAGS = -Wall

# Should be equivalent to your list of C files, if you don't build selectively
SRC=$(wildcard *.c)

optimisation: $(SRC)
	gcc -o $@ $^ $(CFLAGS) $(LIBS)