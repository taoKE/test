all:tke

CC=g++
CFLAGS=-lboost_system -lpthread -I .
OBJECTS=tke.o network/socket.o

%.o:%.c
	$(CC) -c -o $@ $< $(CFLAGS)

tke:$(OBJECTS)
	$(CC) -o $@ $^ $(CFLAGS)

clean:
	rm -f $(OBJECTS) tke
