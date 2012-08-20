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
};
