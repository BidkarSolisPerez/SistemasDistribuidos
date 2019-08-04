// hwserver.c
// Hello World server
// Binds REP socket to tcp://*:5555
// Expects "Hello" from client, replies with "World" 
//
#include <zmq.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <zhelpers.h>
#include <time.h>

int main (void) {
  void *context = zmq_ctx_new ();
  //  Socket to talk to clients
  void *responder = zmq_socket (context, ZMQ_REP); 
  zmq_bind (responder, "tcp://*:5555");
  int numberCount=0	;
  while (1) {
    // Wait for next request from client 
    zmq_msg_t request;
    zmq_msg_init (&request);
    zmq_msg_recv (&request, responder, 0); 
    printf ("Received Hello\n");
    int size = zmq_msg_size(&request);
    char *number = malloc(size + 1);
    memcpy(number, zmq_msg_data(&request), size);
    
    numberCount += atoi(number);
    char numberCountC[10];
    zmq_msg_close (&request);
    //  Do some 'work'
    sleep (1);
    //  Send reply back to client
    zmq_msg_t reply;
    zmq_msg_init_size (&reply, 5);
    memcpy (zmq_msg_data (&reply), itoa(numberCount, numberCountC, 10), size);
    zmq_msg_send (&reply, responder, 0);
    zmq_msg_close (&reply);
  }
  //  We never get here but if we did, this would be how we end
  zmq_close (responder); 
  zmq_ctx_destroy (context); 
  return 0;
}
