#include "threadpool.h"

using tke::threadpool;

template<typename Task>
threadpool<Task>::~threadpool() {
}

template<typename Task>
size_t threadpool<Task>::size() const volatile{
    return nBusy;
}

template<typename Task>
size_t threadpool<Task>::pending() const volatile {
    return  pendingTasks.size();
}

template<typename Task>
void threadpool<Task>::execute_task() {
    boost::function0<void> task;

    {
        boost::mutex::scoped_lock lock(global);
        while(pendingTasks.empty()){
            cond.wait(lock);
        }
        //task = pendingTasks.top();
        task = pendingTasks.front();
        pendingTasks.pop_front();
    }
    if(task) {
        task();
    }
}

template<typename Task>
void threadpool<Task>::schedule(Task const & task){
    boost::mutex::scoped_lock(global);
    pendingTasks.push_back(task);
    cond.notify_one();
}
