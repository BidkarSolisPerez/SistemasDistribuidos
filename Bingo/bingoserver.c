// wuserver.c
// Weather update server
// Binds PUB socket to tcp://*:5556 
// Publishes random weather updates //

#include <zhelpers.h>
#include <unistd.h>

int main (void) {
  //  Prepare our context and publisher
  void *context = zmq_ctx_new ();
  void *publisher = zmq_socket (context, ZMQ_PUB); 
  int rc = zmq_bind (publisher, "tcp://*:5556"); 
  //assert (rc == 0);
  rc = zmq_bind (publisher, "ipc://bingo.ipc"); 
  //assert (rc == 0);
  //  Initialize random number generator
  srandom ((unsigned) time (NULL)); 
  while (1) {
    //  Get values that will fool the boss
    int bingoNumber; 
    bingoNumber = randof (100); 
    //  Send message to all subscribers
    char update [3];
    sprintf (update, "%d", bingoNumber);
    printf("%d",bingoNumber);
    s_send (publisher, update);
    sleep(2);
  }
  zmq_close (publisher); 
  zmq_ctx_destroy (context); 
  return 0;
}
