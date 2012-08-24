#include <iostream>
#include "threadpool.h"

using std::cout;
using std::endl;

void mySleep(){
    cout<<"Start sleeping..."<<endl;
    sleep(1);
    cout<<"Done sleeping"<<endl;
}

int main() {

    //pool has to be constructed with shared_ptr constructor so as to use shared_from_this function. Otherwise, runtime exception.
    shared_ptr<tke::threadpool<boost::function0<void> > > pool(new tke::threadpool<boost::function0<void> >());
    pool->resize(10);

    Fifo_Policy::level = 0;
    for(int i = 0; i < 30; i++) {
        Fifo_Policy fifo(&mySleep)
        pool->schedule(fifo);
    }
    
    pool->wait();
    return 0;
}

