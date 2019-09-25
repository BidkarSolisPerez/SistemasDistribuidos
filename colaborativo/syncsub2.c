// syncsub.c
// Synchronized subscriber
//
#include "zhelpers.h"

int main (void) {
  void *context = zmq_ctx_new ();

  //  First, connect our subscriber socket
  void *subscriber = zmq_socket (context, ZMQ_SUB);
  zmq_connect (subscriber, "tcp://localhost:5561");
  zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, "", 0);

  //  0MQ is so fast, we need to wait a while...
  s_sleep (1);

  //  Second, synchronize with publisher
  void *syncclient = zmq_socket (context, ZMQ_REQ);
  zmq_connect (syncclient, "tcp://localhost:5562");
  //  Initialize random number generator
  srandom ((unsigned) time (NULL));
  int randomNumber;
  randomNumber = rand() % 1;
  char numberasstring [10];
    sprintf (numberasstring, "%d\n", randomNumber);
  //  - send a synchronization request
  s_send (syncclient, numberasstring);

  //  - wait for synchronization reply
  char *string = s_recv (syncclient);
  free (string);

  //  Third, get our updates and report how many we got
  int update_nbr = 0;
  while (1) {
    char *string = s_recv (subscriber);
    if (strcmp (string, "END\n") == 0) {
      free (string);
      break;
    }
printf("Numero con mayor repeticion fue: %s\n",string);
    free (string);
    update_nbr++;
  }
  printf ("Received %d updates\n", update_nbr);  
  zmq_close (subscriber);
  zmq_close (syncclient);
  zmq_ctx_destroy (context);
  getchar();
  return 0;
}