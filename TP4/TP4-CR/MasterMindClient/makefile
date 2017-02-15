client : fon.o client.o	
	gcc fon.o client.o -o client

fon.o :  fon.h fon.c
	gcc -c fon.c
	
client.o : fon.h	client.c 
	gcc -c  client.c

clean : 
	rm -f *.o
