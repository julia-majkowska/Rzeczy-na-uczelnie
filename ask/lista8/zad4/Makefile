# variables for make's implicit rules described at:
# https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html

CC = gcc -g 
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

all: zad4

zad4: zad4.o fibonacci.o

%.stripped: %
	objcopy --strip-all --remove-section .note.gnu.build-id $< $@

zad4.o: 
	$(CC) $(CFLAGS) -c zad4.c -o zad4.o
	
fibonacci.o:
	$(CC) $(CFLAGS) -c fibonacci.s -o fibonacci.o

clean:
	rm -f zad4 *.stripped *.o *~

# vim: ts=8 sw=8 noet

