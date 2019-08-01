// hwclient.c
// Hello World client
// Connects REQ socket to tcp://localhost:5555 
// Sends "Hello" to server, expects "World" back 
//
#include <zmq.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <zhelpers.h>

int main () {
  void* context = zmq_ctx_new();

  // Socket to talk to server
  puts("Connecting to hello world server...");
  void* requester = zmq_socket(context, ZMQ_REQ);
  zmq_connect(requester, "tcp://localhost:5555");

  for (int request_nbr = 0; request_nbr != 10; request_nbr++) {
    zmq_msg_t request;
    zmq_msg_init_size(&request, 5);
    memcpy(zmq_msg_data(&request), "GGGGG", 5);
    printf("Sending Hello %d...\n", request_nbr);
    zmq_msg_send(&request, requester, 0);
    zmq_msg_close(&request);

    zmq_msg_t reply;
    zmq_msg_init(&reply);
    zmq_msg_recv(&reply, requester, 0);
	int size = zmq_msg_size(&reply);
    char *string = malloc(size + 1);
    memcpy(string, zmq_msg_data(&reply), size);
    printf("Received %s %d\n", string,request_nbr);
    zmq_msg_close(&reply);
	getchar();
  }
  zmq_close(requester);
  zmq_ctx_destroy(context);
}