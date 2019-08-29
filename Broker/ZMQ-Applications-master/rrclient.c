// rrclient.c
// Hello World client
// Connects REQ socket to tcp://localhost:5559 
// Sends "Hello" to server, expects "World" back 
//
#include <zhelpers.h>
#include <stdlib.h>

int main (void) {

  void *context = zmq_ctx_new ();

  //  Socket to talk to server
  void *requester = zmq_socket (context, ZMQ_REQ); 
  zmq_connect (requester, "tcp://localhost:5559");
  
  printf ("Press Enter when the workers are ready: "); 
  getchar ();
  printf ("Sending tasks to workers...\n");
  
  int request_nbr;
  for (request_nbr = 0; request_nbr != 10; request_nbr++) {
	int workload;
    // Random workload from 1 to 100 msec
    workload = rand() % 41;  
    
    char string [2];
    sprintf (string, "%d", workload); 
    s_send (sender, string);

    char *string = s_recv (requester);
    printf ("Received reply %d [%s]\n", request_nbr, string); 
    free (string);
  }
  zmq_close (requester); 
  zmq_ctx_destroy (context); 
  return 0;
}
