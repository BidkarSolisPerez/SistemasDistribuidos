// Minimal HTTP server in 0MQ
#include "zhelpers.h"

int main (void) {
  int rc;

  // Set-up our context and sockets
  void *ctx = zmq_ctx_new ();
  assert (ctx);

  // Start our server listening
  void *server = zmq_socket (ctx, ZMQ_STREAM);
  zmq_bind (server, "tcp://*:8080");
  assert (server);
  uint8_t id[256];
  size_t id_size = 256;

  while (1) {
     // Get HTTP request;
     // first frame has ID, the next the request.
     id_size = zmq_recv (server, id, 256, 0);

     // Get HTTP request
     char *request = s_recv(server);
     free (request);
                
     request = s_recv(server);
     free (request);
                
     request = s_recv(server);
     
     char *url = strtok(request," ");
     url = strtok(NULL," ");
                
     puts(url);
     free (request);
     
     FILE *fp = fopen(url, "r");
     char * http_response;
     if (fp==NULL) {
       http_response =
                    "HTTP/1.0 400 BAD REQUEST\n\n";
	 } else {
       char * line = NULL;
       size_t len = 0;
       ssize_t read;

       // define the response
       char http_response [] =
         "HTTP/1.0 200 OK\n"
         "Content-Type: text/html\n"
         "\n";
                
       puts("ok2");
       while ((read = getline(&line, &len, fp)) != -1) {
         printf("Retrieved line of length %zu:\n", read);
         printf("%s", line);
       }
    
       // start sending response
       zmq_send (server, id, id_size, ZMQ_SNDMORE);
       // Send the http response
       zmq_send (server, http_response,
         sizeof (http_response),
         ZMQ_SNDMORE
       );

       // Send a zero to close connection to client
       zmq_send(server, id, id_size, ZMQ_SNDMORE);
       zmq_send(server, NULL, 0, ZMQ_SNDMORE);
    }
    
  }

  rc = zmq_close (server);
  assert (rc == 0);

  rc = zmq_ctx_term (ctx);
  assert (rc == 0);

  return 0;
}
