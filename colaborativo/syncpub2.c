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
  int arrayNumber[2] = {0,0};
  while (subscribers < SUBSCRIBERS_EXPECTED) {
    //  - wait for synchronization request
    char *string = s_recv (syncservice);
    int numberReceived;
    sscanf (string, "%d",&numberReceived);
    printf("El numero es: %d\n",numberReceived);  
    if(numberReceived > 0){
      printf("Numero mayor a 0\n");
      printf("Numero menor a %d\n",arrayNumber[1]);
      arrayNumber[1] +=1;
    }else{
      printf("Numero menor a 0\n");
      printf("Numero menor a %d\n",arrayNumber[0]);
      arrayNumber[0] +=1;
    } 
    free (string);
    // - send synchronization reply
    s_send (syncservice, "Number Received\n");
    subscribers++;
  }

  //  Now broadcast exactly 1M updates followed by END
  printf ("Broadcasting messages\n");
  int update_nbr;
  for (update_nbr = 0; update_nbr < 1; update_nbr++){
    char numberasstring [10];
    if(arrayNumber[0] > arrayNumber[1]){
      maxNumber = 0; 
    }else{
      maxNumber = 1;
    } 
    sprintf (numberasstring, "%d\n", maxNumber);
     s_send (publisher, numberasstring);
  }

  s_send (publisher, "END\n");  
  zmq_close (publisher);
  zmq_close (syncservice);
  zmq_ctx_destroy (context);
getchar();  
  return 0;
}