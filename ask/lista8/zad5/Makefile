# variables for make's implicit rules described at:
# https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html

CC = gcc -g 
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

all: zad5

zad5: zad5.o mulf.o

%.stripped: %
	objcopy --strip-all --remove-section .note.gnu.build-id $< $@

zad5.o: 
	$(CC) $(CFLAGS) -c zad5.c -o zad5.o
	
mulf.o:
	$(CC) $(CFLAGS) -c mulf.s -o mulf.o

clean:
	rm -f zad5 *.stripped *.o *~

# vim: ts=8 sw=8 noet

