#include <zhelpers.h>

int main (void) {

  void *context = zmq_ctx_new ();
  
  void *publisher = zmq_socket (context, ZMQ_PUB);
  zmq_bind (publisher, "tcp://*:5556");
  zmq_bind (publisher, "ipc://shared.ipc"); 
  
  void *responder = zmq_socket (context, ZMQ_REP); 
  zmq_bind (responder, "tcp://*:5555");

  while (1) {
	char* request = s_recv(responder);
	printf("Received: %s\n",request);
	char* reply = "OK";
    s_send (responder, reply);
    
    s_send (publisher, request);
    free(request);
  }
  zmq_close (publisher);
  zmq_close (responder);
  zmq_ctx_destroy (context); 
  return 0;
}
