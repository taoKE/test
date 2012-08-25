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
            typedef Policy<task_func> policy;
            //Using the default less comparison, which will use Policy operator <, 
            //and the highest priority will be the top.
            priority_queue<Policy<task_func> > pendingTasks;
            
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
                cout<<"executing priority:"<<getPriority() << endl;
                task();
            }

            //Looks like when this function is declared as pure virtual function, 
            //the child classes will be abstract class? 
            //TODO: try it out
            virtual bool operator < ( Policy<task_func> const & b) const{};
            virtual bool operator > ( Policy<task_func> const & b) const = 0;
    };

    //Simulating Fifo by automatically set level
    template <typename task_func = boost::function0<void> >
    class Fifo_Policy : public Policy<task_func>{
        public:
            int level;
        public:
            Fifo_Policy(task_func const & _task, int _level):Policy<task_func>(_task){
                //Dont let level goes REALLY big
                level = _level + 1;
            }

            int getPriority() const{
                return level;
            }

            bool operator < ( Policy<task_func> const &  b) const {
                //Normally, it should return level < b.getPriority(), to be consistent with operator < semantics.
                //But here, we are implemented FIFO, need lower priority first..
                return level >  b.getPriority();
            }

            bool operator > (Policy<task_func> const & b) const {
                return level > b.getPriority();
            }
    };
};
