/* servTCPIt.c - Exemplu de server TCP iterativ
 *      Asteapta un nume de la clienti; intoarce clientului sirul
 *           "Hello nume".
 *                
 *                     Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
 *                     */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>

/* portul folosit */
#define PORT 2028

/* codul de eroare returnat de anumite apeluri */
extern int errno;

int main () {

    struct sockaddr_in server;  // structura folosita de server
    struct sockaddr_in from;  
    char msg[100];    //mesajul primit de la client 
    char msgrasp[100]=" ";        //mesaj de raspuns pentru client
    int sd;     //descriptorul de socket 

    /* crearea unui socket */
    if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1) {
        perror ("[server]Eroare la socket().\n");
        return errno;
    }   

    /* pregatirea structurilor de date */
    bzero (&server, sizeof (server));
    bzero (&from, sizeof (from));
    
    /* umplem structura folosita de server */
    /* stabilirea familiei de socket-uri */
    server.sin_family = AF_INET;  
    /* acceptam orice adresa */
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    /* utilizam un port utilizator */
    server.sin_port = htons (PORT);
    
    /* atasam socketul */
    if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1) {
        perror ("[server]Eroare la bind().\n");
        return errno;
    }

    /* punem serverul sa asculte daca vin clienti sa se conecteze */
    if (listen (sd, 5) == -1) {
        perror ("[server]Eroare la listen().\n");
        return errno;
    }
     int nr_client=0;
    /* servim in mod iterativ clientii... */
    while (1) {
        int client;
        socklen_t length = sizeof (from);

        printf ("[server]Asteptam la portul %d...\n",PORT);
        fflush (stdout);

        /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
        client = accept (sd, (struct sockaddr *) &from, &length);

         /* eroare la acceptarea conexiunii de la un client */
        if (client < 0) {
            perror ("[server]Eroare la accept().\n");
            continue;
        }
        else
        nr_client++;
        pid_t fiu=fork();
        if(fiu==0)
        {
        
        
            
        int var=1;
        while(var>=1)
        {
           
     
        /* s-a realizat conexiunea, se astepta mesajul */
        bzero(msg,100);
         
        
        /* citirea mesajului */
         var=read (client, msg, 100);
        if (var < 0) {
            perror ("[server]Eroare la read() de la client.\n");
            close (client); /* inchidem conexiunea cu clientul */
            continue;   /* continuam sa ascultam */
        }
        if(var==0)
        {
            printf("Conexiune inchisa\n");
            close(client);
            continue;
        }

       
        printf ("[Client %d]: %s\n",nr_client, msg);
            
        /*pregatim mesajul de raspuns */
        bzero(msgrasp,100);
        strcat(msgrasp,"Hello ");
        strcat(msgrasp,msg);
            
        
            
            
        /* returnam mesajul clientului */
        if (write (client, msgrasp, 100) <= 0) {
            perror ("[server]Eroare la write() catre client.\n");
            continue;   /* continuam sa ascultam */
        } 
            
      
        
        }
        close (client);
        exit(1);
        }        
            
            
        close(client);

    }       /* while */
}       /* main */
