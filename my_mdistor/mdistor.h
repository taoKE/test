#pragma once

#include <mongo/client/dbclient.h>
#include <string>
#include <map>
#include <boost/utility.hpp>
#include <exception>
#include <iostream>

using namespace mongo;
using boost::shared_ptr;
using namespace std;

namespace MDIS {

    //the name of collections
    const static string WORKERS = "mdistor.workers";

    const static string CHUNKTYPE = "chunk";
    const static string KEYTYPE = "key";

    //chunk info will be stored as a db collection in mdistor
    const static string CHUNKS = "mdistor.";

    class ChunkInfo {
        private:
            int range;
            string key;
            int current_max;

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

    };

    class MDistor {
        private:
            DBClientConnection * dbConn;
            map<string, shared_ptr<DBClientConnection> > workers;//cached all the connections to the workers.
            map<string, string> defaultKeys; //cached the default keys for dbs
            //TODO: temp solution to getAvailableWorker
            static int tempCount; 
            
            map<string, ChunkInfo> chunkInfos;

            void addChunk(string ns, int range);

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
