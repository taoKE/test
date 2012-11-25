#include <iostream>
#include "mdistor.h"
#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>

using namespace std;
using namespace mongo;
using namespace MDIS;

int main() {
    DBClientConnection c;
    MDistor distor(&c);

    distor.connect("localhost");
    BSONObj p = BSON("name" << "test" << "key" << "age" << "id" << 10);
    distor.addWorker("localhost:10000");
    distor.addWorker("localhost:10001");
    BSONObjBuilder key;
    key.append("key", "test_db.test_coll.id");
    key.append("range", 100);
    BSONObj bKey = key.obj();
    distor.setKey("test_db.test_coll.id", bKey);

    BSONObj p2 = BSON("name" << "test" << "key" << "age" << "id" << 110);
    distor.insert(string("test_db.test_coll"), p);
    boost::this_thread::sleep(boost::posix_time::seconds(5));
    distor.insert(string("test_db.test_coll"), p2);
    boost::this_thread::sleep(boost::posix_time::seconds(5));

    return 0;
}
