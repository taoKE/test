#include "socket.h"

void Socket::receive_from(string & message){
    boost::system::error_code error;
    socket->receive_from(boost::asio::buffer(message), remote_endpoint, 0, error);

    if(error && error != boost::asio::error::message_size)
        throw boost::system::system_error(error);
} 

void Socket::send_to(const string & addr, const string & message) {
    boost::system::error_code ignored_error;
    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), addr, "testing");
    udp::endpoint receiver_endpoint = *resolver.resolve(query);
    socket->send_to(boost::asio::buffer(message), receiver_endpoint, 
            0, ignored_error);

}

void Socket::send_to( const string & message) {
    boost::system::error_code ignored_error;
    socket->send_to(boost::asio::buffer(message), remote_endpoint, 
            0, ignored_error);
}
