select: client server secondarymain

server: server.o networking.o
	gcc -o server server.o networking.o

client: client.o networking.o
		gcc -o client client.o networking.o

secondarymain: secondarymain.o networking.o battleship.o
				gcc -o secondarymain secondarymain.o networking.o battleship.o

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

clean:
	rm server
	rm client
	rm secondarymain
	rm *.o
	rm *~
	rm ./
