// taskserver.c
// Task server
// Binds REP socket to tcp://*:5555
// Expects "Hello" from client, replies with "World" 
//
#include <zhelpers.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (void) {
  void *context = zmq_ctx_new ();

  void *responder = zmq_socket (context, ZMQ_REP); 
  zmq_bind (responder, "tcp://*:5555");
  
  char length[20];
  
  while (1) {

    char* request;
    request = s_recv(responder);
    if (request==NULL) continue;
    
    printf ("Received: %s\n",request);
    
    char *url = strtok(request," ");
    url = strtok(NULL," ");
    
    printf ("URL: %s\n",url);
    
    free(request);
    
    char* reply = "Hello World";
    sprintf(length,"%d",strlen(reply));
    
    printf("Length: %s", length);
    
    s_sendmore(responder, length);
    s_send(responder, reply);
  }

  zmq_close (responder); 
  zmq_ctx_destroy (context); 
  return 0;
}
