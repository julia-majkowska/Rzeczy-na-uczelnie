# variables for make's implicit rules described at:
# https://www.gnu.org/software/make/manual/html_node/Catalogue-of-Rules.html

CC = gcc -g 
CFLAGS = -Og -Wall
LDFLAGS = 
ASFLAGS = -g

all: zad6


%.stripped: %
	objcopy --strip-all --remove-section .note.gnu.build-id $< $@

zad6: 
	$(CC) $(CFLAGS) main.s -o zad6
	

clean:
	rm -f zad6 *.stripped *.o *~

# vim: ts=8 sw=8 noet

