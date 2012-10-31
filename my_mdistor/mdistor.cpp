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
    string chunkColl = db + MDIS::CHUNKS; 

    BSONObjBuilder p;
    //it will always add the first chunk into the chunk collection.
    //later insert will figure out the range and corresponding worker 
    //from the record in chunk collection
    p.append("ns", ns);
    p.append("range", keyAndRange["range"]);
    int start = 0; 
    int end = start + 100;
    p.append("key", BSON("min" << start <<"max" << end));

    dbConn->insert(chunkColl, p.obj());

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

