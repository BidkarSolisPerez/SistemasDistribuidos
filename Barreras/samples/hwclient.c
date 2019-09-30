// hwclient.c
// Hello World client
// Connects REQ socket to tcp://localhost:5555 
// Sends "Hello" to server, expects "World" back 
//
#include <zhelpers.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main () {
  void* context = zmq_ctx_new();

  // Socket to talk to server
  puts("Connecting to hello world server...");
  void* requester = zmq_socket(context, ZMQ_REQ);
  zmq_connect(requester, "tcp://localhost:5555");

  for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
    char* request = "Hello";
    s_send(requester, request);
 
    char* reply;
    reply = s_recv(requester);
    printf("Received %s %d\n", reply, request_nbr);
    free (reply);
  }
  zmq_close(requester);
  zmq_ctx_destroy(context);
}
