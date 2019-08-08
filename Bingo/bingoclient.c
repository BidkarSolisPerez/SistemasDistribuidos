// wuclient.c
// Weather update client
// Connects SUB socket to tcp://localhost:5556
// Collects weather updates and finds avg temp in zipcode 
//
#include <zhelpers.h>
#include <unistd.h>

int main (int argc, char *argv []) {
  void *context = zmq_ctx_new ();

  //  Socket to talk to server
  printf ("Collecting updates from weather server...\n"); 
  void *subscriber = zmq_socket (context, ZMQ_SUB);
  int rc = zmq_connect (subscriber, "tcp://localhost:5556"); 
  //assert (rc == 0);

  char *filter = (argc > 1)? argv [1]: "";
  rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter)); 

  //  Process 100 updates
  for (int tiro = 0; tiro < 10; tiro++) {
    char *string = s_recv (subscriber); 
    printf("Aqui!!");
    int number;
    sscanf (string, "%d",
       &number);
    printf("Number was: %d", number);
    free (string);
    printf("Aqui");
    sleep(10);
  }

  zmq_close (subscriber);
  zmq_ctx_destroy (context); 
  return 0;
}