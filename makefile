#Autores:
#Gabriel Ciccotti Monteiro da Silva
#Tacio dos Santos Souza     
#Vinícius dos Santos Rocha

maratona: maratona.o main.o
	gcc -o maratona maratona.o main.o
maratona.o: maratona.h maratona.c
	gcc -c maratona.c
main.o: maratona.h
	gcc -c main.c
