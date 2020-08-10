all: iHATEcomputers fart.dat
iHATEcomputers: boger.o randstr.o
	gcc -o iHATEcomputers boger.o randstr.o
boger.o: boger.c
	gcc -c -g boger.c
randstr.o: randstr.c
	gcc -c -g randstr.c
fart.dat: fart
	strfile fart
clean:
	rm -f *.o
	rm -f iHATEcomputers
	rm -f fart.dat
.PHONY: all clean
