CC=gcc
GENERIC_CFLAGS=-fPIC
INCLUDES=-I /usr/local/lib/erlang/usr/include
MACFLAGS=-bundle -flat_namespace -undefined suppress -fno-common
LINUXFLAGS=-shared
SYSTEM = $(shell uname)

ifeq ($(SYSTEM), Darwin)
        CFLAGS=$(GENERIC_CFLAGS) $(MACFLAGS)
else
        CFLAGS=$(GENERIC_CFLAGS) $(LINUXFLAGS)
endif

all: erlang

erlang: aes_nif.so
        erlc aes.erl

aes_nif.so: aes_core.o
        $(CC) $(CFLAGS) aes_core.o -o aes_nif.so

aes_core.o:
        $(CC) -c aes_core.c -o aes_core.o

clean:
        rm *.o *.so *.beam