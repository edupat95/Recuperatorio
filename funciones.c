#include "funciones.h"
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>

char *ubicacion(char buffer[1024]){
  char *ptr=NULL;//,*ptr2=NULL,*parte1=NULL,*parte2=NULL,ubicacion[30],*ubi=NULL;
  ptr = strtok( buffer, " \n\t\0/" );    // Primera llamada => Primer token
  printf("PRIMERO TOQUEN-----> %s\n",ptr);
  ptr = strtok( NULL, " \n\t\0/");
  printf("SEGUNDO TOQUEN-----> %s\n",ptr);
  /*ptr2 = strtok(ptr,"/");
  parte1=ptr2;
  printf("TERCER TOQUEN-----> %s\n",ptr2);
  ptr2=strtok(NULL,"/");
  printf("CUARTO TOQUEN-----> %s\n",ptr2);
  parte2=ptr2;
  printf("PARTE 1: %s --- PARTE 2: %s \n",parte1,parte2);
  strcpy(ubicacion,parte1);
  strcat(ubicacion,"/");
  strcat(ubicacion,parte2);
  printf("UBICACION EN FUNCION UBICACION: %s\n",ubicacion);
  strcat(ubi,ubicacion);
  printf("UBI EN FUNCION UBICACion: %s\n",ubi);*/
  return ptr;
}

char *protocolo(int i){
  char *protocolo=NULL;
  if(i==1){
    protocolo="HTTP 404 Not Found\n\n\n";
  } else {
    protocolo="HTTP/1.1 200 OK\nContent-Type: text/html\n\n\n";
  }
  return protocolo;
}

