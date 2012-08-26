#include <iostream>
#include "threadpool.h"

using std::cout;
using std::endl;

void mySleep(){
    cout<<"Start sleeping..."<<endl;
    sleep(20);
    cout<<"Done sleeping"<<endl;
}

//static field needs to be declared
//template<> int tke::Fifo_Policy<boost::function0<void> >::level = 0;

int main() {

    //pool has to be constructed with shared_ptr constructor so as to use shared_from_this function. Otherwise, runtime exception.
    shared_ptr<tke::threadpool<boost::function0<void>, tke::Fifo_Policy > > pool(new tke::threadpool<boost::function0<void>, tke::Fifo_Policy >());

    pool->resize(10);


    //tke::Fifo_Policy<boost::function0<void> >::level += 1;
    for(int i = 0; i < 30; i++) {
        tke::Fifo_Policy<boost::function0<void> > fifo(&mySleep, i);
        pool->schedule(fifo);
    }
    
    pool->wait();
    return 0;
}

