#
# Makefile
# Denis Evsyukov, 2019-01-12 11:25
#

SOURCES = source/*.c
LIBS = -lcurl -lpcre
DEBUG = -Wall -ggdb3
FLAGS = -std=c99 -O3

all: compile

clean:
	@rm -rf bin/*
	@mkdir -p bin

compile: clean
	gcc ${DEBUG} ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

release: clean
	gcc ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

linux: clean
	gcc ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

# vim:ft=make
#
