#include "zhelpers.h" 

int main (void) {
  void *context = zmq_ctx_new ();
  
  //  Bind inproc socket before starting step2
  void *receiver = zmq_socket (context, ZMQ_PAIR); 
  zmq_bind (receiver, "inproc://step3");
  

  //  Wait for signal
  char *string = s_recv (receiver); 
  free (string);
  zmq_close (receiver);
  printf ("Test successful!\n"); 
  zmq_ctx_destroy (context); 
  return 0;
}
