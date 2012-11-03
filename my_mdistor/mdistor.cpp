#include "mdistor.h"
#include <iostream>

using namespace std;

namespace MDIS {

void MDistor::connect(string  host) {
    dbConn->connect(host);
    init();
}

void MDistor::insert(string  ns, BSONObj & p) {
    dbConn->insert(ns, p);

}

void MDistor::setKey(string ns, BSONObj & keyAndRange ) {
    //TODO: is it necessary to redeploy existing data if the key changes?
    string db = getDBFromNS(ns);
    string chunkColl = MDIS::CHUNKS + db; 

    BSONObjBuilder chunk, key;
    //it will always add the first chunk into the chunk record
    //there are 2 types of records in a db collecion: key and chunk
    //key records have the info for keys, range and ns
    //chunk records have the info for min and max keys, etc
    chunk.append("type", "chunk");
    chunk.append("ns", ns);
    chunk.append("range", keyAndRange["range"]);
    int start = 0; 
    int end = start + 100;
    chunk.append("key", BSON("min" << start <<"max" << end));

    key.append("type", "key");
    key.append("ns", ns);
    key.append("key", keyAndRange["key"]);


    dbConn->insert(chunkColl, chunk.obj());
    dbConn->insert(chunkColl, key.obj());

}

void MDistor::addWorker(string host) {
    BSONObjBuilder p;
    int count = workers.size();

    //only add the worker if it is new
    if(workers.count(host) == 0) {
        string worker_string = "worker";
        worker_string += char('1' + count);
        p.append("worker", worker_string);
        p.append("host", host);
        dbConn->insert(MDIS::WORKERS, p.obj());
    }

}

void MDistor::getWorkers() {
    auto_ptr<DBClientCursor> cursor = dbConn->query(MDIS::WORKERS, BSONObj());

    while(cursor->more()) {
        string host = cursor->next()["host"];
        shared_ptr<DBClientConnection> conn(new DBClientConnection());
        conn->connect(host);
        workers[host] = conn; 
    }
}

void MDistor::init() {
    getWorkers();
}

};

