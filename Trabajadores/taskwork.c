// taskwork.c
// Task worker
// Connects PULL socket to tcp://localhost:5557
// Collects workloads from task generator via that socket 
// Connects PUSH socket to tcp://localhost:5558
// Sends results to integrator via that socket
//
#include "zhelpers.h"
#include <unistd.h>

int factorial(int n)
{
  if (n == 0)
    return 1;
  else
    return(n * factorial(n-1));
}

int main (void) { 
  void *context = zmq_ctx_new ();

  //  Socket to receive messages on
  void *receiver = zmq_socket (context, ZMQ_PULL); 
  zmq_connect (receiver, "tcp://localhost:5557"); 

  //  Socket to send messages to
  void *sender = zmq_socket (context, ZMQ_PUSH); 
  zmq_connect (sender, "tcp://localhost:5558"); 

  //  Process tasks forever
  while (1) {
    char *string = s_recv (receiver,0);
    // Simple progress indicator for the viewer 
    fflush (stdout);

    // Do the work 
    char result[1000];
    sprintf(result,"%d", factorial(atoi(string)));
    free (string);

    //  Send results to integrator
    s_send (sender, result);
  }
  zmq_close (receiver);
  zmq_close (sender);
  zmq_ctx_destroy (context);
  return 0;
} 
