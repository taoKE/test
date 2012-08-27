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
            priority_queue<Policy<task_func>/*, std::greater<Policy<task_func> >*/ > pendingTasks;
            
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
   
        protected:
            //the less level is, the higher priority the task is. 0 is the highest
            int level;
        public:
            Policy(task_func const & _task, int _level):task(_task), level(_level){}
            task_func & getTask(){
                return task;
            }

            //This function should be pure virtual function. 
            //This function is used by operator <, which is a const function, 
            //that's why it is also a const function. Otherwise, compilation error
            virtual int getPriority()const {
                return level;
            } 

            int getLevel() const {
                return level;
            }

            //operator () will be the same for everyone
            bool operator ()(){
                cout<<"executing priority:"<<getPriority() << endl;
                task();
            }

            //Looks like when this function is declared as pure virtual function, 
            //the child classes will be abstract class? 
            //TODO: try it out
            //
            //OK, just found that Fifo_Policy has to implement these operators 
            //for the scheduler queue work properly...
            //Not quite sure why yet.
            virtual bool operator < ( Policy<task_func> const & b) const{
                getPriority() < b.getPriority();
            }

            virtual bool operator > ( Policy<task_func> const & b) const{
                getPriority() > b.getPriority();
            }
    };

    //Simulating Fifo by automatically set level
    template <typename task_func = boost::function0<void> >
    class Fifo_Policy : public Policy<task_func>{
        public:
            Fifo_Policy(task_func const & _task, int _level):Policy<task_func>(_task, _level){
                //level = _level + 1;
            }

            int getPriority() const{
                return this->level;
            }
            
            /* going to use the default implementation of base Policy*/
            bool operator < ( Policy<task_func> const &  b) const {
                //Normally, it should return level < b.getPriority(), to be consistent with operator < semantics.
                //But here, we are implemented FIFO, need lower priority first..
                return this->level >  b.getPriority();
            }
            
            bool operator > (Policy<task_func> const & b) const {
                return this->level > b.getPriority();
            }
            
    };

    //One customized policy
    template<typename task_func = boost::function0<void> >
    class Another_Policy : public Policy<task_func> {
        private:
            //this weight is used to differentiate operations
            //etc, query is a heave operation, so the weight is higher
            int weight;
            //cost is used to differentiate the same operation. 
            //etc, query on more fields cost more than query with less fields
            int cost;

        public:
            Another_Policy(task_func const & _task, int _level, int _weight, int _cost)
                :Policy<task_func>(_task, _level), weight(_weight), cost(_cost){}

            //the priority only applies to policies with the same level
            int getPriority() const{
                return weight + cost;
            }

            //Should actually make operator > working, but 
            //std::greater<Policy> is not working.
            bool operator < (Policy<task_func> const & b) const {
                if(this->getLevel() == b.getLevel()) {
                    return this->getPriority() > b.getPriority();
                }
                return this->getLevel() > b.getLevel();
            }

            bool operator > (Policy<task_func> const & b) const {
                if(this->getLevel() == b.getLevel()) {
                    return this->getPriority() > b.getPriority();
                }
                 
                return this->getLevel() > b.getLevel();
                
            }
    };
};
