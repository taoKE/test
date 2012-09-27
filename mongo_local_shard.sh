#!/bin/sh
./mongod --shardsvr --nojournal --dbpath /data/db/a --port 10000 > /tmp/sharda.log &
sleep 3
echo "done first shard server"

./mongod --shardsvr --nojournal --dbpath /data/db/b --port 10001 > /tmp/shardb.log &
sleep 3
echo  "done second shard server"

./mongod --configsvr --nojournal --dbpath /data/db/config --port 10002 > /tmp/configdb.log &
sleep 3
echo "done config server"

./mongos --configdb localhost:10002 > /tmp/mongos.log &
echo  "Done mongos"
