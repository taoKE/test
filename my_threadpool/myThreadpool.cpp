#include "myThread.h"

using tke::threadpool;

size_t threadpool::size() const volatile{
    return nBusy;
}

size_t threadpool::pending() const volatile {
    return  pendingTasks.size();
}

void threadpool::execute_task() {
    boost::function0<void> task;

    {
        boost::mutex::scoped_lock lock(global);
        while(pendingTasks.isEmpty()){
            cond.wait(lock);
        }
        task = pendingTasks.top();
        pendingTasks.pop();
    }
    if(task) {
        task();
    }
}

void threadpool::schedule(Task const & task){
    boost::scoped_lock(global);
    pendingTasks.push(task);
    cond.notify_one();
}
