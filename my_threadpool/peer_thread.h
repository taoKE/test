#pragma once

#include "threadpool.h"
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>
#include <boost/utility.hpp>
#include <iostream>

using std::endl;
using std::cout;

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

            ~peer_thread() {
            }
            
            void join(){
                pthread->join();
            }
            void run(){
                while(pool->execute_task()){}
            }
            static void create_and_bind(shared_ptr<Pool> const & pool){
                cout<<"creating and binding thread to the pool"<<endl;
                shared_ptr<peer_thread<Pool> > peer(new peer_thread<Pool>(pool));
                if(peer) {
                    peer->pthread.reset(new boost::thread(bind(& peer_thread<Pool>::run, peer)));
                }
            }
    };
};
