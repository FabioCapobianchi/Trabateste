
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <signal.h>


#define  CHAMP_FIFO "ser_fifo"

#define  CLIENT_FIFO "f%s"

#define TAM_MAX 50



typedef struct cliente client, *pcli;

struct cliente{//CHAMP -> servidor
 pid_t pid_cliente;
 char pnome[TAM_MAX];
 char fname[TAM_MAX];
 char comando[TAM_MAX];
 pcli next;
};


typedef struct{//CHAMP -> cliente
 char comando[TAM_MAX];
 char ngame[TAM_MAX];
 int points;
}resposta_t;

pcli criaCliente(pcli c1, client copia);

int Verifica_player(pcli c1, char cname[]);

void mostra_player(pcli c1);

void mostra_jogos(int tam,char *fga[4][1]);

int max(int a, int b);

// Inicializa o gerador de numeros aleatorios.
// Esta funcao deve ser chamada apenas uma vez no inicio da execucao do programa
void initRandom();

//Devolve um valor inteiro aleatorio distribuido uniformemente entre [a, b]
int randomNum(int a, int b);
