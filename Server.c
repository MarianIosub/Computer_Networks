
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 2024
void reinitializare(int tablajoc[6][7])
{
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 7; j++)
			tablajoc[i][j] = 0;
}
int randomizer()
{
	time_t t;
	srand((unsigned)time(&t));
	if (rand() % 2 == 0)
		return -1;
	else
		return 1;
}
void adaugare(int tablajoc[6][7], int ok, int coloana)
{
	for (int i = 5; i >= 0; i--)
	{
		if (tablajoc[i][coloana] == 0)
		{
			tablajoc[i][coloana] = ok;
			break;
		}
	}
}
int conversiecoloana(char x[1])
{
	if (strcmp(x, "a") == 0 || strcmp(x, "A") == 0)
		return 0;
	else if (strcmp(x, "b") == 0 || strcmp(x, "B") == 0)
		return 1;
	else if (strcmp(x, "c") == 0 || strcmp(x, "C") == 0)
		return 2;
	else if (strcmp(x, "d") == 0 || strcmp(x, "D") == 0)
		return 3;
	else if (strcmp(x, "e") == 0 || strcmp(x, "E") == 0)
		return 4;
	else if (strcmp(x, "f") == 0 || strcmp(x, "F") == 0)
		return 5;
	else if (strcmp(x, "g") == 0 || strcmp(x, "G") == 0)
		return 6;
	else
		return -1;
}
int winner(int tablajoc[6][7])
{
	int i, j;
	for (i = 0; i < 6; i++)
		for (j = 0; j < 7; j++)
			if (abs(tablajoc[i][j] + tablajoc[i][j + 1] + tablajoc[i][j + 2] + tablajoc[i][j + 3]) == 4)
				return tablajoc[i][j];
			else if (abs(tablajoc[i][j] + tablajoc[i + 1][j] + tablajoc[i + 2][j] + tablajoc[i + 3][j]) == 4)
				return tablajoc[i][j];
			else if (abs(tablajoc[i][j] + tablajoc[i + 1][j + 1] + tablajoc[i + 2][j + 2] + tablajoc[i + 3][j + 3]) == 4)
				return tablajoc[i][j];
			else if (abs(tablajoc[i][j] + tablajoc[i + 1][j - 1] + tablajoc[i + 2][j - 2] + tablajoc[i + 3][j - 3]) == 4)
				return tablajoc[i][j];

	return 0;
}
void conversieoutput(int x)
{
	if (x == -1)
		printf("|R| ");
	else if (x == 1)
		printf("|G| ");
	else
		printf("|0| ");
}
void afisare(int tablajoc[6][7])
{
	printf("|A| |B| |C| |D| |E| |F| |G|\n");
	printf("___________________________\n");
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 7; j++)
			conversieoutput(tablajoc[i][j]);
		printf("\n");
	}
	printf("___________________________\n");
	printf("|A| |B| |C| |D| |E| |F| |G|\n\n");
}
int egalitate(int tablajoc[6][7])
{
	for (int i = 0; i < 7; i++)
		if (tablajoc[0][i] == 0)
			return 1;
	return 0;
}
extern int errno;

