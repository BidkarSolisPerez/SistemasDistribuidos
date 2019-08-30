// taskserver.c
// Task server
// Binds REP socket to tcp://*:5555
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
	memmove(url, url+1, strlen(url));
	printf ("New URL: %s\n",url);	
	FILE *fp;
	char ch;
	char * buffer = 0;
	int size;
   fp = fopen(url, "r"); // read mode
 
   if (fp == NULL)
   {
      perror("Error while opening the file.\n");
	  getchar();
      exit(EXIT_FAILURE);
   }	  
	  
   printf("Yeah\n");
    fseek(fp, 0, SEEK_END); // seek to end of file
	size = ftell(fp); // get current file pointer
	fseek(fp, 0, SEEK_SET); // seek back to beginning of file
	printf("size: %d\n",size);
	buffer = malloc (size);
    //while((ch = fgetc(fp)) != EOF)
      //printf("%c", ch);
    fread (buffer, 1, size, fp);
	printf("Data: %s\n", buffer);
    //free(request);	
	//free(url);
    //char* reply = "<h6>Hello World<h6> <h1>Hello World<h1>";
    sprintf(length,"%d",strlen(buffer));

    s_sendmore(responder, length);
    s_send(responder, buffer);
	free(buffer);
  }

  zmq_close (responder); 
  zmq_ctx_destroy (context); 
  return 0;
}