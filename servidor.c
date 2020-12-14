

#include "comuns.h"
#include <signal.h>

#define NPALAVRAS 7


int s_fifo_fd,c_fifo_fd;

void trataSig(int i){
fprintf(stderr,"\nServidor de dicionario a terminar"
        "(interrompido via teclado)\n\n");
    close(s_fifo_fd);
    unlink(SERVER_FIFO);
    exit(EXIT_SUCCESS);
}

int main(int argc, char * argv[]){
initRandom();


int num, nfd ,ver,res,x=0,y=0;
char c_fifo_fname[50];
char *gamedir, *maxplayer;

fd_set read_fds;

client cli1;
resposta_t resp;
pcli players = NULL,auxp;

 //printf("\nNumero aleatorio: %d\n",randomNum(1,15));
 printf("\nBEM VINDO AO CHAMP\n");
 
    while (argc!=5)
{
 printf("\nFaltam Parametros!\n Parametros esperados ./arbitro -d  <duracao> -t <tempo_espera>\n");
 return 0;
} 
   while((num=getopt(argc,argv,"d:t:"))!= -1)
     switch(num){
        case 'd':
           if(strcmp(argv[1],"-d")==0){
               x=atoi(argv[2]);
               printf("Duracao do Campeonato -> %d\n",x);
         }else{
               x=atoi(argv[4]);
               printf("Duracao do Campeonato  -> %d\n",x);
}
   break;
        case 't':
           if(strcmp(argv[1],"-t")==0){
               y=atoi(argv[2]);
               printf("Tempo de espera-> %d\n",y);
} else {
               y=atoi(argv[4]);
               printf("Tempo de espera -> %d\n",y);
}
   break;
   
}

execlp("bash -c", "bash -c", "source . ./ambVar.sh &", "", NULL);
  maxplayer=getenv("MAXPLAYER");
  gamedir=getenv("GAMEDIR");
  printf("max - %s\ngame - %s\n", maxplayer, gamedir);

if(signal(SIGINT,trataSig) == SIG_ERR){
perror("\nNao foi possivel configurar o sinal SIGINT\n");
exit(EXIT_FAILURE);
}
fprintf(stderr, "\nSignal SIGINT configurado");


res = mkfifo(SERVER_FIFO, 0777);
if (res == -1){
perror("\nmkfifo do FIFO servidor deu erro");
exit(EXIT_FAILURE);
}
fprintf(stderr, "\nfIFO servidor criado");


s_fifo_fd = open(SERVER_FIFO, O_RDWR);
if (s_fifo_fd == -1){
perror("\nmkErro ao abrir FIFO servidor(RDWR/blocking)");
exit(EXIT_FAILURE);
}
 fprintf(stderr, "\nFIFO aberto para READ (+WRITE) bloqueante");
 
 while (1){
 
 FD_ZERO(& read_fds);
 FD_SET(0,  & read_fds);
 FD_SET(s_fifo_fd, & read_fds);
 nfd = select(2, & read_fds, NULL, NULL, NULL);/////parei aqui
 
 if(FD_ISSET(0, & read_fds)){
 char buff[25];
 scanf("%s",buff);
 if(strcmp(buff,"sair")==0){
 
  close(s_fifo_fd);
 unlink(SERVER_FIFO);
 
 return 0;
 }
 }
 
 if(FD_ISSET(s_fifo_fd, & read_fds)){
 
 continue;
 
 }
 
 
 res = read(s_fifo_fd,  &cli1, sizeof(cli1));
 if(res < sizeof(cli1)){
   fprintf(stderr,"\nRecebida pergunta incompleta " "[bytes lidos: %d]", res);
   continue;
 }
 
 ver = Verifica_player(players, cli1.pnome);
 printf("\nRecebido %d\n", ver);
 if(ver == 1){
 auxp = criaCliente(players, cli1);
 players = auxp;
 }
 
 printf("\nRecebido %s\n", cli1.comando);
 
   strcpy(resp.comando, "DESCONHECIDO");

   //fprintf(stderr, "\nResposta %s", resp.comando);

   strcpy(c_fifo_fname,cli1.fname);
  
  c_fifo_fd = open(c_fifo_fname, O_WRONLY);
  
   /*if(!strcasecmp(cli.comando, "fim")){
    close(c_fifo_fd);
    unlink(cli.fname);
  }*/
    if(!strcasecmp(cli1.comando, "mygame")){
   strcpy(resp.ngame,"jogo1");
   resp.points=10;
  }
  if(c_fifo_fd == -1){
    perror("\Erro no open - Ninguem quis a resposta");
    }
      
    res = write(c_fifo_fd, & resp, sizeof(resp));
    if(res == sizeof(resp))
      fprintf(stderr,"\nescreveu a resposta");
      else
      perror("\nerro a escrever a resposta");
    
    close(c_fifo_fd);
    fprintf(stderr,"\nFIFO cliente fechado");
    

 }
 close(s_fifo_fd);
 unlink(SERVER_FIFO);
 
 return 0;
 }
  

