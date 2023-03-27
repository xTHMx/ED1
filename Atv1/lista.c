#include "lista.h"

bool isVazia(Lista *L){
   return (L->size == 0);
}

bool isCheia(Lista *L){
   return (L->size == MAX);
}

void criaLista(Lista *L){
   int i = 0;
   L->size = 0;
   for(i; i < MAX+1; i++)
        L->Arr[i].chave = 0;
        
   //printf("Criada");
}

void criaElem(Elem *e, int ch, char nome[], int idade){
    strcpy(e->data.nome, nome);
    e->data.idade = idade;
    e->chave = ch;
    //printf("Criado %d", e->chave);
    
}

bool inserirElemOrd(Elem e, Lista *L){
   int i = 0, j;

   if (isCheia(L)){
      return false;
      
   }else if(isVazia(L)){
       L->Arr[0] = e;
       L->size++;
       return true;
       
   }else{
      while(L->Arr[i].chave < e.chave && i < L->size) //||
          i++;
    
      if(i < L->size){ //existem valores entre
          for(j = L->size ; j > i ; j--){ //passa pra frente os outros
            L->Arr[j] = L->Arr[j-1];
          }
      }
      
	  L->Arr[i] = e;
      L->size++;
      //printf("inserido %d and %d", i);
      
	  return true; 
   }
}


int Tamanho(Lista *L){
   printf("\nTamanho > %d",L->size);
   return L->size;
}


int buscaBinaria(int ch, Lista *L){
   int esq = 0, dir = L->size-1;
   int meio;
   
   if(L->Arr[esq].chave == ch) return esq;
   if(L->Arr[dir].chave == ch) return dir;
   
   while(!(dir < esq)){
       
      meio = (esq + dir)/2;
      
      if (L->Arr[meio].chave == ch){
          return meio;
          
      }else{
          
         if (L->Arr[meio].chave < ch)
            esq = meio+1;
         else
            dir = meio-1;
      }
   }
   
   return -1;
}

bool RemoverPorChave(int ch, Lista *L){
   int pos, j;
   bool rem = false;
   
   pos = buscaBinaria(ch, L);
   if( pos != -1){        
       L->Arr[pos].chave = 0;
       rem = true;
       L->size--;
       
       if(L->size > 0){ //existem valores
          for(j = pos ; j < L->size ; j++){ //passa pra frente os outros ->size n tem -1 pois removemos uma posiçao antes
            L->Arr[j] = L->Arr[j+1];
          }
          
          L->Arr[j+1].chave = 0; //remove o ultimo elemento fora do tamanho ocupado
      }
   }
   printf("Removido elemento da posiçao %d", pos);
   return rem;
}



void Imprimir(int ch, Lista *L)
{
   int pos;
   Elem e;
   
   if((pos = buscaBinaria(ch, L)) != -1){
       e = L->Arr[pos];
       printf("posicao: %d\n", pos);
       printf("chave: %d\n", e.chave);
       printf("nome: %s\n", e.data.nome);
       printf("idade: %d\n", e.data.idade);
       
    }else{
        printf("Erro: chave nao encontrada!\n");
        
    }
}


