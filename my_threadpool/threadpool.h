#pragma once
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/utility.hpp>
#include <queue>
#include <deque>

#include "peer_thread.h"

using std::vector;
using std::queue;
using std::priority_queue;
using std::deque;
using boost::enable_shared_from_this;
using boost::noncopyable;

namespace tke {

    template<typename Task>
    class threadpool:
            public enable_shared_from_this<threadpool<Task> >,
            private noncopyable
    {
        private:
            boost::mutex global;
            boost::condition_variable cond;
            //Looks like we dont really need a queue of threads
            //queue<boost::thread > freeThreads;
            //queue<boost::thread > busyThreads;
            int nBusy;
            //priority_queue< boost::function0<void> > pendingTasks;
            deque<boost::function0<void> > pendingTasks;
            //friend class tke::peer_thread<threadpool>;

        public:
            threadpool(int _n = 100):nBusy(0){
            }   
            ~threadpool();

            //Gets the number of threads in the pool
            size_t size() const volatile;

            size_t pending() const volatile;
            void execute_task();
            void wait();
            void schedule(Task const & );
            void shutdown();        

    };
};
