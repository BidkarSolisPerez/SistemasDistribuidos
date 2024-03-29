//  lpclient.c  
//  Use zmq_poll to do a safe request-reply  
//
#include <czmq.h>
  
#define REQUEST_TIMEOUT  2500  // (msec(>1000!)  
#define REQUEST_RETRIES  3 // Before we abandon   
#define SERVER_ENDPOINT "tcp://localhost:5555"   
  
int main (void) {  
  
  zctx_t *ctx = zctx_new ();  
  printf ("I: connecting to server...\n");   
  void *client = zsocket_new (ctx, ZMQ_REQ);   
  assert (client);  
  zsocket_connect (client, SERVER_ENDPOINT);   
  
  int sequence = 0;  
  int retries_left = REQUEST_RETRIES;  
  while (retries_left && !zctx_interrupted) {   
    //  We send a request, then we work to get a reply  
    char request [10];  
    sprintf (request, "%d", ++sequence);   
    zstr_send (client, request);   
      
    int expect_reply = 1;   
    while (expect_reply) {   
      //  Poll socket for a reply, with timeout  
      zmq_pollitem_t items [] = { { client, 0, ZMQ_POLLIN, 0 } };   
      int rc = zmq_poll (items, 1, REQUEST_TIMEOUT * ZMQ_POLL_MSEC);   
      if (rc == -1)   
        break; // Interrupted   
      if (items [0].revents & ZMQ_POLLIN) {  
        // We got a reply from the server, must match sequence   
        char *reply = zstr_recv (client);  
        if (!reply)   
          break; // Interrupted   
        if (atoi (reply) == sequence) {   
          printf ("I: server replied OK (%s)\n", reply);   
          retries_left = REQUEST_RETRIES;  
          expect_reply = 0;   
        }   
        else   
          printf ("E: malformed reply from server: %s\n", reply);  
        free (reply);  
      } else   
      if (--retries_left == 0) {   
        printf ("E: server seems to be offline, abandoning\n");   
        break;   
      } else {  
        printf ("W: no response from server, retrying...\n");  
        // Old socket is confused; close it and open a new one   
        zsocket_destroy (ctx, client);  
        printf ("I: reconnecting to server...\n");  
        client = zsocket_new (ctx, ZMQ_REQ);  
        zsocket_connect (client, SERVER_ENDPOINT);  
        // Send request again, on new socket  
        zstr_send (client, request);   
      }   
    }   
  }  
  zctx_destroy (&ctx);   
  return 0;   
} 
