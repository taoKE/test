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

            virtual bool operator < (Policy<task_func> const & a, Policy<task_func> const & b) = 0;
    };

    //Simulating Fifo by automatically set level
    template <typename task_func = boost::function0<void> >
    class Fifo_Policy : Policy<task_func>{
        private:
            queue<task_func> pendingTask;
            static int level;
        public:
            FifoPolicy(Task const & _task):task(_task){
                //Dont let level goes REALLY big
                level = ((level+ 1) % 100);
            }

            int getLevel(){
                return level;
            }

            bool operator < (Policy<task_func> const & a, Policy<task_func> const & b) {
                //level 0 is biggest. This is a heck to implement FIFO with priority_queue
                //There may be some better way.
                if(level == 0) return false;
                return a.getLevel() < b.getLevel();
            }
    };
};
