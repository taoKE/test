#include <iostream>
#include "threadpool.h"

using std::cout;
using std::endl;

void mySleep(){
    cout<<"Start sleeping..."<<endl;
    sleep(4);
    cout<<"Done sleeping"<<endl;
}

int main() {
    tke::threadpool<boost::function0<void> > pool;

    for(int i = 0; i < 100; i++) {
        pool.schedule(&mySleep);
    }

    return 0;
}

