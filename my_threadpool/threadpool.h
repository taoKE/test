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
#include "schedule_policy.h"

using std::cout;
using std::endl;
using std::vector;
using std::queue;
using std::priority_queue;
using std::deque;
using boost::enable_shared_from_this;
using boost::noncopyable;

namespace tke {

    template<typename Task,  
            template<typename> class Policy >
    class threadpool:
            public enable_shared_from_this<threadpool<Task, Policy> >,
            private noncopyable
    {
        private:
            boost::mutex global;
            boost::condition_variable cond;
            boost::condition_variable no_active_worker;
            
            int nBusy;
            //priority_queue< boost::function0<void> > pendingTasks;
            deque<boost::function0<void> > pendingTasks;

            tke::Priority_Scheduler<Policy, Task > scheduler;
            //friend class tke::peer_thread<threadpool>;

        public:
            typedef threadpool<Task, Policy> poolType;
            threadpool(int _n = 10):nBusy(10){
            }   
            ~threadpool(){}

            //Gets the number of threads in the pool
            size_t size() const volatile {
                return nBusy;
            }

            size_t pending() {
                //return  pendingTasks.size();
                return scheduler.size();
            }
            bool execute_task(){
                boost::function0<void> task;
                cout<<"Inside execute_task"<<endl;
                {
                    boost::mutex::scoped_lock lock(global);
                    //while(pendingTasks.empty()){
                    while(scheduler.empty()) {
                        no_active_worker.notify_one();
                        cond.wait(lock);
                    }
                    cout<<"Awaken to work"<<endl;

                    //task = pendingTasks.front();
                    //pendingTasks.pop_front();
                    task = scheduler.top();
                    scheduler.pop();
                }

                if(task) {
                    task();
                }
                return true;
            }

            bool wait(){
                boost::mutex::scoped_lock lock(global);
                //while(!pendingTasks.empty()) {
                while(!scheduler.empty()) {
                    no_active_worker.wait(lock);
                }
                return true;
            }

            void schedule(Task const & task){
                boost::mutex::scoped_lock(global);
                //pendingTasks.push_back(task);
                scheduler.push(task);
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
