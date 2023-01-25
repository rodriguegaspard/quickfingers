CC	= gcc
CFLAGS 	= -Wall -pedantic
LDLIBS 	= -lncurses
OBJ 	= main.o

quickfingers: $(OBJ)
	$(CC) $(CFLAGS) -o quickfingers $(OBJ) $(LDLIBS)

.PHONY : clean
clean :
	-rm quickfingers $(OBJ)
