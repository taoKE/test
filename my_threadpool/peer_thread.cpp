#include <peer_thread.h>

using tke::peer_thread;
using tke::threadpool;

void peer_thread::run(){


    while(pool->execute_task()){}

    //pool->worker_descruted(this->shared_from_this());
}

void peer_thread::join(){
    pthread->join();
}

static void create_and_bind(shared_ptr<threadpool> const & pool){
    shared_ptr<peer_thread> peer(new peer_thread(pool));
    if(peer) {
        peer->pthread.reset(new boost::thread(bind(&peer_thread::run, peer)));
    }
}
