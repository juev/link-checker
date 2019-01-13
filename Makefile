#
# Makefile
# Denis Evsyukov, 2019-01-12 11:25
#

SOURCES = source/*.c
LIBS = -lcurl
DEBUG = -Wall -ggdb3

all: clean compile

clean:
	@rm -rf bin/*

compile:
	@mkdir -p bin
	gcc ${DEBUG} ${LIBS} ${SOURCES} -o bin/link-checker

release: clean
	@mkdir -p bin
	gcc ${LIBS} ${SOURCES} -o bin/link-checker

# vim:ft=make
#
