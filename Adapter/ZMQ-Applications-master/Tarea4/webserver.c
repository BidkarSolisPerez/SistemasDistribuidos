// webserver.c
// HTTP adapter in 0MQ
#include "zhelpers.h"

char *replaceWord(const char *s, const char *oldW, 
                                 const char *newW) 
{ 
    char *result; 
    int i, cnt = 0; 
    int newWlen = strlen(newW); 
    int oldWlen = strlen(oldW); 
  
    // Counting the number of times old word 
    // occur in the string 
    for (i = 0; s[i] != '\0'; i++) 
    { 
        if (strstr(&s[i], oldW) == &s[i]) 
        { 
            cnt++; 
  
            // Jumping to index after the old word. 
            i += oldWlen - 1; 
        } 
    } 
  
    // Making new string of enough length 
    //result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1); 
    result = (char *)malloc(i + (newWlen * cnt ) + 1); 
  
    i = 0; 
    while (*s) 
    { 
        // compare the substring with the result 
        if (strstr(s, oldW) == s) 
        { 
            strcpy(&result[i], newW); 
            i += newWlen; 
            s += oldWlen; 
        } 
        else
            result[i++] = *s++; 
    } 
  
    result[i] = '\0'; 
    return result; 
} 

int main (void) {   
  void *ctx = zmq_ctx_new ();  

  void *hserver = zmq_socket (ctx, ZMQ_STREAM);  
  zmq_bind (hserver, "tcp://*:6060");  

  void *tserver = zmq_socket(ctx, ZMQ_REQ);
  zmq_connect (tserver, "tcp://localhost:5555");

  uint8_t id[256];  
  size_t id_size = 256;  
  char * line;  
  int more;  
  size_t more_size = sizeof(more);  
  int length = 0;  

  while (1) { 
     // first frame has ID, the next the request.  
     id_size = zmq_recv (hserver, id, 256, 0);  

     // Get HTTP request  
     char *request = s_recv(hserver);  
	 printf("Request1: %s\n", request);
     free (request);  

     request = s_recv(hserver);
	 printf("Request2: %s\n", request);
     free (request);  

     request = s_recv(hserver);
	 
	 printf("Request3: %s\n", request);

     char http_response [] =  
         "HTTP/1.0 200 OK\n" 
         "Connection: close\n"  
         "Content-Type: text/html\n"
         "Content-Length:          ";	
		 
	char http_response2 [] =  
         "HTTP/1.0 200 OK\n" 
         "Connection: close\n"  
         "Content-Type: text/html\n"
         "Content-Length:          ";
	
		char  * requestExtra = malloc(strlen(request) + 1);
		strcpy(requestExtra, request);
    char *url = strtok(requestExtra," ");
    url = strtok(NULL," ");   
	memmove(url, url+1, strlen(url));
	
	char * extension;
	char * token;
	int cont = 0;
	
	token = strtok(url, ".");
   
	   /* walk through other tokens */
	   while( token != NULL ) {
		   if(cont == 1) extension = token;
		  printf( "%s\n", token );
		
		  token = strtok(NULL, ".");
		  cont = cont+1;
	   }	   
  
    // oldW string 
    printf("Old string: %s \n", http_response2); 
    char * resultAux;
	int normal = 1;
	printf("Extension es: %s %d\n", extension,strcmp("html", extension));
	if(strcmp("html", extension) != 0){		
		if (strcmp("js", extension) == 0)
			resultAux = replaceWord(http_response2, "text/html", "application/javascript"); 
		else if (strcmp("css", extension) == 0)
			resultAux = replaceWord(http_response2, "text/html", "text/css"); 
		
		normal = 0;
		if(resultAux)
			printf("New String: %s \n", resultAux); 
	}		
	s_send(tserver,request);	

     line = s_recv(tserver);	 
		if (normal == 1 && strcmp("js", extension) == 0) {
			sscanf(line,"%d",&length);
			sprintf(resultAux+87,"%d\n\n",length);
			zmq_send(hserver, id, id_size, ZMQ_SNDMORE);  
			zmq_send(hserver, resultAux, 
              strlen(resultAux),ZMQ_SNDMORE);
		}
		else if (normal == 1 && strcmp("css", extension) == 0){
			sscanf(line,"%d",&length);
			sprintf(resultAux+73,"%d\n\n",length);
			zmq_send(hserver, id, id_size, ZMQ_SNDMORE);  
			zmq_send(hserver, resultAux, 
              strlen(resultAux),ZMQ_SNDMORE);
		}
		else{			
			sscanf(line,"%d",&length);
			sprintf(http_response+74,"%d\n\n",length);			
			zmq_send(hserver, id, id_size, ZMQ_SNDMORE);  
			zmq_send(hserver, http_response, 
              strlen(http_response),ZMQ_SNDMORE);
		}    
     free(line);

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