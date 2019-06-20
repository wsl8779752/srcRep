CC=gcc
CFLAGS=-I.
DEPS = hellomake.h


hellomake: hellomake.o hellofunc.o 
	$(CC) -o hellomake hellomake.o hellofunc.o 
	
%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
.PONY : clean
clean :
	-rm hellomake *.o

