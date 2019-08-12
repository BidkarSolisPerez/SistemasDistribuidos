// Bingoclient.c
// Bingo client
// Connects SUB socket to tcp://localhost:5556
// Collects weather updates and finds avg temp in zipcode 
//
#include <zhelpers.h>

int validate(int card[], int number){
	for(int i = 0; i<25;i++){
		if(number == card[i]){			
			return 1;
		}
	}
	return 0;
}

int semilla(int card[], int number, int counter){
	for(int i = 0; i<25;i++){		
		if(number == card[i]){			
			return counter += 1;						
		}
	}
	return counter;
}

int main (int argc, char *argv []) {
  void *context = zmq_ctx_new ();
	
	int card[25];
//  Initialize random number generator
  srandom ((unsigned) time (NULL));	
	for(int i =0; i <25; i++){	
		int number = randof(101);
		while (validate(card,number)){			
			number = randof(101);
		}
		card[i]=number;
	}
	
	for(int i =0; i <25; i++){
		printf("Los valores del bingo son: %d\n",card[i]);
	}
	
  //  Socket to talk to server
  printf ("Collecting updates from weather server...\n"); 
  void *subscriber = zmq_socket (context, ZMQ_SUB);
  int rc = zmq_connect (subscriber, "tcp://localhost:5556"); 
  void* requester = zmq_socket(context, ZMQ_REQ);
  zmq_connect(requester, "tcp://localhost:5555");
  //assert (rc == 0);

  char *filter = "";
  rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter)); 
  //assert (rc == 0);

  int update_nbr;
  long number = 0;
  int ganador = 1;
  int counter = 0;
  while(ganador) {	  
    char *string = s_recv (subscriber,0);    
    sscanf (string, "%d",
       &number);  	   
    free (string);	
	if(number>=0){
		printf("Number: %d, Seed used: %d\n", number, counter);
		counter = semilla(card,number,counter);	
		if(counter == 25){			
			ganador = 0;
			char* bingo = "Bingo";
			s_send(requester, bingo);
			printf("After Send %s\n",bingo);
		}
	}
	else{
		ganador = 0;
		printf("Carton Lleno/n");
	}
  }  

  zmq_close (subscriber);
  zmq_close (requester);
  zmq_ctx_destroy (context); 
  
  printf("Bingo!!!!");
  
  getchar();
  return 0;
}
