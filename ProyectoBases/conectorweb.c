// conectorweb.c
// HTTP adapter in 0MQ
#include "zhelpers.h"

int main(void)
{
  //Contexto para el manejo de sockets
  void *ctx = zmq_ctx_new();

  //Servicio que permite recibir de los request web
  void *hserver = zmq_socket(ctx, ZMQ_STREAM);
  zmq_bind(hserver, "tcp://*:8080");

  //Socket para la comunicacion interna con los servicios para el envio de la informacion necesaria por parte de
  //los programas internos para procesar las consultas
  void *tserver = zmq_socket(ctx, ZMQ_REQ);
  zmq_connect(tserver, "tcp://localhost:5555");

  //Parametros para la configuracion de los sockets
  uint8_t id[256];
  size_t id_size = 256;
  char *line;
  int more;
  size_t more_size = sizeof(more);
  int length = 0;

  //Mensaje para indicar que el servidor se encuentra esperando consultas
  printf("Servidor iniciado para recibir consultas\n");

  while (1)
  {
    // first frame has ID, the next the request.
    id_size = zmq_recv(hserver, id, 256, 0);

    // Get HTTP request
    char *request = s_recv(hserver);
    printf("1: valor del request %s\n", request);
    free(request);

    request = s_recv(hserver);
    printf("2: valor del request %s\n", request);
    free(request);

    request = s_recv(hserver);
    printf("3: valor del request %s Perros ending\n", request);	

    char http_response[] =
        "HTTP/1.0 200 OK\n"
        "Connection: close\n"
        "Content-Type: text/html\n"
        "Content-Length:          ";

    //Recepcion del request para ser enviado a la programacion interna de la consulta
    s_send(tserver, request);

    line = s_recv(tserver);
    sscanf(line, "%d", &length);
    sprintf(http_response, "%d\n\n", length);

    //Envio de la informacion para los subscriptiores del servicio
    zmq_send(hserver, id, id_size, ZMQ_SNDMORE);
    zmq_send(hserver, http_response,
             strlen(http_response), ZMQ_SNDMORE);
    free(line);

    while (1)
    {
      //Mantiene el servicio de conector vivo para las demas consultas
      line = s_recv(tserver);
      zmq_send(hserver, id, id_size, ZMQ_SNDMORE);
      zmq_send(hserver, line, strlen(line), ZMQ_SNDMORE);
      free(line);

      zmq_getsockopt(tserver, ZMQ_RCVMORE, &more, &more_size);

      if (!more)
      {
        // Send a zero to close connection to client
        zmq_send(hserver, id, id_size, ZMQ_SNDMORE);
        zmq_send(hserver, NULL, 0, ZMQ_SNDMORE);
        break;
      }
    }
    free(request);
  }

  // Cierre de los servicios y sockets
  zmq_close(hserver);
  zmq_close(tserver);
  zmq_ctx_term(ctx);
  return 0;
}