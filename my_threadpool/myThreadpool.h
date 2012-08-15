#pragma once
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vector>
#include <queue>
#include <priority_queue>

typedef std::vector vector;
typedef std::queue queue;
typedef std::priority_queue priority_queue;

namespace tke {
    /*
    class Task {
        private:
        
            
    };
    */

    class threadpool: boost::noncopyable {
        private:
            boost::mutex global;
            boost::condition_variable cond;
            queue<boost::thread > freeThreads;
            queue<boost::thread > busyThreads;
            int nFree, nBusy;
            priority_queue< boost::function<void> > pendingTasks;

        public:
            threadpool(int _n = 100): nFree(_n), nBusy(0){
                for(int i = 0; i < nFree; i++) {

                }
            }
            
    };
};
