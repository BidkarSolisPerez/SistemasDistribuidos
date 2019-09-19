#include <zhelpers.h>
#include <pthread.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define SA_CREATE 0
#define SA_INT 1
#define SA_FLOAT 2
#define SA_STRING 3

typedef int shared_array;

void* sa_arrays[50];
char* sa_names[50];
int sa_sizes[50];

int sa_length=0;

void* context;
void* requester;
void* receiver;

pthread_t worker;

shared_array _sa_create(char*,int,int);
void _sa_setFloat(shared_array, int, float);
void _sa_setInt(shared_array, int, int);
void _sa_setString(shared_array, int, char*);

static void * sa_update (void *context) {
  void *receiver = zmq_socket (context, ZMQ_PULL);
  zmq_connect (receiver, "tcp://localhost:5556");
  while (1) {
    char *string = s_recv (receiver);
    int cmmd,item1,item2;
    char* item3; 
    sscanf (string, "%d %d %d %s",  
       &cmmd, &item1, &item2, &item3);
    free (string); 
    s_send (receiver, "OK");
    if (cmmd==SA_CREATE)
      _sa_create(item3,item1,item2);
    else if (cmmd==SA_FLOAT)
      _sa_setFloat(item1,item2,atof(item3));
    else if (cmmd==SA_INT)
      _sa_setInt(item1,item2,atoi(item3));
    else if (cmmd==SA_STRING) 
      _sa_setString(item1,item2,item3);
  }
  zmq_close (receiver);
}

static void sa_init() {
  context = zmq_ctx_new();
  requester = zmq_socket(context, ZMQ_REQ);
  zmq_connect(requester, "tcp://localhost:5555");
  pthread_create(&worker, NULL, sa_update, context);
}

void sa_sendCmmd(int cmmd, int item1, int item2, char* item3) {
	char request[256];
	sprintf(request,"%d %d %d %s\0",cmmd,item1,item2,item3);
    s_send(requester, request);
    char* reply = s_recv(requester);
    free (reply);
}

shared_array _sa_create(char* name, int size, int type) {
	sa_names[sa_length] = name;
	sa_sizes[sa_length] = size;
	if (type==SA_STRING)
	  sa_arrays[sa_length] = malloc(sizeof(char)*size);
	else if (type==SA_FLOAT)
	  sa_arrays[sa_length] = malloc(sizeof(float)*size);
	else
	  sa_arrays[sa_length] = malloc(sizeof(int)*size);
	sa_length++;
	return sa_length-1;
}

shared_array sa_create(char* name, int size, int type) {
	int id = _sa_create(name, size, type);
	sa_sendCmmd(SA_CREATE,size,type,name);
	return id;
}

shared_array sa_attach(char* name) {
	for (int i=0; i<sa_length; i++)
	  if (strcmp(sa_names[i],name) == 0)
	    return i;
	return -1;
}

void sa_list() {
	for (int i=0; i<sa_length; i++)
	  printf("%s\n",sa_names[i]);
}

void sa_delete(char* name) {
	for (int i=0; i<sa_length; i++)
	  if (strcmp(sa_names[i],name) == 0) {
		  free(sa_names[i]);
		  sa_names[i] = NULL;
		  free(sa_arrays[i]);
		  sa_arrays[i] = NULL;
      }
}

void _sa_setFloat(shared_array array, int index, float value) {
  ((float*)sa_arrays[array])[index] = value;
}

void sa_setFloat(shared_array array, int index, float value) {
	_sa_setFloat(array,index,value);
    char str[20];
    sprintf(str, "%f", value);
	sa_sendCmmd(SA_FLOAT,array,index,str);
}

float sa_getFloat(shared_array array, int index) {
	return ((float*)sa_arrays[array])[index];
}

void _sa_setInt(shared_array array, int index, int value) {
	((int*)sa_arrays[array])[index] = value;
}

void sa_setInt(shared_array array, int index, int value) {
	sa_setInt(array, index, value);
	char str[20];
    sprintf(str, "%d", value);
	sa_sendCmmd(SA_INT,array,index,str);
}

int sa_getInt(shared_array array, int index) {
     return ((int*)sa_arrays[array])[index];
}

void _sa_setString(shared_array array, int index, char* value) {
	((char**)sa_arrays[array])[index] = value;
}

void sa_setString(shared_array array, int index, char* value) {
	_sa_setString(array, index, value);
	sa_sendCmmd(SA_STRING,array,index,value);
}

char* sa_getString(shared_array array, int index) {
	return ((char**)sa_arrays[array])[index];
}
