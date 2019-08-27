// taskserver.c
// Task server
// Binds REP socket to tcp://*:5555
//
#include <zhelpers.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

long fsize(FILE *fp){
    long prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    long sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}

int main (void) {
  void *context = zmq_ctx_new ();

  void *responder = zmq_socket (context, ZMQ_REP); 
  zmq_bind (responder, "tcp://*:5555");

  char length[2000];

  while (1) {

    char* request;
    request = s_recv(responder);
    if (request==NULL) continue;

    printf ("Received: %s\n",request);

    char *url = strtok(request," ");
    url = strtok(NULL," ");
    
    int urlSize = strlen(url);
    
    printf("Char size url %d \n",urlSize);
    
    char urlFile[urlSize-1];
    
    printf("Pos 1 url: %c\n", *(&url[1]));
    

    for(int i=0; i < urlSize; i++){
		urlFile[i] = *(&url[i+1]);
	}
	
	

    printf ("URL: %s\n",url);
    printf ("URL file: %s\n",urlFile);
    
    free(request);

    
    char linea[1024];
    FILE *fich;
 
    fich = fopen(urlFile, "r");
	 
	long fileSize = fsize(fich);
    
    printf("Tamano del archivo es: %d\n",fileSize); 
	   
    printf("Leer Archivo");
    
    char *lect;
    
    //Lee línea a línea y escribe en pantalla hasta el fin de fichero
    while(fgets(linea, 1024, (FILE*) fich)) {
        printf("%s\n", linea);
        strcat(lect,linea);
    }
    fclose(fich);
    
    printf ("\nLo que dice el archivo es: %s\n",lect);

    char* reply = lect;
    
    sprintf(length,"%d",strlen(reply));

    s_sendmore(responder, length);
    s_send(responder, reply);
  }

  zmq_close (responder); 
  zmq_ctx_destroy (context); 
  return 0;
}
