select: client server battleship nonetworking

server: server.o networking.o
			gcc -o server server.o networking.o

client: client.o networking.o
			gcc -o client client.o networking.o

battleship: secondarymain.o networking.o battleship.o
			gcc -o battleship secondarymain.o networking.o battleship.o

nonetworking: main.o
			gcc -o nonetworking main.o

main.o: main.c
			gcc -c main.c

server.o: server.c networking.h
			gcc -c server.c

client.o: client.c networking.h
			gcc -c client.c

networking.o: networking.c networking.h
			gcc -c networking.c

battleship.o: battleship.c battleship.h
			gcc -c battleship.c

secondarymain.o: secondarymain.c networking.h battleship.h
			gcc -c secondarymain.c


run:
	./battleship

clean:
	rm *.o
	rm *~
	rm ./
	rm server
	rm client
	rm secondarymain
	rm battleship
	rm nonetworking
