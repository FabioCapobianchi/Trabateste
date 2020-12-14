#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int  fsinal;
int pontos=0;

void recebeSinal(int sin){

printf("\nSinal recebido.\n ");
printf("\nPontuacao final: %d pontos.\n",pontos);
fsinal=1;
}

void initRandom(){
  srand(time(NULL));
}

int randomNum(int a,int b){
  return a + rand()%(b-a+1);
}

int main(int argc, char * argv[]){

  int n,res=0;
  initRandom();
  printf("\nPID=%d\n",getpid());
  fsinal = 0;
  signal(SIGUSR1, recebeSinal);
  printf("\n\nBem vindo ao AdvinhaNum!!!\n\n");
while(1){
    n = randomNum(1,5);
  if (fsinal == 1)
    fsinal = 0;
  printf("\nFoi escolhido um numero entre 1 e 5 \\escolha \"0\"  para terminar!!!\n");
  printf("\nTente acertar o numero \n");
  scanf("%d",&res);
  if(res == 0){
   printf("\nPontuacao final: %d pontos.\n",pontos);
  break;  
    }
  if(res == n){
  printf("\nAcertou!!!\n");
  pontos+=1;
}else{
  printf("\n--Errou--\n");
    }
}
 return 0;
}
