#pragma once

#include <mongo/client/dbclient.h>
#include <string>
#include <map>
#include <boost/utility.hpp>

using namespace mongo;
using boost::shared_ptr;

namespace MDIS {

    //the name of collections
    const static string WORKERS = "mdistor.workers";
    const static string CHUNKS = "mdistor.chunks";

    class MDistor {
        private:
            DBClientConnection * dbConn;
            map<string, shared_ptr<DBClientConnection> > workers;//cached all the connections to the workers.


        public:
            MDistor(DBClientConnection * _dbConn): dbConn(_dbConn) {}
            void connect(string  host);
            void insert(string  ns, BSONObj & p);
            void addWorker(string host);
        
        protected:
            /* 
             * query 
             */
            void getWorkers();
            void init();
    };
};
