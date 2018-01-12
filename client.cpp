/* cliTCPIt.c - Exemplu de client TCP
   Trimite un numar la server; primeste de la server numarul incrementat.
         
   Autor: Lenuta Alboaie  <adria@infoiasi.ro> (c)2009
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

/* codul de eroare returnat de anumite apeluri */
extern int errno;

/* portul de conectare la server*/
int port,sd;
char answer;
pid_t pid; 



void handler2(int sig)
{
  
  answer='O';
  if (write(sd, &answer, sizeof(char)) <= 0)
    {
      perror("[client]Eroare la write() spre server.\n");
    }
  if(kill(pid,SIGUSR1)==-1) 
	    	{
	        perror("Eroare la transmiterea semnalului\n");
	        exit(2);
        }
  
}

void showQuestion(char question[1000], int nr,int i, int index)
{
  printf("Intrebare %d/%d:\n",i,index);
  for (int i = 0; i < nr; i++)
  {
    if (question[i] == '~')
      printf("\n");
    else
      printf("%c", question[i]);
  }
  printf("\n");
}
int main(int argc, char *argv[])
{
  struct sockaddr_in server; // structura folosita pentru conectare
      // mesajul trimis

  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
  {
    printf("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
    return -1;
  }

  /* stabilim portul */
  port = atoi(argv[2]);

  /* cream socketul */
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Eroare la socket().\n");
    return errno;
  }

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons(port);

  /* ne conectam la server */
  if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
  {
    perror("[client]Eroare la connect().\n");
    return errno;
  }


  if(signal(SIGALRM,handler2)==SIG_ERR)
	   	   {
	   	   perror("Eroare la prinderea semnalului\n");
	   	   exit(1);
	   	   }	   	   


  char username[20],winner[20];
  int win;
  system("clear");
  printf("QUIZZGAME\nIn jocul QuizzGame vei primi un set de intrebari la care trebuie sa raspunzi.\nPentru fiecare intrebare ai la dispozitie 10 secunde.\nLa finalul rundei vei afla scorul tau si cine a castigat.\n");
  printf("Te rog sa iti introduci usernameul: \n");
  scanf("%s", username);
  system("clear");
  if (write(sd, username, 20) <= 0)
  {
    perror("[client]Eroare la write() spre server.\n");
    return errno;
    exit(1);
  }
  int nr, index, punctaj;
  char enter;
  if (read(sd, &index, sizeof(int)) < 0)
  {
    perror("[client]Eroare la read() de la server.\n");
    return errno;
    exit(1);
  }
  for (int i = 1; i <= index; i++)
  {
    char question[1000];
    if (read(sd, &nr, sizeof(int)) < 0)
    {
      perror("[client]Eroare la read() de la server.\n");
      return errno;
      exit(1);
    }
    if (read(sd, question, nr) < 0)
    {
      perror("[client]Eroare la read() de la server.\n");
      return errno;
      exit(1);
    }

    showQuestion(question, nr,i,index);
    /* citirea mesajului */
    printf("Care crezi ca e raspunsul?\n");
    fflush(stdout);

 pid=fork();
 if(pid==-1)
	{
	perror("Eroare la apelul fork");
	return 1;
	}
	else
	if(pid==0)
		{
     
		      read(0, &answer, sizeof(char));
          read(0, &enter, sizeof(char));
          if (write(sd, &answer, sizeof(char)) <= 0)
            {
              perror("[client]Eroare la write() spre server.\n");
              return errno;
            }
	    exit(1);
     }
        else
        {
          alarm(10);
          wait(NULL);
        }
    

    /* trimiterea mesajului la server */
    
    char right;
    if (read(sd, &right, sizeof(char)) < 0)
    {
      perror("[client]Eroare la read() de la server.\n");
      return errno;
      exit(1);
    }
    system("clear");
    if (right == 'Y')
      printf("Raspunsul este corect.\n\n");
    else
     if(right == 'O')
      printf("Imi pare rau,a expirat timpul pentru  intrebare.\n\n");
      else
      printf("Raspunsul este gresit.\n\n");
      
  }
  
  if (read(sd, &win, sizeof(int)) < 0)
  {
    perror("[client]Eroare la read() de la server.\n");
    return errno;
    exit(1);
  }
  if (read(sd, &winner, 20) < 0)
  {
    perror("[client]Eroare la read() de la server.\n");
    return errno;
    exit(1);
  } 
  if (read(sd, &punctaj, sizeof(int)) < 0)
  {
    perror("[client]Eroare la read() de la server.\n");
    return errno;
    exit(1);
  }
  if(win==punctaj)
  printf("Felicitari!%s, ai castigat jocul cu %d puncte.\n",username,punctaj);
  else
  {
  printf("Jocul este gata.%s a castigat jocul cu %d puncte.\n",winner,win);
  printf("%s, ai obtinut %d puncte.Bravo!\n", username, punctaj);
  }
/* inchidem conexiunea, am terminat */
  close(sd);
}
