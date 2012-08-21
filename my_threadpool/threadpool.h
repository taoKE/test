#pragma once
#include <boost/thread/mutex.hpp>
#include <boost/thread/condition_variable.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/utility.hpp>
#include <queue>
#include <deque>
#include <iostream>

#include "peer_thread.h"

using std::cout;
using std::endl;
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
            typedef threadpool<Task> poolType;
            threadpool(int _n = 10):nBusy(10){
            }   
            ~threadpool(){}

            //Gets the number of threads in the pool
            size_t size() const volatile {
                return nBusy;
            }

            size_t pending() const volatile{
                return  pendingTasks.size();
            }
            bool execute_task(){
                boost::function0<void> task;
                cout<<"Inside execute_task"<<endl;
                {
                    boost::mutex::scoped_lock lock(global);
                    while(pendingTasks.empty()){
                        cond.wait(lock);
                    }
                    //task = pendingTasks.top();
                    task = pendingTasks.front();
                    pendingTasks.pop_front();
                    if(task) {
                        task();
                    }
                }

                return true;
            }
            void wait(){}

            void schedule(Task const & task){
                boost::mutex::scoped_lock(global);
                pendingTasks.push_back(task);
                cond.notify_one();
            }

            void shutdown(){}

            void resize(int n) {
                cout<<"Inside pool resize"<<endl;
                for(int i = 0; i < n; i++) {
                    cout<<"Creating thread"<<endl;
                    peer_thread<poolType>::create_and_bind(this->shared_from_this());
                }
            }     

    };

};
