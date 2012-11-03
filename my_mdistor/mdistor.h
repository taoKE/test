#pragma once

#include <mongo/client/dbclient.h>
#include <string>
#include <map>
#include <boost/utility.hpp>
#include <exception>

using namespace mongo;
using boost::shared_ptr;

namespace MDIS {

    //the name of collections
    const static string WORKERS = "mdistor.workers";

    //chunk info will be stored as a db collection in mdistor
    const static string CHUNKS = "mdistor.";

    class MDistor {
        private:
            DBClientConnection * dbConn;
            map<string, shared_ptr<DBClientConnection> > workers;//cached all the connections to the workers.
 

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
                if(pos == string::npos) 
                    throw std::exception();
                
                return ns.substr(pos);
            }

    };
};
