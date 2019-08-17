// taskintegr.c
// Task sink
// Binds PULL socket to tcp://localhost:5558
// Collects results from workers via that socket //
#include "zhelpers.h" 
#include <unistd.h>

int main (void) {

   //  Prepare our context and socket
   void *context = zmq_ctx_new ();
   void *receiver = zmq_socket (context, ZMQ_PULL); 
   zmq_bind (receiver, "tcp://*:5558"); 

   //  Wait for start of batch
   char *string = s_recv (receiver,0); 
   free (string); 

   //  Start our clock now
   int64_t start_time = s_clock (); 
   
   int sumFact= 0;

   //  Process 100 confirmations
   int task_nbr;
   for (task_nbr = 0; task_nbr < 4; task_nbr++) { 
     char *string = s_recv (receiver,0); 
     sumFact += atoi(string);
     free (string);

     fflush (stdout);
   } 
   //  Calculate and report duration of batch
   printf ("Total sum of Factorial calculation is: %d", sumFact); 

  zmq_close (receiver); 
  zmq_ctx_destroy (context); 
  return 0; 
}
