#pragma once
#include <queue>
#include <algorithm>
#include <iostream>

using std::priority_queue;
using std::cout;
using std::endl;


namespace tke{

    /*
     *Policy needs to implement operator <, except for FIFO
     */
    template< template<typename> class Policy, 
               typename task_func>
    class Priority_Scheduler{
        private:
            priority_queue<Policy<task_func> > pendingTasks;
            
            typedef Policy<task_func> policy;
        public:
            Priority_Scheduler(){};

            void push (policy const &  element){
                pendingTasks.push(element);
            }

            //The size of pending queue
            size_t size(){
                return pendingTasks.size();
            }

            policy & top() const {
                pendingTasks.top();
            }
    
            void pop() {
                pendingTasks.pop();
            }

            bool empty() {
                return pendingTasks.empty();
            }
            
    };


    template<typename task_func = boost::function0<void> >
    class Policy {
        private:
            task_func task;
   
        public:
            Policy(task_func const & _task):task(_task){}
            task_func & getTask(){
                return task;
            }

            //This function should be pure virtual function. 
            //This function is used by operator <, which is a const function, 
            //that's why it is also a const function. Otherwise, compilation error
            virtual int getPriority()const {} 

            //operator () will be the same for everyone
            bool operator ()(){
                task();
            }

            //Looks like when this function is declared as pure virtual function, 
            //the child classes will be abstract class? 
            //TODO: try it out
            virtual bool operator < ( Policy<task_func> const & b) const{};
    };

    //Simulating Fifo by automatically set level
    template <typename task_func = boost::function0<void> >
    class Fifo_Policy : public Policy<task_func>{
        public:
            static int level;
        public:
            Fifo_Policy(task_func const & _task):Policy<task_func>(_task){
                //Dont let level goes REALLY big
                level = ((level+ 1) % 100);
            }

            int getPriority() const{
                return level;
            }

            bool operator < ( Policy<task_func> const &  b) const {
                //level 0 is biggest. This is a heck to implement FIFO with priority_queue
                //There may be some better way.
                if(level == 0) return false;
                return level < b.getPriority();
            }
    };
};
