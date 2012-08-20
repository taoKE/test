#pragma once
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/utility.hpp>
#include <vector>
#include <queue>
#include <queue>

#include "peer_thread.h"

using std::vector;
using std::queue;
using std::priority_queue;
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
            priority_queue< boost::function<void> > pendingTasks;
            friend class peer_thread;

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
