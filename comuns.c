
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
   fprintf(stderr,"\nCliente gravado\n");
   return c1;
}

int Verifica_player(pcli c1, char cname[])
{
fprintf(stderr,"\nCliente verificado %s\n", cname);
    pcli aux;
    aux=c1;
     if(aux == NULL){
     return 1;
     }
    while(aux != NULL)
    {  fprintf(stderr,"\naux->nome %s nome %s\n",aux->pnome, cname);
        if(strcmp(aux->pnome,cname)==0)
        { fprintf(stderr,"\naux: %s  cname %s\n",aux->pnome, cname);
            return 0;
        }
        aux = aux->next;
    }
    printf(" *** Local nao encontrado  ***\n\n");
    return 1;
}

int max(int a, int b){

return (a > b) ? a : b;

}
