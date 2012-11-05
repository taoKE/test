#include "mdistor.h"
#include <iostream>

using namespace std;

namespace MDIS {

    int MDistor::tempCount = 1;

void MDistor::connect(string  host) {
    dbConn->connect(host);
    init();
}

void MDistor::insert(string  ns, BSONObj & p) {
    //dbConn->insert(ns, p);
    string db = ns;
    string chunkColl = MDIS::CHUNKS + db;
    
    //We need to key here to decide which chunk this record goes to
    BSONObjBuilder key;
    key.append("type", MDIS::KEYTYPE);
    key.append("ns", ns);
    cout<<"Before querying chunkcoll"<<endl;
    auto_ptr<DBClientCursor> keyCursor = dbConn->query(chunkColl, key.obj());
    cout<<"Done querying chunkColl"<<endl;
    
    //string keyS = keyCursor->next().getStringField("key");;

    cout<<"Getting worker connection"<<endl;
    //shared_ptr<DBClientConnection> worker = getWorkerConnection(keyS,  p); 
    shared_ptr<DBClientConnection> worker = getWorkerConnection(defaultKeys[ns], p);

    cout << "Attempting to insert "<< ns << endl;
    worker->insert(ns, p);
}

void MDistor::setKey(string ns, BSONObj & keyAndRange ) {
    //TODO: is it necessary to redeploy existing data if the key changes?
    cout<<"Starting to set keys"<<endl;
    string db = ns;
    string chunkColl = MDIS::CHUNKS + db; 
    cout<<" is : "<<chunkColl<<endl;
    BSONObjBuilder chunk, key;
    //it will always add the first chunk into the chunk record
    //there are 2 types of records in a db collecion: key and chunk
    //key records have the info for keys, range and ns
    //chunk records have the info for min and max keys, etc
    chunk.append("type", "chunk");
    chunk.append("ns", ns);
    chunk.append("range", keyAndRange.getStringField("range"));
    int start = 0; 
    int end = start + 100;
    chunk.append("key", BSON("min" << start <<"max" << end));
    BSONObj worker = getAvailableWorker();
    chunk.append("worker", worker.getStringField("worker"));
    chunk.append("host" , worker.getStringField("host"));

    key.append("type", "key");
    key.append("ns", ns);
    key.append("key", keyAndRange.getStringField("key"));

    cout<<"trying to insert to chunk collection "<<endl;
    dbConn->insert(chunkColl, chunk.obj());
    cout<<"Done one"<<endl;
    dbConn->insert(chunkColl, key.obj());
    cout<<"Done all "<<endl;

    string coll = ns.substr(0,ns.rfind('.'));
    cout<<"--------"<<coll<<"----------------"<<endl;
    defaultKeys[coll] = ns;
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

        shared_ptr<DBClientConnection> worker(new DBClientConnection());
        worker->connect(host);
        workers[worker_string] = worker;
    }
    cout<<"Done adding workers"<<endl;

}

void MDistor::getWorkers() {
    auto_ptr<DBClientCursor> cursor = dbConn->query(MDIS::WORKERS, BSONObj());

    while(cursor->more()) {
        //string host = cursor->next()["host"];
        string host = cursor->next().getStringField("host");
        cout << "getWorkers: host is: " << host <<endl;
        shared_ptr<DBClientConnection> conn(new DBClientConnection());
        conn->connect(host);
        workers[host] = conn; 
    }
    cout<<"Done getting workers"<<endl;
}

void MDistor::init() {
    getWorkers();
}

/**
 * return the connection to the right worker according to the key curor.
 *
 * param:
 *  cursor: cursor for the key query.
 */
shared_ptr<DBClientConnection> MDistor::getWorkerConnection(string key, BSONObj & p )  {
    cout<<"getworker, key is:"<<key<<endl;
    string _key = key.substr(key.rfind('.')+1);
    cout<<"_key is :"<<_key<<"|"<<endl;
    cout<<"p is :"<<p.toString()<<endl;
    string  field = p.getStringField("id");
    cout<<"getWorker, field is :"<<field<<endl;
    //auto_ptr<DBClientCursor>  cursor = dbConn->query(MDIS::CHUNKS, BSON("key.min" << BSON("$lte" << p.getStringField(key.c_str())) << "key.max" << BSON("$gte" << p.getStringField(key.c_str()))));
    auto_ptr<DBClientCursor> cursor = dbConn->query(MDIS::CHUNKS, QUERY("key.max"<<GT<<field));

    string mdistor_ns = MDIS::CHUNKS + key;
    cout << "mdistor_ns:"<<mdistor_ns <<endl;
    //auto_ptr<DBClientCursor> testCur = dbConn->query(mdistor_ns, QUERY("key.max"<<"100"));
    auto_ptr<DBClientCursor> testCur = dbConn->query(mdistor_ns, QUERY("key.min" <<LT<< 10));
    cout<<"testCur is : "<<testCur->next().getStringField("host");

    if(cursor->more()) {
        cout<<"trying to get host"<<endl;
        string host = cursor->next().getStringField("host");
        return workers[host];
    }

    //TODO: need to add new chunks if there is no corresponding chunk
    return workers.begin()->second;
}


};

