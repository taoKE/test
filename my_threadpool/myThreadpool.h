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

    class Threadpool: boost::noncopyable {
        private:
            boost::mutex global;
            queue<boost::thread> freeThreads;
            queue<boost::thread> busyThreads;
            priority_queue< boost::function<void> > pendingTasks;

        public:
    };
};
