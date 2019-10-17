x86_64-w64-mingw32-gcc hwserver.c -o ../bin/hwserver.exe -lzmq -L../lib -I../include
x86_64-w64-mingw32-gcc hwclient.c -o ../bin/hwclient.exe -lzmq -L../lib -I../include

x86_64-w64-mingw32-gcc version.c -o ../bin/version.exe -lzmq -L../lib -I../include

x86_64-w64-mingw32-gcc wuserver.c -o ../bin/wuserver.exe -lzmq -L../lib -I../include
x86_64-w64-mingw32-gcc wuclient.c -o ../bin/wuclient.exe -lzmq -L../lib -I../include

x86_64-w64-mingw32-gcc taskevent.c -o ../bin/taskevent.exe -lzmq -L../lib -I../include
x86_64-w64-mingw32-gcc taskwork.c -o ../bin/taskwork.exe -lzmq -L../lib -I../include
x86_64-w64-mingw32-gcc tasksink.c -o ../bin/tasksink.exe -lzmq -L../lib -I../include

x86_64-w64-mingw32-gcc msreader.c -o ../bin/msreader.exe -lzmq -L../lib -I../include
x86_64-w64-mingw32-gcc mspoller.c -o ../bin/mspoller.exe -lzmq -L../lib -I../include

x86_64-w64-mingw32-gcc webserver.c -o ../bin/webserver.exe -lzmq -L../lib -I../include

x86_64-w64-mingw32-gcc taskserver.c -o ../bin/taskserver -lzmq -I../include -L../lib

x86_64-w64-mingw32-gcc rrbroker.c -o ../bin/rrbroker -lzmq -I../include -L../lib
x86_64-w64-mingw32-gcc rrclient.c -o ../bin/rrclient -lzmq -I../include -L../lib
x86_64-w64-mingw32-gcc rrworker.c -o ../bin/rrworker -lzmq -I../include -L../lib
x86_64-w64-mingw32-gcc rsbroker.c -o ../bin/rsbroker -lzmq -I../include -L../lib

x86_64-w64-mingw32-gcc sharedTest.c -o ../bin/sharedTest -lzmq -I../include -L../lib

x86_64-w64-mingw32-gcc fileAttrib.c -o ../bin/fileAttrib -I../include

x86_64-w64-mingw32-gcc test_json.c -o ../bin/test_json -I../include

x86_64-w64-mingw32-gcc lpserver.c -o ../bin/lpserver -lczmq -I../include
x86_64-w64-mingw32-gcc lpclient.c -o ../bin/lpclient -lczmq -I../include
