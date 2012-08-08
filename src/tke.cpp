#include <iostream>
#include <string>
#include "network/socket.h"

using namespace std;

void run(){
    boost::asio::io_service io_service;
    cout<<"In run"<<endl;
    Socket testSocket(io_service);
    string buf;
    while(1) {
        cout<<"Waiting for msg..."<<endl;
        try{
            testSocket.receive_from(buf);
            cout<<"Got message:"<<buf<<endl;
            testSocket.send_to(string("Done"));
        } catch(exception & e) {
            std::cerr << e.what() << endl;
            break;
        }
    }
    return ;
}

void msg(const string & addr, const string & msg) {
    cout<<"In msg"<<endl;
    boost::asio::io_service io_service;
    Socket testSocket(io_service);
    testSocket.send_to(addr, msg);
    string message;
    try{
        testSocket.receive_from(message);
        cout<<"msg got message:"<<message<<endl;
    } catch(exception & e) {
        cerr << e.what() << endl;
    }

    return ;
}

int main(int argc, char * argv[]) {

    if(argc >= 2) {
        if(strcmp(argv[1], "run") == 0) {
            run();
            return 0;
        } else if(strcmp(argv[1], "send") == 0) {
            msg(argc >= 3? string(argv[2]):string("127.0.0.1"), argc >= 4?string(argv[3]):string("Ping"));
            return 0;
        }
    }

    cout<<" Usage:"<<endl;
    cout<<"run   run as server"<<endl;
    cout<<"send [msg]   send a request"<<endl;
   
    return 0;
}
