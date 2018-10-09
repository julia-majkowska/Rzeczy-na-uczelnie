# variables for make's implicit rules described at:
# https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html

CC = gcc -g -nostdlib
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

all: zad7


%.stripped: %
	objcopy --strip-all --remove-section .note.gnu.build-id $< $@

zad7: 
	$(CC) $(CFLAGS) zad7.s -o zad7
	

clean:
	rm -f zad7 *.stripped *.o *~

# vim: ts=8 sw=8 noet

