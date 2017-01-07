all : clean main.o affichage.o ia.o interface.o liste.o
	gcc -o run.exe main.o affichage.o ia.o interface.o liste.o

run : clean all
	clear
	./run

main.o : main.c
	gcc main.c -c

affichage.o : affichage.c
	gcc affichage.c -c

ia.o : ia.c
	gcc ia.c -c

liste.o : liste.c
	gcc liste.c -c

interface.o : interface.c
	gcc interface.c -c

clean :
	-rm *.o