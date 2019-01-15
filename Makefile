#
# Makefile
# Denis Evsyukov, 2019-01-12 11:25
#

SOURCES = source/*.c
LIBS = -lcurl -lpcre
DEBUG = -Wall -ggdb3
FLAGS = -std=c99 -O3

all: clean compile

clean:
	@rm -rf bin/*

compile:
	@mkdir -p bin
	gcc ${DEBUG} ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

release: clean
	@mkdir -p bin
	gcc ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

# vim:ft=make
#
