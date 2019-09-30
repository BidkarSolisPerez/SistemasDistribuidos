#include "zhelpers.h" 

static main (void) {
	//  Bind inproc socket before starting step1
  void *receiver = zmq_socket (context, ZMQ_PAIR); 
  zmq_bind (receiver, "tcp://*:5552");
  pthread_t thread;
  pthread_create (&thread, NULL, step1, context);

  //  Wait for signal and pass it on
  char *string = s_recv (receiver); 
  free (string);
  zmq_close (receiver);

  //  Connect to step3 and tell it we're ready
  void *xmitter = zmq_socket (context, ZMQ_PAIR); 
  zmq_connect (xmitter, "inproc://step3");
  printf ("Step 2 ready, signaling step 3\n"); 
  s_send (xmitter, "READY");
  zmq_close (xmitter);
  return 0;
}
