#
# Makefile
# Jim Zenn, 2019-05-16 21:53
#

.PHONY:all test
all: injdump rpassraw rtest
injection: injection.s
	gcc -c injection.s -o injection.o
injdump: injection.o
	objdump -d injection.o > injdump
cpassraw: cpasshex
	./hex2raw < cpasshex > cpassraw
rpassraw: rpasshex
	./hex2raw < rpasshex > rpassraw
ctest: cpassraw
	cat cpassraw | ./ctarget
rtest: rpassraw
	cat rpassraw | ./rtarget

injection.s:
cpasshex:
rpasshex:

