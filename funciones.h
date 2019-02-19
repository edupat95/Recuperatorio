#ifndef FUNCIONESH
#define FUNCIONESH
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
char *ubicacion(char buffer[1024]);
char *protocolo(int i);
void proceso_archivo(char *ubicacion,void * connfd);
#endif
