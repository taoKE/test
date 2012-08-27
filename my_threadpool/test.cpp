#include<iostream>
#include <ctime>
#include <cstdlib>
#include "threadpool.h"

using std::cout;
using std::endl;

void mySleep(){
    cout<<"Start sleeping..."<<endl;
    sleep(1);
    cout<<"Done sleeping"<<endl;
}

//static field needs to be declared
//template<> int tke::Fifo_Policy<boost::function0<void> >::level = 0;

int main() {

    //pool has to be constructed with shared_ptr constructor so as to use shared_from_this function. Otherwise, runtime exception.
    shared_ptr<tke::threadpool<boost::function0<void>, tke::Fifo_Policy > > pool(new tke::threadpool<boost::function0<void>, tke::Fifo_Policy >());

    pool->resize(10);

   tke::Priority_Scheduler<tke::Fifo_Policy, boost::function0<void> > test_scheduler;

    //tke::Fifo_Policy<boost::function0<void> >::level += 1;
    for(int i = 0; i < 30; i++) {
        tke::Fifo_Policy<boost::function0<void> > fifo(&mySleep, i);
        tke::Fifo_Policy<boost::function0<void> > fifo_test(&mySleep, i);
        pool->schedule(fifo);
        test_scheduler.push(fifo_test);
    }

    
    pool->wait();
    //testing if the scheduler sort the policy in the right order with priority queue
    while(!test_scheduler.empty()){
        tke::Policy<boost::function0<void> > task = test_scheduler.top();
        test_scheduler.pop();
        cout<<task.getPriority()<<endl;
    }

    /////////////Testing Another_Policy 
    cout<<"----------------------------Testing Another_Policy---------------------"<<endl;
    tke::Priority_Scheduler<tke::Another_Policy, boost::function0<void> > test_another_scheduler;
    srand( time(NULL) );
    for(int i = 0; i < 100; i++) {
        tke::Another_Policy<boost::function0<void> > test_policy(&mySleep, i % 10, rand(), rand());
        test_another_scheduler.push(test_policy);
    }

    while(!test_another_scheduler.empty()){
        tke::Policy<boost::function0<void> > task = test_another_scheduler.top();
        test_another_scheduler.pop();
        cout<<task.getLevel() << ":" << task.getPriority() <<endl;
    }

    return 0;
}

