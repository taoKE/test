#pragma once

#include "myThreadpool.h"
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/bind.hpp>

namespace tke {
    class peer_thread : private noncopyable{
        private:
            shared_prt<boost::thread> pthread;
            shared_ptr< tke::threadpool> pool;

        public:
            //TODO: does it need to be private?
            peer_thread(shared_prt<tke::threadpool> const & _pool)
                :pool(_pool){}
            
            void join();
            void run();
    };
}
