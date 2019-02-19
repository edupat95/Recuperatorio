#include <string.h>
#include <fcntl.h>
#include "cliente.h"
#include "funciones.h"

void *servicio (void * connfd){
  int leido,fds;
  char buff[1024];
  fds = (intptr_t)connfd;

  printf ("-------LO QUE EL CLIENTE MANDA------");
  /*while((leido = read (fds,buff ,sizeof (buff))) > 0){ // muestro lo que tieen el archivo configuracion
  write(1,buff,leido);
  //write(1 ,buffer ,leido2);
}*/
leido = read (fds,buff ,sizeof (buff));
write(1,buff,leido);

printf ("-----Procesamos la info enviada, armando protoclo y abriendo archivo--------\n");
char *ubi=NULL, *proto=NULL;
ubi=ubicacion(buff);
printf("La ubicacion que pide el clientes es: %s\n",ubi);

if(ubi==NULL){
  proto=protocolo(1);
  write(fds,proto,strlen(proto));
  close(fds);
  return 0;
} else  {
  proto=protocolo(0);
}
printf("protocolo : %s\n",proto);

printf("------------------PROCESANDO ARCHIVO--------------------------\n");
proceso_archivo(ubi,(void *) (intptr_t) fds);
printf("--------------------------------------------\n");

printf("------------>ahora connfd vale %d\n",fds);
close(fds);
return 0;
}
