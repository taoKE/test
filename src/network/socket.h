#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <ctime>
#include <string>
#include <boost/lexical_cast.hpp>


using boost::asio::ip::udp;
using std::string;
using std::cout;
using std::endl;
class Socket {
    private:
        boost::asio::io_service& io_service;
        udp::socket socket;
        boost::system::error_code error;
        udp::endpoint remote_endpoint;
        int port;
        
    public:
        Socket(boost::asio::io_service & _io_service, int _port):
            io_service(_io_service),
            socket(io_service, udp::endpoint(udp::v4(), _port)),
            port(_port)
         {

            /*
            cout<<"Before socket"<<endl;
            socket = new udp::socket(io_service, udp::endpoint(udp::v4(), port));
            */
            cout<<"Done socket construction"<<endl;
        }
        ~Socket(){
            //delete socket;
        }
        void receive_from(string &);
        void send_to(const string & addr, const string & message, const int port);
        void send_to(string );
};
