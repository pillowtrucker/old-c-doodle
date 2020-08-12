MYFLAGS = -lxml2 -lpthread -lcurl -lncurses -lxml2 -lpcre2-8 -L. -lrandstr -I/usr/include/libxml2
all: iHATEcomputers update-fortunes fart.dat mla

iHATEcomputers: boger.o librandstr.so fart.dat
	gcc $(MYFLAGS) -o iHATEcomputers boger.o
boger.o: boger.c
	gcc $(MYFLAGS) -c -g boger.c
librandstr.so: randstr.c
	gcc $(MYFLAGS) --shared -olibrandstr.so -c -g randstr.c
fart.dat: fart
	strfile fart
clean:
	rm -f *.o
	rm -f iHATEcomputers
	rm -f fart.dat
	rm -f mla
.PHONY: all clean update-fortunes

total-wanking: total-wanking.c
	gcc total-wanking.c -ototal-wanking -march=broadwell
update-fortunes:
	./update-fortunes.sh
mla: mla.o wiki.o ui.o libstolen.o librandstr.so fart.dat
	gcc $(MYFLAGS) -omla mla.o wiki.o ui.o libstolen.o
mla.o: mla.c
	gcc $(MYFLAGS) -c -g mla.c
libstolen.o: libstolen.c
	gcc $(MYFLAGS) -c -g libstolen.c
wiki.o: wiki.c
	gcc $(MYFLAGS) -c -g wiki.c
ui.o: ui.c
	gcc $(MYFLAGS) -c -g ui.c
test:	iHATEcomputers
	./iHATEcomputers
