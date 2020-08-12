MYFLAGS = -lxml2 -lpthread -lcurl -lncurses -lxml2 -lpcre2-8 -L. -lrandstr -I/usr/include/libxml2
HARD_MODE = -lxml2 -lpthread -lcurl -lncurses -lxml2 -lpcre2-8 -L. -lrandstr_hard -I/usr/include/libxml2 -O2 -march=native -s
all: iHATEcomputers update-fortunes fart.dat mla

iHATEcomputers: boger.o librandstr.so fart.dat
	gcc $(MYFLAGS) -o iHATEcomputers boger.o
boger.o: boger.c
	gcc $(MYFLAGS) -c -g boger.c
boger_hard.o: boger.c
	gcc $(HARD_MODE) -o boger_hard.o -c boger.c
librandstr.so: randstr.c
	gcc $(MYFLAGS) --shared -olibrandstr.so -c -g randstr.c
librandstr_hard.so: randstr.c
	gcc $(HARD_MODE) --shared -o librandstr_hard.so -c randstr.c
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
mla_hard.o: mla.c
	gcc $(HARD_MODE) -o mla_hard.o -c mla.c
libstolen.o: libstolen.c
	gcc $(MYFLAGS) -c -g libstolen.c
libstolen_hard.o: libstolen.c
	gcc $(HARD_MODE) -o libstolen_hard.o -c libstolen.c
wiki.o: wiki.c
	gcc $(MYFLAGS) -c -g wiki.c
ui.o: ui.c
	gcc $(MYFLAGS) -c -g ui.c
wiki_hard.o: wiki.c
	gcc $(HARD_MODE) -o wiki_hard.o -c wiki.c
ui_hard.o: ui.c
	gcc $(HARD_MODE) -o ui_hard.o -c ui.c

test:	iHATEcomputers
	./iHATEcomputers

hard: mla_hard.o ui_hard.o wiki_hard.o libstolen_hard.o librandstr_hard.so fart.dat boger_hard.o
	gcc $(HARD_MODE) -omla_hard mla_hard.o wiki_hard.o ui_hard.o libstolen_hard.o
	gcc $(HARD_MODE) -o iHATEcomputers_hard boger_hard.o
