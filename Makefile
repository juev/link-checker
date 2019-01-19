#
# Makefile
# Denis Evsyukov, 2019-01-12 11:25
#

SOURCES = source/*.cc
LIBS = -lcurl -lpcre
DEBUG = -Wall -ggdb3
FLAGS = -std=gnu++17 -O3

all: compile

clean:
	@rm -rf bin/*
	@mkdir -p bin

compile: clean
	g++ ${DEBUG} ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

release: clean
	g++ ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

linux: clean
	g++ ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

# vim:ft=make
#
