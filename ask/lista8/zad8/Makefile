# variables for make's implicit rules described at:
# https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html

CC = gcc -g 
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

all: zad8

zad8: zad8.o approx_sqrt.o

%.stripped: %
	objcopy --strip-all --remove-section .note.gnu.build-id $< $@

zad8.o: 
	$(CC) $(CFLAGS) -c zad8.c -o zad8.o
	
approx_sqrt.o:
	$(CC) $(CFLAGS) -c approx_sqrt.s -o approx_sqrt.o

clean:
	rm -f zad8 *.stripped *.o *~

# vim: ts=8 sw=8 noet

