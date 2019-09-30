// HTTP adapter in 0MQ  
#include "zhelpers.h"  
  
int main (void) {  
  
  // Set-up our context and sockets  
  void *ctx = zmq_ctx_new ();  
  
  // Start our server listening  
  void *hserver = zmq_socket (ctx, ZMQ_STREAM);  
  zmq_bind (hserver, "tcp://*:8080");  
    
  void *tserver = zmq_socket(ctx, ZMQ_REQ);
  zmq_connect (tserver, "tcp://localhost:5555");
  
  uint8_t id[256];  
  size_t id_size = 256;  
  char * line;  
  int more;  
  size_t more_size = sizeof(more);  
  int length = 0;  
  
  while (1) {  
     // Get HTTP request;  
     // first frame has ID, the next the request.  
     id_size = zmq_recv (hserver, id, 256, 0);  
  
     // Get HTTP request  
     char *request = s_recv(hserver);  
     free (request);  
                  
     request = s_recv(hserver);
     free (request);  
                  
     request = s_recv(hserver);
       
     // define the response  
     char http_response [] =  
         "HTTP/1.0 200 OK\n" 
         "Connection: close\n"  
         "Content-Type: text/html\n"
         "Content-Length:          "; 
  
     printf("%s\n",request);
     
     s_send(tserver,request);
  
     line = s_recv(tserver);
     
     printf("Line: %s\n",line);
     
     sscanf(line,"%d",&length);
     
     printf("Length: %d\n",length);
     
     sprintf(http_response+74,"%d\n\n",length);
     
     printf("%s\n",http_response);
     
     free(line);
     
     zmq_send(hserver, id, id_size, ZMQ_SNDMORE);  
     zmq_send(hserver, http_response, 
              strlen(http_response),ZMQ_SNDMORE);
     
     while (1) {  
       line = s_recv(tserver);
       zmq_send(hserver, id, id_size, ZMQ_SNDMORE);  
       zmq_send(hserver, line, strlen(line),ZMQ_SNDMORE);  
       free(line);  
         
       zmq_getsockopt(tserver, ZMQ_RCVMORE, &more, &more_size);  
         
       if (!more) {  
         // Send a zero to close connection to client  
         zmq_send(hserver, id, id_size, ZMQ_SNDMORE);  
         zmq_send(hserver, NULL, 0, ZMQ_SNDMORE);  
         break;  
       }  
     }  
     free (request);
  }  
  
  zmq_close (hserver);  
  zmq_close (tserver);  
  zmq_ctx_term (ctx);  
  return 0;  
}

