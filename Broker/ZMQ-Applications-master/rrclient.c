#include "zhelpers.h"

int main (void) {

  void *context = zmq_ctx_new ();

  //  Socket to talk to server
  void *requester = zmq_socket (context, ZMQ_REQ); 
  zmq_connect (requester, "tcp://localhost:5559");
  int request_nbr;
  
  srandom ((unsigned) time (NULL));	
  
  for (request_nbr = 0; request_nbr != 10; request_nbr++) {
	
	int factNumber = randof(5);
	
	char number [2];
	sprintf (number, "%d", factNumber);
	  
    s_send (requester, number);
    char *string = s_recv (requester);
    printf ("Received reply %d [%s]\n", request_nbr, string); 
    free (string);
  }
  zmq_close (requester); 
  zmq_ctx_destroy (context); 
  return 0;
}
