CC=g++
LIBS=-lboost_system -lpthread -lboost_thread-mt
CFLAGS= -c -g -Wall -fPIC $(LIBS) -I.
#OBJECTS=threadpool.o peer_thread.o

all:libthreadpool.so

test:test

%.o:%.cpp
	$(CC) $(CFLAGS)  -o $@ $<

libthreadpool.so:$(OBJECTS)
	$(CC) -g -shared -Wl,--export-dynamic -Wl,-soname,libthreadpool.so -o libthreadpool.so $(OBJECTS)

test:libthreadpool.so
	g++  -lboost_thread-mt -L. -lthreadpool -o test test.cpp

clean:
	rm *.so test
