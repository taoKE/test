#pragma once

#include "threadpool.h"
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/utility.hpp>

using boost::noncopyable;
using boost::shared_ptr;

namespace tke {
    template<typename Pool>
    class peer_thread : private noncopyable{
        private:
            shared_ptr<boost::thread> pthread;
            shared_ptr< Pool> pool;

        public:
            //TODO: does it need to be private?
            peer_thread(shared_ptr<Pool> const & _pool)
                :pool(_pool){}
            
            void join();
            void run();
            static void create_and_bind(shared_ptr<Pool> const & pool);
    };

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

};
