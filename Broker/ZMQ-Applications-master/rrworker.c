// rrworker.c
// Hello World worker
// Connects REP socket to tcp://*:5560
// Expects "Hello" from client, replies with "World" 
//
#include "zhelpers.h"

int factorial(int n)
{
  if (n == 0)
    return 1;
  else
    return(n * factorial(n-1));
}

int main (void) {

  void *context = zmq_ctx_new ();

  //  Socket to talk to clients
  void *responder = zmq_socket (context, ZMQ_REP);
  zmq_connect (responder, "tcp://localhost:5560");
  
  
  while (1) {
    // Wait for next request from client
    char *string = s_recv (responder);
    printf ("Received request: [%s]\n", string); 
    
    char result[1000];
    sprintf(result,"%d", factorial(atoi(string)));
    
    free (string);

    //  Do some 'work'
    sleep (1);

    //  Send reply back to client
    s_send (responder, result);
  }
  //  We never get here, but clean up anyhow
  zmq_close (responder); 
  zmq_ctx_destroy (context); 
  return 0;
}
