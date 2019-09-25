// syncpub.c
// Synchronized publisher
//
#include "zhelpers.h"

//  We wait for 10 subscribers
#define SUBSCRIBERS_EXPECTED  3

int main (void) {
  void *context = zmq_ctx_new ();
int maxNumber = 0;
  //  Socket to talk to clients
  void *publisher = zmq_socket (context, ZMQ_PUB);
  zmq_bind (publisher, "tcp://*:5561");

  //  Socket to receive signals
  void *syncservice = zmq_socket (context, ZMQ_REP);
  zmq_bind (syncservice, "tcp://*:5562");

  //  Get synchronization from subscribers
  printf ("Waiting for subscribers\n");
  int subscribers = 0;
  while (subscribers < SUBSCRIBERS_EXPECTED) {
    //  - wait for synchronization request
    char *string = s_recv (syncservice);
    int numberReceived;
    sscanf (string, "%d",&numberReceived);
    printf("El numero es: %d\n",numberReceived);  
    maxNumber = (maxNumber < numberReceived) ? numberReceived : maxNumber;
    free (string);
    // - send synchronization reply
    s_send (syncservice, "Number Received");
    subscribers++;
  }

  //  Now broadcast exactly 1M updates followed by END
  printf ("Broadcasting messages\n");
  int update_nbr;
  for (update_nbr = 0; update_nbr < 1; update_nbr++){
    char numberasstring [10];
    sprintf (numberasstring, "%d", maxNumber);
     s_send (publisher, numberasstring);
  }

  s_send (publisher, "END");  
  zmq_close (publisher);
  zmq_close (syncservice);
  zmq_ctx_destroy (context);
getchar();  
  return 0;
}