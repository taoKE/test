#pragma once
#include <iostream>
#include <boost/asio.hpp>
#include <ctime>
#include <string>

using boost::asio::ip::udp;
using std::string;
class Socket {
    private:
        boost::asio::io_service io_service;
        udp::socket *socket;
        boost::system::error_code error;
        udp::endpoint remote_endpoint;
        
    public:
        Socket(){
            socket = new udp::socket(io_service, udp::endpoint(udp::v4(), 13));
        }
        ~Socket(){
            delete socket;
        }
        void receive_from(string &);
        void send_to(const string & addr, const string & message);
        void send_to(const string &);
};
