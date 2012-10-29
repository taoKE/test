#include <iostream>
#include "mdistor.h"

using namespace std;
using namespace mongo;
using namespace MDIS;

int main() {
    DBClientConnection c;
    MDistor distor(&c);

    distor.connect("localhost");
    BSONObj p = BSON("name" << "test" << "key" << "age");
    distor.insert(string("mdistor.chunks_test"), p);

    return 0;
}
