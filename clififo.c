
#include "comuns.h"
#include <signal.h>

 
int main(){

int s_fifo_fd;
int c_fifo_fd;
client cli1;
resposta_t resp;
char c_fifo_fname[25];
char pnome[25];
int read_res;

//Cria o FIFO do cliente
printf("\nDigite o nome de jogador: \n");
scanf("%s",pnome);

cli1.pid_cliente = getpid();
strcpy(cli1.pnome,pnome);
sprintf(cli1.fname, CLIENT_FIFO, cli1.pnome);
strcpy(c_fifo_fname,cli1.fname);

if(mkfifo(c_fifo_fname, 0777) == -1){
perror("\nmkfifo do FIFO cliente deu erro");
exit(EXIT_FAILURE);
}

fprintf(stderr,"\nJogador %s criado\n",pnome);

s_fifo_fd = open(SERVER_FIFO, O_WRONLY);
if(s_fifo_fd == -1){
 fprintf(stderr, "\nO servidor não esta a correr\n");
 unlink(c_fifo_fname);
 exit(EXIT_FAILURE);
}
 
 c_fifo_fd = open(c_fifo_fname, O_RDWR);
 if(c_fifo_fd == -1){
 perror("\nErro ao abrir o FIFO do cliente");
 close(c_fifo_fd);
 unlink(c_fifo_fname);
 exit(EXIT_FAILURE);
 }
 
 
 fprintf(stderr, "\nFIFO do cliente aberto para READ(+Write) Block");
 
 memset(cli1.comando, '\0', TAM_MAX);
 
 

 
 while(1){

printf("\nDigite o comando > ");
scanf("%s",cli1.comando);
if(!strcasecmp(cli1.comando,"fim")){
write(s_fifo_fd, &cli1, sizeof(cli1));
break;
}
// B) Envia a pergunta
write(s_fifo_fd, &cli1, sizeof(cli1));


// c) Obtem a resposta

read_res = read(c_fifo_fd, &resp, sizeof(resp));
if(read_res == sizeof(resp)){
  
  printf("\nJogo -> %s" , resp.ngame);
  printf("\nPontos -> %d" , resp.points);
  }
else
  printf("\nSem resposta ou resposta incompreensivel" "[bytes lidos: %d]", read_res);  
}

close(c_fifo_fd);
close(s_fifo_fd);
unlink(c_fifo_fname);
return 0;

}
