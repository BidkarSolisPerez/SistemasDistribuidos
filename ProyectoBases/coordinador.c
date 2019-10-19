// taskserver.c
// Task server
// Binds REP socket to tcp://*:5555
//
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
    void *context = zmq_ctx_new();

    void *responder = zmq_socket(context, ZMQ_REP);
    zmq_bind(responder, "tcp://*:5555");

    char length[20];

    while (1)
    {

        char *request;
        request = s_recv(responder);
        if (request == NULL)
            continue;

        printf("Received in coordinator: %s\n", request);
        char *url = strtok(request, " ");

        printf("Request despues del strtok: %s\n", url);
        url = strtok(NULL, " ");
        printf("Request despues del strtok con NULL: %s\n", url);

        url = replaceWord(url, "/", "");
        printf("Url despues de replace: %s", url);

        printf("URL final: %s\n", url);

        free(request);

        char *reply = "Hello World";
        sprintf(length, "%d", strlen(reply));

        s_sendmore(responder, length);
        s_send(responder, reply);
    }

    zmq_close(responder);
    zmq_ctx_destroy(context);
    return 0;
}