int main()
{
	struct sockaddr_in server;
	struct sockaddr_in from;
	char nick1[10], nick2[10];
	int sd;
	int runda = 0;
	if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		perror("Eroare la crearea socketului.\n");
		return errno;
	}

	bzero(&server, sizeof(server));
	bzero(&from, sizeof(from));
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(PORT);

	if (bind(sd, (struct sockaddr *)&server, sizeof(struct sockaddr)) == -1)
	{
		perror("Eroare la executarea bind-ului.\n");
		return errno;
	}

	if (listen(sd, 1) == -1)
	{
		perror("Eroare la ascultare.\n");
		return errno;
	}

	while (1)
	{
		int client, client1;
		int length = sizeof(from);
		int matrice[6][7] = {0};
		char coloana[10];
		int coloananumerica = 0;
		int plin = 0;
		int gresit = 0;
		char coloanabuna[1];
		int trimitereelement;
		int salveazaculoare;
		int castigator = 3;
		char continua[4], continua1[4];
		int continuare = 4;
		fflush(stdout);

		client = accept(sd, (struct sockaddr *)&from, &length);
		client1 = accept(sd, (struct sockaddr *)&from, &length);

		if (client < 0)
		{
			perror("Eroare la acceptarea clientilor.\n");
			continue;
		}

		int pid;
		if ((pid = fork()) == -1)
		{
			close(client);
			close(client1);
			continue;
		}
		else if (pid > 0)
		{

			close(client);
			close(client1);
			continue;
		}
		else if (pid == 0)
		{

			close(sd);
			bzero(nick1, 10);
			bzero(nick2, 10);
			read(client, nick1, 10);
			read(client1, nick2, 10);
			write(client, nick2, 10);
			write(client1, nick1, 10);
			runda = randomizer();
			salveazaculoare = 1;
			fflush(stdout);
			write(client1, &runda, sizeof(int));
			runda = (runda == -1 ? 1 : -1);
			write(client, &runda, sizeof(int));
		rejoaca:
			reinitializare(matrice);
			continuare = 4;
			castigator = 5;
			bzero(coloana, 10);
			fflush(stdout);
			gresit = 10;
			plin = 10;
			while (1)
			{

				coloananumerica = 0;
				for (int i = 0; i < 6; i++)
					for (int j = 0; j < 7; j++)
					{
						write(client1, &matrice[i][j], sizeof(int));
						write(client, &matrice[i][j], sizeof(int));
					}

				write(client, &runda, sizeof(int));
				runda = (runda == -1 ? 1 : -1);
				write(client1, &runda, sizeof(int));
			greseala:
				if (runda == 1)
				{
					bzero(coloana, 10);
					read(client1, coloana, 10);
					fflush(stdout);
				}
				else
				{
					bzero(coloana, 10);
					read(client, coloana, 10);
					fflush(stdout);
				}
				gresit = 0;

				if (coloana[2] != '\0' || ((coloana[0] < 'a' || coloana[0] > 'g') && (coloana[0] < 'A' || coloana[0] > 'G')))
				{

					gresit = 3;
				}
				write(client1, &gresit, sizeof(int));
				write(client, &gresit, sizeof(int));
				if (gresit == 3)
					goto greseala;

				plin = 0;
				strcpy(coloanabuna, coloana);
				coloanabuna[1] = '\0';
				coloananumerica = conversiecoloana(coloanabuna);
				if (matrice[0][coloananumerica] != 0)
				{

					plin = 3;
				}
				write(client1, &plin, sizeof(int));
				write(client, &plin, sizeof(int));
				if (plin == 3)
					goto greseala;
				adaugare(matrice, salveazaculoare, coloananumerica);
				afisare(matrice);
				if (winner(matrice) != 0||egalitate(matrice)==0)
					castigator = 4;

				write(client1, &castigator, sizeof(int));
				write(client, &castigator, sizeof(int));
				if (castigator == 4)
				{
					for (int i = 0; i < 6; i++)
						for (int j = 0; j < 7; j++)
						{
							write(client1, &matrice[i][j], sizeof(int));
							write(client, &matrice[i][j], sizeof(int));
						}
					read(client, continua, 4);
					read(client1, continua1, 4);
					if (strstr(continua, "play") && strstr(continua1, "play"))
						continuare = 5;
					write(client1, &continuare, sizeof(int));
					write(client, &continuare, sizeof(int));
					if (continuare == 5)
					{	
						bzero(coloana, 10);
						fflush(stdout);
						if(salveazaculoare==-1)
						{runda=runda==1?-1:1;
						salveazaculoare=salveazaculoare==1?-1:1;}
						goto rejoaca;
						
					}
					else
					{
						close(client);
						close(client1);
						exit(0);
					}
				}

				salveazaculoare = (salveazaculoare == 1 ? -1 : 1);
			}

			close(client);
			close(client1);
			exit(0);
		}

	} /* while */
} /* main */
