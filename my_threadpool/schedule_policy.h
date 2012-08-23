#pragma once
#include <queue>
#include <algorithm>
#include <iostream>

using std::queue;
using std::cout;
using std::endl;


namespace tkd{
    /*
     *Policy needs to implement operator <, except for FIFO
     */
    template<typename Policy, typename QueueType>
    class Scheduler{
        private:
            QueueType< Policy> pendingTasks;
            
        public:
            Schedule_policy(){};

            void push (Policy &  element){
                pendingTasks.push(element);
            }

            //The size of pending queue
            size_t size(){
                return pendingTasks.size();
            }

            elementType & top() const {
                pendingTasks.top();
            }
    
            void pop() {
                pendingTasks.pop();
            }

            void empty() const {
                return pendingTasks.empty();
            }
            
    };


    //When using this policy, Scheduler needs queue
    template <typename task_func = boost::function0<void> >
    class FiFoPolicy {
        private:
            task_func task;            
        public:
            FifoPolicy(Task const & _task):task(_task){}
    };
};
