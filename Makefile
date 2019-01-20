#
# Makefile
# Denis Evsyukov, 2019-01-12 11:25
#

SOURCES = source/*.cc
LIBS = -lcurl
DEBUG = -Wall -ggdb3
FLAGS = -std=gnu++17 -O3

all: linux

clean:
	@rm -rf bin/*
	@mkdir -p bin

compile: clean
	${CXX} ${DEBUG} ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

release: clean
	${CXX} ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

linux: clean
	${CXX} ${FLAGS} ${SOURCES} -o bin/link-checker ${LIBS}

# vim:ft=make
#
