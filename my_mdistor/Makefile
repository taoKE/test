all:server

objects=mdistor.o server.o

server:mdistor.so server.o
	g++ -o server server.o -L. -lmdistor -pthread -lmongoclient -lboost_thread-mt -lboost_filesystem -lboost_program_options -lboost_system

mdistor.so:mdistor.o
	g++ -shared -o libmdistor.so  mdistor.o

$(objects):%.o:%.cpp
	g++ -fPIC -c  $< -o $@

clean:
	rm *.o server libmdistor*

