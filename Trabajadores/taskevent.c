// taskevent.c
// Task generator
// Binds PUSH socket to tcp://localhost:5557
// Sends batch of tasks to workers via that socket 
//

#include "zhelpers.h" 
#include <unistd.h>

int main (void) { 
  void *context = zmq_ctx_new (); 

  //  Socket to send messages on
  void *sender = zmq_socket (context, ZMQ_PUSH); 
  zmq_bind (sender, "tcp://*:5557"); 

  //  Socket to send start of batch message on
  void *sink = zmq_socket (context, ZMQ_PUSH); 
  zmq_connect (sink, "tcp://localhost:5558");

  printf ("Press Enter when the workers are ready: "); 
  getchar ();
  printf ("Sending tasks to workers...\n");

  //  The first message is "0" and signals start of batch
  s_send (sink, "0");


  //  Send 100 tasks
  int task_nbr;

  for (task_nbr = 0; task_nbr < 4; task_nbr++) { 
    int workload;
    // Random workload from 1 to 100 msec
    workload = task_nbr;
 
    char string [2];
    sprintf (string, "%d", workload); 
    s_send (sender, string); 
  }
  sleep (1); // Give 0MQ time to deliver 

  zmq_close (sink); 
  zmq_close (sender); 
  zmq_ctx_destroy (context); 
  return 0; 
} 
