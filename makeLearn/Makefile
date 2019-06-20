objects = a.o 

program : $(objects)

$(objects) :%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@
