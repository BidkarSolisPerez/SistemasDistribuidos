// hwserver.c
// Hello World server
// Binds REP socket to tcp://*:5555
// Expects "Hello" from client, replies with "World" 
//
#include <zhelpers.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (void) {
  void *context = zmq_ctx_new ();
  //  Socket to talk to clients
  void *responder = zmq_socket (context, ZMQ_REP); 
  zmq_bind (responder, "tcp://*:5555");
  while (1) {
    // Wait for next request from client
    char* request;
    request = s_recvnoblock(responder);
    if (request==NULL) continue;
    printf ("Received %s\n",request);
    free(request);
    
    //  Do some 'work'
    s_sleep (1);
    
    //  Send reply back to client
    char* reply = "World";
    s_send (responder, reply);
  }
  //  We never get here but if we did, this would be how we end
  zmq_close (responder); 
  zmq_ctx_destroy (context); 
  return 0;
}
