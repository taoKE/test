#include "socket.h"

int Socket::receive_from(string & message){
    boost::system::error_code error;
    //boost::array<char, 1024> recv_buf;
    int len = socket.receive_from(boost::asio::buffer(buf), remote_endpoint, 0, error);

    if(error && error != boost::asio::error::message_size)
        throw boost::system::system_error(error);
    
    cout<<"--------------------------------"<<endl;
    //std::cout.write(buf, len - 1);
    //cout<<buf;
   ;
    cout<<endl<<"Done receive_from:"<<"| len="<<len<<endl;
    cout<<"--------------------------------"<<endl;
   
    return len; 
} 

void Socket::send_to(const string & addr, const string & message, const int port_ ) {
    boost::system::error_code ignored_error;
    //udp::resolver resolver(io_service);
    //the last param is the service the port is for (define in firewall)
    //udp::resolver::query query(udp::v4(), addr, "testing");
    //udp::endpoint receiver_endpoint = *resolver.resolve(query);
    
    //constructing the endpoint with IP and port
    udp::endpoint receiver_endpoint = boost::asio::ip::udp::endpoint(
                  boost::asio::ip::address::from_string(addr), boost::lexical_cast<int>(port_));
    cout<<receiver_endpoint.address()<<":"<<receiver_endpoint.port()<<endl;
    socket.send_to(boost::asio::buffer(message), receiver_endpoint, 
            0, ignored_error);
}

void Socket::send_to(string message) {
    boost::system::error_code ignored_error;
    //cout<<remote_endpoint.address()<<";"<<remote_endpoint.port()<<endl;
    socket.send_to(boost::asio::buffer(message), remote_endpoint, 
            0, ignored_error);
}
