#include "zhelpers.h" 

static main (void) {
  //  Connect to step2 and tell it we're ready
  void *xmitter = zmq_socket (context, ZMQ_PAIR); 
  zmq_connect (xmitter, "tcp://:5555");
  printf ("Step 1 ready, signaling step 2\n"); 
  s_send (xmitter, "READY");
  zmq_close (xmitter); 
  return 0;
}
