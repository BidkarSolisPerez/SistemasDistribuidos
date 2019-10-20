// coordinador.c
// Publisher coordinador server
// Binds REP socket to tcp://*:5555
#include <zhelpers.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Function to replace a string with another
// string
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
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);

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

int main(void)
{
    //Context
    void *context = zmq_ctx_new();

    //Socket para comunicar con el adapter
    void *responder = zmq_socket(context, ZMQ_REP);
    zmq_bind(responder, "tcp://*:5555");

    //Socket Publisher
    void *contextPub = zmq_ctx_new();
    void *publisher = zmq_socket(contextPub, ZMQ_PUB);
    int rc = zmq_bind(publisher, "tcp://*:5556");
    rc = zmq_bind(publisher, "ipc://weather.ipc");

    char length[20];

    printf("Coordinador web esperando la informacion de la consulta HTTP");
    //Bucle para mantener vivo el servicio
    while (1)
    {

        //Variale para recibir la informacion de la consulta
        char *request;
        request = s_recv(responder);
        /*
        request = replaceWord(request, "%7B", "");
        request = replaceWord(request, "%7D", "");
        */
        if (request == NULL)
            continue;

        // Imprime lo que trae la consulta
        printf("Received in coordinator: %s\n", request);

        //Metodo utilizado para obtener el tipo de request y se almacena en la variable requestType
        char *url = strtok(request, " ");
        char *requestType;
        char *id;

        //Variable para almacenar el tipo de request HTTP
        requestType = url;

        //A partir de aca seguimos filtrando la informacion para obtener el nombre de la base de datos y la informacion necesaria
        //para formatear el query para la ejecucion en la base de datos por medio del servidor web
        printf("Request despues del primer strtok: %s\n", url);
        url = strtok(NULL, " ");

        printf("Tipo de request: %s\n", requestType);

        url = strtok(url, "/");
        printf("Request despues del segundo strtok: %s\n", url);

        url = strtok(NULL, "/");
        printf("Request despues del tercer strtok: %s\n", url);

        id = strtok(NULL, "/");
        printf("Valor de ID: %s\n", id);

        printf("Request despues del strtok con NULL: %s\n", url);

        //Concatenamos la informacion necesaria para enviarla a los subscriptores
        strcat(requestType, ",");
        strcat(requestType, url);

        // Algunas veces vienen los ID para consultas individiales, se obtinen aca y se hace la concatenacion si
        //la variable id obtine algun valor
        if (id != NULL)
        {
            strcat(requestType, ",");
            strcat(requestType, id);
        }

        //Imprimimos el url y el request que vamos enviar al servidor web
        printf("Url despues de replace: %s\n", url);
        printf("Statement: %s\n", requestType);

        //Envia la informacion a los subscriptores para que realicen el trabajo dependiendo de la informacion enviada
        s_send(publisher, requestType);

        free(request);

        //Reply que recibe el conector web cuando finaliza las consultas
        char *reply = "Hello World";
        sprintf(length, "%d", strlen(reply));

        s_sendmore(responder, length);
        s_send(responder, reply);
    }

    //Cierre de los recursos para la los sockets
    zmq_close(responder);
    zmq_close(publisher);
    zmq_ctx_destroy(context);
    zmq_ctx_destroy(contextPub);
    return 0;
}