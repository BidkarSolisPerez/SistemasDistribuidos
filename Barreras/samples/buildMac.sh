gcc hwserver.c -o ../bin/hwserver -lzmq -I../include
gcc hwclient.c -o ../bin/hwclient -lzmq -I../include

gcc version.c -o ../bin/version -lzmq -I../include

gcc wuserver.c -o ../bin/wuserver -lzmq -I../include
gcc wuclient.c -o ../bin/wuclient -lzmq -I../include

gcc taskevent.c -o ../bin/taskevent -lzmq -I../include
gcc taskwork.c -o ../bin/taskwork -lzmq -I../include
gcc tasksink.c -o ../bin/tasksink -lzmq -I../include

gcc msreader.c -o ../bin/msreader -lzmq -I../include
gcc mspoller.c -o ../bin/mspoller -lzmq -I../include

gcc webserver.c -o ../bin/webserver -lzmq -I../include
gcc taskserver.c -o ../bin/taskserver -lzmq -I../include

gcc rrbroker.c -o ../bin/rrbroker -lzmq -I../include
gcc rrclient.c -o ../bin/rrclient -lzmq -I../include
gcc rrworker.c -o ../bin/rrworker -lzmq -I../include
gcc rsbroker.c -o ../bin/rsbroker -lzmq -I../include

gcc sharedTest.c -o ../bin/sharedTest -lzmq -I../include
gcc sharedBroker.c -o ../bin/sharedBroker -lzmq -I../include
