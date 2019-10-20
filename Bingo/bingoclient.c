// wuclient.c
// Weather update client
// Connects SUB socket to tcp://localhost:5556
// Collects weather updates and finds avg temp in zipcode
//
#include <zhelpers.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
  void *context = zmq_ctx_new();
  int count = 0;
  int carton[24];

  //  Socket to talk to server
  printf("Collecting updates from weather server...\n");

  void *subscriber = zmq_socket(context, ZMQ_SUB);
  int rc = zmq_connect(subscriber, "tcp://localhost:5556");
  //assert (rc == 0);

  //  Initialize random number generator
  srandom((unsigned)time(NULL));

  for (int i = 0; i < 25; i++)
  {
    carton[i] = randof(100);
    printf("%d y valor en el carton: %d\n", i, carton[i]);
  }

  char *filter = (argc > 1) ? argv[1] : "";
  rc = zmq_setsockopt(subscriber, ZMQ_SUBSCRIBE, filter, strlen(filter));

  //  Process 100 updates
  while (count < 25)
  {
    char *string = s_recv(subscriber);

    int number;
    sscanf(string, "%d",
           &number);
    printf("\n\nNumber was: %d\n\n", number);
    free(string);

    for (int i = 0; i < 25; i++)
    {
      printf("\nValor del numero es: %d, valor del carton: %d", number, carton[i]);
      if (carton[i] == number)
      {
        carton[i] = -1;
      }
    }
    count = 0;
    for (int i = 0; i < 25; i++)
    {
      if (carton[i] == -1)
      {
        count++;
      }
    }

    sleep(10);
  }
  printf("\nCarton lleno!!!");
  getchar();
  zmq_close(subscriber);
  zmq_ctx_destroy(context);
  getchar();
  return 0;
}
