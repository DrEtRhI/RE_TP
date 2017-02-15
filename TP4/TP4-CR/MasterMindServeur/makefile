serveur : fon.o serveur.o masterMind.o
	gcc fon.o serveur.o masterMind.o -o serveur
	
masterMind.o : fon.h masterMind.c
	gcc -c masterMind.c

fon.o :  fon.h fon.c
	gcc -c fon.c

serveur.o : fon.h	serveur.c 
	gcc -c  serveur.c	

clean : 
	rm -f *.o
