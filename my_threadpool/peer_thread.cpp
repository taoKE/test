#include <peer_thread.h>

using tke::peer_thread;
using tke::threadpool;

template<typename Pool>
void peer_thread<Pool>::run(){


    while(pool->execute_task()){}

    //pool->worker_descruted(this->shared_from_this());
}

template<typename Pool>
void peer_thread<Pool>::join(){
    pthread->join();
}

template<typename Pool>
static void create_and_bind(shared_ptr<Pool> const & pool){
    shared_ptr<peer_thread<Pool> > peer(new peer_thread<Pool>(pool));
    if(peer) {
        peer->pthread.reset(new boost::thread(bind(& peer_thread<Pool>::run, peer)));
    }
}
