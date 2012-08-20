CC=g++
LIBS=-lboost_system -lpthread
CFLAGS=-shared -fPIC $(LIBS) -I .
OBJECTS=threadpool.o peer_thread.o

all:threadpool.so

%.o:%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

threadpool.so:$(OBJECTS)
	$(CC) -shared -Wl -fPIC $(OBJECTS) -o libthreadpool.so

clean:
	rm *.o *.so
