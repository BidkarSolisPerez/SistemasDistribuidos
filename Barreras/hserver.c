// hwserver.c
// Hello World server
// Binds REP socket to tcp://*:5555
// Expects "Hello" from client, replies with "World" 
//
#include <zhelpers.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main (void) {
  void *context = zmq_ctx_new ();
  //  Socket to talk to clients
  void *responder = zmq_socket (context, ZMQ_REP);
  zmq_bind (responder, "tcp://*:5555");

  int cantRequest = 0;

  printf("Awaiting for clients:\n");

  while (1) {
    // Wait for next request from client
    char* request;
    request = s_recv(responder);
    if (request==NULL) continue;
    printf ("Received %s\n",request);
    
    if(strcmp(request,"ahora") == 0){
        printf("Se recibio %s\n",request);
    }else{
        printf("Incrementar cant de request\n");
        printf("Cantidad de request %d.\n",cantRequest);
        cantRequest++;
    }

    free(request);

    if(cantRequest%3 == 0){
        printf("Cantidad de request %d.\n",cantRequest);
        //  Do some 'work'
        s_sleep (1);

        //  Send reply back to client
        char* reply = "S";
        printf("Reply to client %s.\n",reply);
        s_send (responder, reply);
    }
    else{
        printf("Cantidad de request %d.\n",cantRequest);
        //  Send reply back to client
        char* reply = "N";
        printf("Reply to client %s\n",reply);
        s_send (responder, reply);
    }
  }
  //  We never get here but if we did, this would be how we end
  zmq_close (responder); 
  zmq_ctx_destroy (context); 
  return 0;
}