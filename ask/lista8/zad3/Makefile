# variables for make's implicit rules described at:
# https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html

CC = std=C99 gcc -g 
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

all: zad3

zad3: zad3.o insert_sort.o

%.stripped: %
	objcopy --strip-all --remove-section .note.gnu.build-id $< $@

zad3.o: 
	$(CC) $(CFLAGS) -c zad3.c -o zad3.o
	
insert_sort.o:
	$(CC) $(CFLAGS) -c insert_sort.s -o insert_sort.o

clean:
	rm -f zad3 *.stripped *.o *~

# vim: ts=8 sw=8 noet

