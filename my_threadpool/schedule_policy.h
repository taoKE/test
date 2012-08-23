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
    template<typename Policy>
    class Priority_Scheduler{
        private:
            priority_queue<Policy> pendingTasks;
            
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


    template<typenmae task_func = boost::function0<void> >
    class Policy {
        private:
            task_func task;
        public:
            Policy(task_func const & _task):task(_task){}
            task_func & getTask(){
                return task;
            }
    };

    //When using this policy, Scheduler needs queue
    template <typename task_func = boost::function0<void> >
    class Fifo_Policy : Policy<task_func>{
        private:
            queue<task_func> pendingTask;
        public:
            FifoPolicy(Task const & _task):task(_task){
                type = "fifo";
            }

            string getType() const {
                return type;
            }
    };
};
