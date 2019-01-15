#
# Makefile
# Denis Evsyukov, 2019-01-12 11:25
#

SOURCES = source/*.c
LIBS = -lcurl -lpcre
DEBUG = -Wall -ggdb3
FLAGS = -std=c99 -O3

all: clean compile

dir:
	@mkdir -p bin

clean:
	@rm -rf bin/*

compile: dir
	gcc ${DEBUG} ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

release: clean dir
	gcc ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

linux: clean dir
	gcc ${FLAGS} -static ${SOURCES} -o bin/link-checker ${LIBS}

# vim:ft=make
#
