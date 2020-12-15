#include "comuns.h"
#include <signal.h>

#define NPALAVRAS 7

int s_fifo_fd,c_fifo_fd;

void trataSig(int i){
fprintf(stderr,"\nCHAMP a terminar!!!!\n"
        "(interrompido via teclado == ^C)\n\n");
    close(s_fifo_fd);
    unlink(CHAMP_FIFO);
    exit(EXIT_SUCCESS);
}

int main(int argc, char * argv[]){
initRandom();

int num, ndd,ver,res,x=0,y=0;
char c_fifo_fname[50];
char *gamedir, *maxplayer;

fd_set read_fds;
struct timeval t;

client cli1;
resposta_t resp;
char *games[4][1]={{"g_1.exe"},{"g_2.exe"},{"g_3.exe"},{"g_4.exe"}};
pcli players = NULL,auxp;


 printf("\nBEM VINDO AO CHAMP\n");
 
    while (argc!=5){
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
        }else{
            y=atoi(argv[4]);
            printf("Tempo de espera -> %d\n",y);
        }
    break;
   }

maxplayer=getenv("MAXPLAYER");
gamedir=getenv("GAMEDIR");
printf("MAXPLAYER - %s\nGAMEDIR - %s\n", maxplayer, gamedir);

    if(signal(SIGINT,trataSig) == SIG_ERR){
        perror("\nNao foi possivel configurar o sinal SIGINT\n");
        exit(EXIT_FAILURE);
    }
    
res = mkfifo(CHAMP_FIFO, 0777);
    if (res == -1){
        perror("\nmkfifo do FIFO servidor deu erro");
        exit(EXIT_FAILURE);
    }


s_fifo_fd = open(CHAMP_FIFO, O_RDWR);
    if (s_fifo_fd == -1){
        perror("\nmkErro ao abrir FIFO servidor(RDWR/blocking)");
        exit(EXIT_FAILURE);
    }
 
    while (1){
    
        t.tv_sec = 2;
        t.tv_usec = 0;
    
        FD_ZERO(& read_fds);
        FD_SET(0,  & read_fds);
        FD_SET(s_fifo_fd, & read_fds);
        ndd = select(s_fifo_fd + 1, & read_fds, NULL, NULL, & t);
       
        if(ndd == 0){
        
        fflush(stdout);
        continue;
        }

        if(FD_ISSET(0, & read_fds)){

            char buff[25];
            scanf("%s",buff);
            if(strcmp(buff,"exit")==0){
                close(s_fifo_fd);
                unlink(CHAMP_FIFO);
            return 0;
            }else
             if(strcasecmp(buff,"players")==0){
                mostra_player(players);
                
            }else
            if(strcasecmp(buff,"games")==0){
                mostra_jogos(4,games);
           
            }else
            if(strcasecmp(buff,"k")==0){
               
               printf("falta implementar");
               
            }
            
        }
 
    if(FD_ISSET(s_fifo_fd, & read_fds)){
        
        res = read(s_fifo_fd,  &cli1, sizeof(cli1));
        
        }
 
 
    if(res < sizeof(cli1)){
        fprintf(stderr,"\nRecebida pergunta incompleta " "[bytes lidos: %d]", res);
        
    }
 
 ver = Verifica_player(players, cli1.pnome);

    if(ver == 1){
        auxp = criaCliente(players, cli1);
        players = auxp;
    }
 
  printf("\nRecebido %s\n", cli1.comando);
  if(!strcasecmp(cli1.comando, "quit")){
       close(c_fifo_fd);
        fprintf(stderr,"\nFIFO cliente fechado\n"); 
    }
  strcpy(resp.comando, "DESCONHECIDO");
  strcpy(c_fifo_fname,cli1.fname);  
  c_fifo_fd = open(c_fifo_fname, O_WRONLY);
   
  
    if(!strcasecmp(cli1.comando, "mygame")){
        strcpy(resp.ngame,"jogo1");
        resp.points=10;
    }
    if(c_fifo_fd == -1){
        perror("\Erro no open - Ninguem quis a resposta");
    }
      
res = write(c_fifo_fd, & resp, sizeof(resp));
    if(res != sizeof(resp)){

        perror("\nerro a escrever a resposta");
        close(c_fifo_fd);
        fprintf(stderr,"\nFIFO cliente fechado"); 
    }
    }
    
 close(s_fifo_fd);
 unlink(CHAMP_FIFO);
 
 return 0;
 }