void proceso_archivo(char *ubicacion,void * connfd){
  int fds=0 ,tam=0  ,fda=0,leido=0;
  fds = (intptr_t)connfd;
  printf("--------------FUNCION PROCESO_ARCHIVO DONDE HAY VIOLACION DE SEGMENTO-----------------\n");
  printf("--->ubicacion: %s\n",ubicacion);
  printf("--->connfds: %d\n",fds);
  tam=strlen(ubicacion);
  char buffer[1024],aux[tam-1],*ptr=NULL,*p1=NULL,*dato_extra=NULL,*numero_usuario=NULL;
  ptr = strtok(ubicacion,"/");
  p1=ptr;
  strcpy(aux,p1);
  strcat(aux,"/");
  strcat(aux,"usuario.txt");
  printf ("La ubicacion donde se busca es: %s y el tamaño es: %d\n",aux,tam);

  ptr = strtok(NULL,"/");
  numero_usuario=ptr;
  if((ptr=strtok(NULL,"/"))!=NULL){
    dato_extra=ptr;
    printf("Y el pedido que realiza el cliente es el siguiente: %s y dato extra: %s \n",numero_usuario,dato_extra);
  }else{
    printf("Y el pedido que realiza el cliente es el siguiente: %s \n",numero_usuario);
  }

  printf ("AUX = %s\n",aux);

  fda = open(aux,O_RDONLY,0666); //abro archivo de configuracion
  if(fda==-1){
    protocolo(0);
  }//fda = open ("cpu/info",O_RDONLY,0666); // HARDCODEO EL NOMBRE DE LA UBICACION PARA CORROBORAR QUE ES CORRECTA
  char *ptr1=NULL;
  //int contador=0;
  char *nombre=NULL,*email=NULL,*tel=NULL,*ciudad=NULL,*cp=NULL;
  while((leido = read (fda,buffer ,sizeof (buffer))) > 0){ // muestro lo que tiene el archivo configuracion
    //write(fds ,buffer ,leido); //enviamos el archivo entero
    ptr1=strtok(buffer,"|");
    printf("primer token: -%s-\npero numero usuario: -%s-\n",ptr1,numero_usuario);
    if(*ptr1==*numero_usuario){
      printf("Entro al primer if y dato extra %s \n",dato_extra);
      //write(fds,numero_usuario,strlen(numero_usuario));
      if(dato_extra==NULL){
        printf("Entra al segundo if\n");
        if((ptr1=strtok(NULL,"|"))!=NULL){
          nombre=ptr1;
          printf ("nombre= %s\n",nombre);
          ptr1=strtok(NULL,"|");
          email=ptr1;
          printf ("email= %s\n",email);
          ptr1=strtok(NULL,"|");
          tel=ptr1;
          printf ("tel= %s\n",tel);
          ptr1=strtok(NULL,"|");
          ciudad=ptr1;
          printf ("ciudad= %s\n",ciudad);
          ptr1=strtok(NULL,"|");
          cp=ptr1;
          printf ("cp= %s\n",cp);
          int tam_aux=strlen(nombre)+strlen(email)+strlen(tel)+strlen(ciudad)+strlen(cp);
          char aux_mostrar[tam_aux];
          strcpy(aux_mostrar,nombre);
          strcat(aux_mostrar," ");
          strcat(aux_mostrar,email);
          strcat(aux_mostrar," ");
          strcat(aux_mostrar,tel);
          strcat(aux_mostrar," ");
          strcat(aux_mostrar,ciudad);
          strcat(aux_mostrar," ");
          strcat(aux_mostrar,cp);
          strcat(aux_mostrar,"\n");
          printf("AUX VALE %s",aux_mostrar);
          write(fds,aux_mostrar,strlen(aux_mostrar));
        }
      } else {
          printf("Entra al else\n");
          char *n="nombre", *e="email", *t="tel", *c="ciudad", *cp="cp";
          if(*dato_extra==*n){
            ptr1=strtok(NULL,"|");
            nombre=ptr1;
            printf("nombre= %s",nombre);
            int tam_aux=strlen(nombre);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          } else if(*dato_extra==*e){
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            nombre=ptr1;
            printf("email= %s",nombre);
            int tam_aux=strlen(nombre);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          }else if(*dato_extra==*t){
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            nombre=ptr1;
            printf("tel= %s",nombre);
            int tam_aux=strlen(nombre);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          }else if(*dato_extra==*c){
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            nombre=ptr1;
            printf("ciudad= %s",nombre);
            int tam_aux=strlen(nombre);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          }else if(*dato_extra==*cp){
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            nombre=ptr1;
            printf("cp= %s",nombre);
            int tam_aux=strlen(nombre);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          }
        }
    }

    while((ptr1=strtok(NULL,"|"))!=NULL){
      if(*ptr1==*numero_usuario){
        //printf("Entra porque %d es igual a %d ",strlen(ptr1),strlen(numero_usuario));
        if(dato_extra==NULL){
          printf("Entra al segundo if\n");
          if((ptr1=strtok(NULL,"|"))!=NULL){
            nombre=ptr1;
            printf ("nombre= %s\n",nombre);
            ptr1=strtok(NULL,"|");
            email=ptr1;
            printf ("email= %s\n",email);
            ptr1=strtok(NULL,"|");
            tel=ptr1;
            printf ("tel= %s\n",tel);
            ptr1=strtok(NULL,"|");
            ciudad=ptr1;
            printf ("ciudad= %s\n",ciudad);
            ptr1=strtok(NULL,"|");
            cp=ptr1;
            printf ("cp= %s\n",cp);
            int tam_aux=strlen(nombre)+strlen(email)+strlen(tel)+strlen(ciudad)+strlen(cp);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            strcat(aux_mostrar," ");
            strcat(aux_mostrar,email);
            strcat(aux_mostrar," ");
            strcat(aux_mostrar,tel);
            strcat(aux_mostrar," ");
            strcat(aux_mostrar,ciudad);
            strcat(aux_mostrar," ");
            strcat(aux_mostrar,cp);
            strcat(aux_mostrar,"\n");
            printf("AUX VALE %s",aux_mostrar);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          }
        } else {
          printf("Entra al else\n");
          char *n="nombre", *e="email", *t="tel", *c="ciudad", *cp="cp";
          if(*dato_extra==*n){
            ptr1=strtok(NULL,"|");
            nombre=ptr1;
            printf("nombre= %s",nombre);
            int tam_aux=strlen(nombre);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          } else if(*dato_extra==*e){
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            nombre=ptr1;
            printf("email= %s",nombre);
            int tam_aux=strlen(nombre);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          }else if(*dato_extra==*t){
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            nombre=ptr1;
            printf("tel= %s",nombre);
            int tam_aux=strlen(nombre);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          }else if(*dato_extra==*c){
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            nombre=ptr1;
            printf("ciudad= %s",nombre);
            int tam_aux=strlen(nombre);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          }else if(*dato_extra==*cp){
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            ptr1=strtok(NULL,"|");
            nombre=ptr1;
            printf("cp= %s",nombre);
            int tam_aux=strlen(nombre);
            char aux_mostrar[tam_aux];
            strcpy(aux_mostrar,nombre);
            write(fds,aux_mostrar,strlen(aux_mostrar));
          }
        }
      }
    }

  }
}
