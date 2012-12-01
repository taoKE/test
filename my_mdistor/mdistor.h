#pragma once

#include <mongo/client/dbclient.h>
#include <string>
#include <map>
#include <boost/utility.hpp>
#include <exception>
#include <iostream>
#include <boost/thread/mutex.hpp>

using namespace mongo;
using boost::shared_ptr;
using namespace std;
using boost::mutex;

namespace MDIS {

    //the name of collections
    const static string WORKERS = "mdistor.workers";

    const static string CHUNKTYPE = "chunk";
    const static string KEYTYPE = "key";

    //chunk info will be stored as a db collection in mdistor
    const static string CHUNKS = "mdistor.";

    //in MB
    static int MAX_CHUNK_SIZE = 32;

    class ChunkInfo {
        private:
            int range;
            string key;
            int current_max;

            //Size in MB of the chunk on the storage server
            int sizeMB;

        public:
            ChunkInfo(string k, int r) : key(k), range(r){}
            void setKey(string k) {
                key = k;
            }

            /**This is required by map to create a new instance
             */
            ChunkInfo(){
                key = "";
                range = 0;
                current_max = 0;
            }

            void setRange(int r) {
                range = r;
            }

            void setCurrentMax(int max) {
                current_max = max;
            }

            int getRange() {
                return range;
            }

            int getCurrentMax() {
                return current_max;
            }

            string getKey() {
                return key;
            }

            int getSize() {
                return sizeMB;
            }

            void setSize(int s) {
                sizeMB = s;
            }

    };


    class MDistor {
        private:
            DBClientConnection * dbConn;
            map<string, shared_ptr<DBClientConnection> > workers;//cached all the connections to the workers.
            map<string, string> defaultKeys; //cached the default keys for dbs
            //TODO: temp solution to getAvailableWorker
            static int tempCount; 
            
            map<string, ChunkInfo> chunkInfos;

            boost::mutex distor_mutex;

            void addChunk(string ns, int range);

            //This background thread that will 
            //check the size of the collections on mongo server 
            //where the chunk reside. If the size exceeds the threads hold,
            //mdistor will creat another chunk for the key so that future inserts
            //will go to the right server for balance. 
            shared_ptr<boost::thread> sizeChecker;

            //This function is going to bind with a thread, 
            //and check the size of collection periodically
            void checkSize();

        public:
            MDistor(DBClientConnection * _dbConn): dbConn(_dbConn) {}
            void connect(string  host);
            void insert(string  ns, BSONObj & p);
            void addWorker(string host);

            /* set the keys and ranges for the ns
             *
             * ns: namespace
             * keyAndRange: 
             *      keys and range. 
             *      Example:
             *        {"id" : "600"} : key is "id", and each chunk will hold 600 entities
             */
            void setKey(string ns, BSONObj & keyAndRange);
        
        protected:
            /* 
             * query 
             */
            void getWorkers();
            void init();

            string getDBFromNS(string ns) {
                size_t pos = ns.find('.');
                if(pos == string::npos){ 
                    std::cout << "invalid ns:"<<ns << std::endl;
                    throw std::exception();
                }
                
                return ns.substr(pos);
            }

            BSONObj getAvailableWorker(){
                int count  = tempCount % workers.size() - 1;
                tempCount++;
                map<string, shared_ptr<DBClientConnection> >::iterator it = workers.begin();

                while(count >= 0){
                    it++;
                    count--;
                }

                std::cout<<"getting available worker: "<<it->first<<endl;
                BSONObj res = dbConn->query(MDIS::WORKERS, BSON("host" << it->first))->next();

                return res;
            }

            shared_ptr<DBClientConnection>  getWorkerConnection(string key,  BSONObj & );

    };
};
