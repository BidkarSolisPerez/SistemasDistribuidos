// Bingoserver.c
// Bingo server
// Binds PUB socket to tcp://*:5556 
// Publishes random weather updates //

#include <zhelpers.h>
int main (void) {
  //  Prepare our context and publisher
  void *context = zmq_ctx_new ();
  void *publisher = zmq_socket (context, ZMQ_PUB); 
  int rc = zmq_bind (publisher, "tcp://*:5556"); 
  //assert (rc == 0);
  rc = zmq_bind (publisher, "ipc://weather.ipc");  

  void *responder = zmq_socket (context, ZMQ_REP); 
  zmq_bind (responder, "tcp://*:5555");  
  //assert (rc == 0);
  //  Initialize random number generator
  srandom ((unsigned) time (NULL));   
  while (1) {
	char* request;
	request = s_recv(responder,ZMQ_NOBLOCK);
	//if (request==NULL) continue;
	if (request==NULL){
		int number = randof(101);
		//  Send message to all subscribers
		char update [3];
		sprintf (update, "%d" , number); 
		s_send (publisher, update);	
		//Sleep to see how to clients are working on in the same way based on the send data...
		s_sleep(500);
	}
	else{
		printf ("Received %s\n",request);
		free(request);
		char* reply = "-1";
		s_send (publisher, reply);
	}
  }
  printf("Fin del juego");
  zmq_close (publisher); 
  zmq_close (responder); 
  zmq_ctx_destroy (context); 
  return 0;
}
