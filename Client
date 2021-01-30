
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

extern int errno;

int port;
void conversieoutput(int x)
{
  if (x == -1)
    printf("\x1b[31m"
           "|R| "
           "\x1b[0m");
  else if (x == 1)
    printf("\x1b[33m"
           "|G| "
           "\x1b[0m");
  else
    printf("\x1b[30m" "|O| " "\x1b[0m");
}
void afisare(int tablajoc[6][7])
{
  printf("\x1b[32m");
  printf("                         |A| |B| |C| |D| |E| |F| |G|\n");
  printf("                         ___________________________\n");
  printf("\x1b[0m");
  for (int i = 0; i < 6; i++)
  {
    printf("                         ");
    {
      for (int j = 0; j < 7; j++)
        conversieoutput(tablajoc[i][j]);
      printf("\n");
    }
  }
  printf("\x1b[32m");
  printf("                         ___________________________\n");
  printf("                         |A| |B| |C| |D| |E| |F| |G|\n\n");
  printf("\x1b[0m");
}

int main(int argc, char *argv[])
{
  system("clear");
  int sd, runda = 0;
  struct sockaddr_in server;
  char nickname[100];
  char coloana[10];
  int plin, nimic, gresit;
  int matrice[6][7];
  int castigator = 3;
  char continua[4];
  int continuare = 4;
  int scorpersonal = 0, scoradversar = 0;
  int culoare;

  if (argc != 3)
  {
    printf("Ati introdus sintaxa gresit! Sintaxa trebuie sa fie : %s <adresa_server> <port>\n", argv[0]);
    return -1;
  }

  port = atoi(argv[2]);

  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("Eroare la crearea socket-ului.\n");
    return errno;
  }

  server.sin_family = AF_INET;

  server.sin_addr.s_addr = inet_addr(argv[1]);

  server.sin_port = htons(port);

  if (connect(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
  {
    perror("Eroare la conectarea la server!\n");
    return errno;
  }
  printf("\x1b[34m");
  printf("             ***********************************************\n\n");
  printf("             ************   BINE ATI VENIT LA   ************\n\n");
  printf("             **************   CONNECT FOUR   ***************\n\n");
  printf("             ***********************************************\n\n");
  printf("\x1b[0m");
  sleep(1);
  printf("Va rugam sa introduceti un nickname (max 10 caractere):   ");
  printf("\x1b[36m");
  bzero(nickname, 10);
  fflush(stdout);
  read(0, nickname, 10);
  printf("\n");
  printf("\x1b[0m");
  printf("Asteptati pentru a va primi adversarul!\n\n");
  write(sd, nickname, 10);
  bzero(nickname, 10);
  read(sd, nickname, 10);
  printf("Jucati Impotriva lui :  %s\n", nickname);
  read(sd, &runda, sizeof(int));
  culoare = runda;
  if (runda == 1)
  {
    printf("\x1b[33m");
    printf("Jucati cu culoarea GALBEN si incepeti!\n");
    printf("\x1b[0m");
  }

  else
  {
    printf("\x1b[31m");
    printf("Jucati cu culoarea ROSU si adversarul incepe!\n");
    printf("\x1b[0m");
  }

  sleep(2);
rejoaca:
  sleep(2);
  culoare = (culoare == 1 ? -1 : 1);
  gresit = 4;
  plin = 4;
  continuare = 4;
  castigator = 10;
  fflush(stdout);
  bzero(coloana, 10);
  while (1)
  {
    system("clear");
    printf("\x1b[34m");
    printf("             ********   DUMNEAVOASTRA  -  ADVERSAR   ********\n\n");
    printf("             ***********    %d         -     %d     ***********\n\n", scorpersonal, scoradversar);
    printf("\x1b[0m");
    bzero(coloana, 10);
    for (int i = 0; i < 6; i++)
      for (int j = 0; j < 7; j++)
        read(sd, &matrice[i][j], sizeof(int));
    read(sd, &runda, sizeof(int));
    afisare(matrice);

    if (runda == 1)
    {
      if (culoare == -1)
      {
        printf("\x1b[33m");
        printf("Jucati cu culoarea GALBEN!\n");
        printf("\x1b[0m");
      }
      else
      {
        printf("\x1b[31m");
        printf("Jucati cu culoarea ROSU!\n");
        printf("\x1b[0m");
      }
      printf("Introduceti coloana pe care doriti sa adaugati:   ");
    greseala1:

      plin = 0;
      gresit = 0;
      printf("\x1b[36m");
      fflush(stdout);
      bzero(coloana, 10);

      read(0, coloana, 10);

      printf("\n");
      printf("\x1b[0m");
      write(sd, coloana, 10);
      read(sd, &gresit, sizeof(int));
      if (gresit == 3)
      {
        printf("Ati introdus coloana in formatul gresit, Reincercati:    ");
        sleep(2);
        goto greseala1;
      }
      read(sd, &plin, sizeof(int));
      if (plin == 3)
      {
        printf("Coloana pe care doriti sa introduceti este plina, Reincercati:    ");
        sleep(2);
        goto greseala1;
      }
      read(sd, &castigator, sizeof(int));
      if (castigator == 4)
      {
        system("clear");
        scorpersonal++;
        printf("             ********   DUMNEAVOASTRA  -  ADVERSAR   ********\n\n");
        printf("             ***********    %d         -     %d     ***********\n\n", scorpersonal, scoradversar);
        for (int i = 0; i < 6; i++)
          for (int j = 0; j < 7; j++)
            read(sd, &matrice[i][j], sizeof(int));
        afisare(matrice);

        printf("Felicitari ati castigat!\n");
        printf("Scorul este Dumneavoastra %d-%d Adversar!\n", scorpersonal, scoradversar);
        printf("Introduceti 'play' daca doriti sa rejucati sau altceva pentru a iesi:  ");
        fflush(stdout);
        bzero(continua, 4);
        read(0, continua, 4);
        printf("\nAsteptati raspunsul adversarului!\n");

        write(sd, continua, 4);
        sleep(2);
        read(sd, &continuare, sizeof(int));
        if (continuare == 5)
        {
          system("clear");
          printf("*************************************************\n\n");
          printf("*************************************************\n\n");
          printf("*************************************************\n\n");
          printf("************   VA INCEPE IN CURAND   ************\n\n");
          printf("*****************   NOUL MECI   *****************\n\n");
          printf("************************************************\n\n");
          printf("*************************************************\n\n");
          printf("*************************************************\n\n");
          sleep(3);
          fflush(stdout);
          bzero(coloana, 10);
          goto rejoaca;
        }
        else
        {
          system("clear");
          printf("************************************************\n\n");
          printf("************************************************\n\n");
          printf("************************************************\n\n");
          printf("************   DVS SAU ADVERSARUL   ************\n\n");
          printf("***************   ATI PARASIT   ****************\n\n");
          printf("************************************************\n\n");
          printf("************************************************\n\n");
          printf("************************************************\n\n");
          exit(0);
        }

        sleep(10);
      }
      sleep(2);
      continue;
    }
    else
    {
      plin = 0;
      gresit = 0;
      if (culoare == -1)
      {
        printf("\x1b[33m");
        printf("Jucati cu culoarea GALBEN!\n");
        printf("\x1b[0m");
      }
      else
      {
        printf("\x1b[31m");
        printf("Jucati cu culoarea ROSU!\n");
        printf("\x1b[0m");
      }
      printf("Nu este runda dumneavoastra! Va rugam asteptati!\n");
    greseala2:

      fflush(stdout);
      read(sd, &gresit, sizeof(int));

      if (gresit == 3)
      {
        printf("Adversarul a facut o greseala! Va rugam asteptati in continuare!\n");
        sleep(2);
        goto greseala2;
      }
      read(sd, &plin, sizeof(int));
      if (plin == 3)
      {
        printf("Adversarul a introdus o coloana deja plina! Va rugam asteptati in continuare!\n");
        sleep(2);
        goto greseala2;
      }
      read(sd, &castigator, sizeof(int));
      if (castigator == 4)
      {
        scoradversar++;
        system("clear");
        printf("             ********   DUMNEAVOASTRA  -  ADVERSAR   ********\n\n");
        printf("             ***********    %d         -     %d     ***********\n\n", scorpersonal, scoradversar);
        for (int i = 0; i < 6; i++)
          for (int j = 0; j < 7; j++)
            read(sd, &matrice[i][j], sizeof(int));
        afisare(matrice);

        printf("Scorul este Dumneavoastra %d-%d Adversar!\n", scorpersonal, scoradversar);
        printf("Din pacate ati pierdut!\n");
        printf("Introduceti 'play' daca doriti sa rejucati sau altceva pentru a iesi:  ");
        fflush(stdout);
        bzero(continua, 4);
        read(0, continua, 4);
        printf("\nAsteptati raspunsul adversarului!\n");

        write(sd, continua, 4);
        sleep(2);
        read(sd, &continuare, sizeof(int));
        if (continuare == 5)
        {
          system("clear");
          printf("*************************************************\n\n");
          printf("*************************************************\n\n");
          printf("*************************************************\n\n");
          printf("************   VA INCEPE IN CURAND   ************\n\n");
          printf("*****************   NOUL MECI   *****************\n\n");
          printf("************************************************\n\n");
          printf("*************************************************\n\n");
          printf("*************************************************\n\n");
          sleep(3);
          fflush(stdout);
          bzero(coloana, 10);

          goto rejoaca;
        }
        else
        {
          system("clear");
          printf("************************************************\n\n");
          printf("************************************************\n\n");
          printf("************************************************\n\n");
          printf("************   DVS SAU ADVERSARUL   ************\n\n");
          printf("***************   ATI PARASIT   ****************\n\n");
          printf("************************************************\n\n");
          printf("************************************************\n\n");
          printf("************************************************\n\n");
          exit(0);
        }
      }
      sleep(2);
      continue;
    }
  }

  close(sd);
}
