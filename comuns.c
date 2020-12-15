
#include "comuns.h"

void initRandom()
{
    srand(time(NULL));
}

int randomNum(int a, int b)
{
    return a + rand()%(b-a+1);
}

pcli criaCliente(pcli c1, client copia)
{
  pcli novo;

  novo=malloc(sizeof(client));
 if(novo==NULL)
 {
  return NULL;
 }else{
   novo->pid_cliente = copia.pid_cliente;
   strcpy(novo->pnome, copia.pnome);
   strcpy(novo->fname, copia.fname);
   novo->next= NULL;
   
    if(c1==NULL)
        c1 = novo;
    else
    {  
      novo->next = c1->next;
      c1->next = novo;
     }                           
   }
   if(c1!=NULL)
   fprintf(stderr,"\nCliente %s gravado\n", novo->pnome);
   return c1;
}

int Verifica_player(pcli c1, char cname[])
{
    pcli aux;
    aux=c1;
     if(aux == NULL){
     return 1;
     }
    while(aux != NULL)
    {  
        if(strcmp(aux->pnome,cname)==0)
        { 
            return 0;
        }
        aux = aux->next;
    }
    
    return 1;
}


void mostra_player(pcli c1)
{
    pcli aux;
    aux=c1;
     if(aux == NULL){
     fprintf(stderr,"\nAinda nao existem jogadores\n");
     return;
     }
    while(aux != NULL)
    {  
       fprintf(stderr,"Player: %s\n", aux->pnome);
        aux = aux->next;
    }
    
    return ;
}

void mostra_jogos(int tam,char *fga[4][1]){
int i;

for(i=0;i<tam;i++){
  printf("Jogo: %s\n", fga[i][0]);
}
return;
}

int max(int a, int b){

return (a > b) ? a : b;

}
