// hwclient.c
// Hello World client
// Connects REQ socket to tcp://localhost:5555 
// Sends "Hello" to server, expects "World" back 
//
#include <zhelpers.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

int main () {
  void* context = zmq_ctx_new();

  // Socket to talk to server
  puts("Connecting to server...");
  void* requester = zmq_socket(context, ZMQ_REQ);
  zmq_connect(requester, "tcp://localhost:5555");

  for (int request_nbr = 0; request_nbr != 40; request_nbr++) {
    
    sleep(1);
    if((request_nbr%10 == 0) && (request_nbr > 0)){
        printf("Entro al if\n");
        char* request = "Puedo continuar?\n";
        s_send(requester, request);

        char* reply;
        reply = s_recv(requester);
        printf("Received %s %d\n", reply, request_nbr);

        printf("Antes del while\n");
        
        int espera = 0;

        while(strcmp(reply,"N") == 0){
            espera++;
            printf("En el while\n");
            char * request = "ahora";
            if(espera > 15){
                request = "Esperado mucho\n";
            }
            s_send(requester, request);
            printf("Request value %s\n",request);

            sleep(1);
            free(reply);

            char* reply;
            reply = s_recv(requester);
            printf("Received %s %d\n", reply, request_nbr);
            if(strcmp(reply,"S") == 0){
                break;
            }
            
        }
        
        free(reply);
    }

    printf("Conteo: %d\n",request_nbr);
  }
  zmq_close(requester);
  zmq_ctx_destroy(context);
}