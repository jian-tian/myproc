objects = main.o

myShell: $(objects)
	gcc -g $(objects) -o $@

$(objects): %.o: %.c
	$(CC) -c $(CFLAGS) $< 

.PHONY : clean

clean :
	-rm myShell $(objects)
