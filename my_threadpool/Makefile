CC=g++
LIBS=-lboost_system -lpthread
CFLAGS= -c -g -Wall -fPIC $(LIBS) -I.
#OBJECTS=threadpool.o peer_thread.o

all:threadpool.so

%.o:%.cpp
	$(CC) $(CFLAGS)  -o $@ $<

threadpool.so:$(OBJECTS)
	$(CC) -g -shared -Wl,--export-dynamic -Wl,-soname,libthreadpool.so -o libthreadpool.so $(OBJECTS)

clean:
	rm *.o *.so
