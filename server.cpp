/* servTCPConcTh2.c - Exemplu de server TCP concurent care deserveste clientii
   prin crearea unui thread pentru fiecare client.
   Asteapta un numar de la clienti si intoarce clientilor numarul incrementat.
	Intoarce corect identificatorul din program al thread-ului.
  
   
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <algorithm>    
#include <vector>       
#include <ctime>        
#include <cstdlib>
#include "select.h"
/* portul folosit */
#define PORT 2907

/* codul de eroare returnat de anumite apeluri */
extern int errno;
sqlite3* db;
class thData
{

public:
  int idThread; //id-ul thread-ului tinut in evidenta de acest program
  int cl;       //descriptorul intors de accept
public:
  thData(int idThread, int cl);
  thData(thData *ptr);
};
thData::thData(int idThread, int cl)
{
  this->idThread = idThread;
  this->cl = cl;
}

thData::thData(thData *ptr)
{
  this->idThread = ptr->idThread;
  this->cl = ptr->cl;
}
static void *treat(void *); /* functia executata de fiecare thread ce realizeaza comunicarea cu clientii */
void raspunde(void *);

int main()
{
  struct sockaddr_in server; // structura folosita de server
  struct sockaddr_in from;
  int nr; //mesajul primit de trimis la client
  int sd; //descriptorul de socket
  int pid;
  pthread_t th[100]; //Identificatorii thread-urilor care se vor crea
  int i = 0;
  db = openDatabase();

  /* crearea unui socket */
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("[server]Eroare la socket().\n");
    return errno;
  }
  /* utilizarea optiunii SO_REUSEADDR */
  int on = 1;
  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

  /* pregatirea structurilor de date */
  bzero(&server, sizeof(server));
  bzero(&from, sizeof(from));

  /* umplem structura folosita de server */
  /* stabilirea familiei de socket-uri */
  server.sin_family = AF_INET;
  /* acceptam orice adresa */
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  /* utilizam un port utilizator */
  server.sin_port = htons(PORT);

  /* atasam socketul */
  if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
  {
    perror("[server]Eroare la bind().\n");
    return errno;
  }

  /* punem serverul sa asculte daca vin clienti sa se conecteze */
  if (listen(sd, 2) == -1)
  {
    perror("[server]Eroare la listen().\n");
    return errno;
  }

   std::srand ( unsigned ( std::time(0) ) );
  
  /* servim in mod concurent clientii...folosind thread-uri */
  while (1)
  {
    int client;
    socklen_t length = sizeof(from);

    printf("[server]Asteptam la portul %d...\n", PORT);
    fflush(stdout);

    //client= malloc(sizeof(int));
    /* acceptam un client (stare blocanta pina la realizarea conexiunii) */
    if ((client = accept(sd, (struct sockaddr *)&from, &length)) < 0)
    {
      perror("[server]Eroare la accept().\n");
      continue;
    }

    /* s-a realizat conexiunea, se astepta mesajul */

    thData td(i++, client);
    thData *ptr = &td;
    pthread_create(&th[i], NULL, &treat, ptr);
    printf("Am %d thread-uri\n",i);
  } //while
};

static void *treat(void *arg)
{
  thData td((thData *)arg);
  printf("Utilizatorul %d este conectat \n", td.idThread);
  fflush(stdout);
  pthread_detach(pthread_self());
  raspunde((thData *)arg);
  /* am terminat cu acest client, inchidem conexiunea */
  close((intptr_t)arg);
  return (NULL);
};

void raspunde(void *arg)
{
  int nr = 0, i = 0;
  int index = 5;
  char answer;
  thData tdL((thData *)arg);
  int ordine[100];
  for(int i=0;i<index;i++)
   ordine[i]=i+1;
  
   std::random_shuffle(ordine, ordine+index-1);
  int punctaj = 0;
  char question1[1000];
  char *question;
  if (write(tdL.cl, &index, sizeof(int)) <= 0)
  {
    printf("[Thread %d] ", tdL.idThread);
    perror("[Thread]Eroare la write() catre client.\n");
  }

  for (int i = 0; i<index; i++)
  {
    Question q = selectDatabase(ordine[i], db);
    question = q.Prepare();
    strcat(question, "\0");

    sprintf(question1, "%s", question);
    nr = strlen(question1);
    if (write(tdL.cl, &nr, sizeof(int)) <= 0)
    {
      printf("[Thread %d] ", tdL.idThread);
      perror("[Thread]Eroare la write() catre client.\n");
    }

    if (write(tdL.cl, question1, nr) <= 0)
    {
      printf("[Thread %d] ", tdL.idThread);
      perror("[Thread]Eroare la write() catre client.\n");
    }

    if (read(tdL.cl, &answer, sizeof(char)) <= 0)
    {
      printf("[Thread %d]\n", tdL.idThread);
      perror("Eroare la read() de la client.\n");
    }
    printf("Raspunsul utilizatorului %d: %c\n", tdL.idThread, answer);
    char right = q.Verify(answer);
    if (right == 'Y')
      punctaj = punctaj + 1;
    if (write(tdL.cl, &right, sizeof(char)) <= 0)
    {
      printf("[Thread %d] ", tdL.idThread);
      perror("[Thread]Eroare la write() catre client.\n");
    }
  }
  if (write(tdL.cl, &punctaj, sizeof(int)) <= 0)
    {
      printf("[Thread %d] ", tdL.idThread);
      perror("[Thread]Eroare la write() catre client.\n");
    }
}
