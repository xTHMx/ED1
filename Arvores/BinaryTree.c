#include <stdio.h>
#include <stdlib.h>

typedef struct No {
    int val;
    struct No *esq, *dir;
}No;

void inserir(No **raiz, int num){
    No *new = malloc(sizeof(No));
    
    if(new){
        
        if(*raiz == NULL){
            *raiz = malloc(sizeof(No));
            (*raiz)->val = num;
            (*raiz)->esq = NULL;
            (*raiz)->dir = NULL;
            
        }else{
            if(num < (*raiz)->val){
                inserir(&(*raiz)->esq, num);
                
            }else if(num > (*raiz)->val){
                inserir(&(*raiz)->dir, num);
                
            }else{          //ja existe valor
                free(new);
                return;
            }
        }
    }
}

void imprimir(No **raiz){
    if(*raiz != NULL){
        imprimir(&(*raiz)->esq);
        printf("%d ", (*raiz)->val);
        imprimir(&(*raiz)->dir);
        
    }
}

int altura(No **raiz){
    int d,e;
    
    if(*raiz == NULL){
        return 0;
    }else{
        d = altura(&(*raiz)->dir);
        e = altura(&(*raiz)->esq);
        if(e > d)
            return e + 1;
        else
            return d + 1;
    }
}

No* buscar(No *raiz, int val){
    if(raiz == NULL){
        return NULL;
        
    }else{
        if(raiz->val == val){
            return raiz;
        }else{
            if(val < raiz->val){
                return buscar(raiz->esq, val);
            }else{
                return buscar(raiz->dir, val);
            }
        }
    }
}

No* remover(No **raiz, int val){
    if(*raiz != NULL){
        if((*raiz)->val == val){
            if((*raiz)->esq == NULL && (*raiz)->dir == NULL){ //sem descendentes
                printf("removido %d \n", (*raiz)->val);
                free(*raiz);
                
                return NULL;
            }else{
                if((*raiz)->esq == NULL || (*raiz)->dir == NULL){ //um descendente
                    No *aux;
                    
                    if((*raiz)->esq != NULL){
                        aux = (*raiz)->esq;
                    }else{
                        aux = (*raiz)->dir;
                    }
                    printf("removido-%d \n", (*raiz)->val);
                    free(*raiz);
                    return aux;
                    
                }else{                   //dois descendente
                    No *aux = (*raiz)->esq;
                    while(aux->dir != NULL)
                        aux = aux->dir;
                        
                    (*raiz)->val = aux->val; //troco o valor dos nós
                    aux->val = val;
                    (*raiz)->esq = remover(&(*raiz)->esq,val); //agora o nó sera uma folha -> apago normal
                    
                    return *raiz;
                }
            }
        }else{
            if(val < (*raiz)->val)
                (*raiz)->esq = remover(&(*raiz)->esq, val); 
            else
                (*raiz)->dir = remover(&(*raiz)->dir, val); 

            return (*raiz);

        }
    }
}

int calcularFolhas(No **raiz){
    if((*raiz) != NULL){
        if((*raiz)->esq == NULL && (*raiz)->dir == NULL )
            return 1;
        else    
            return calcularFolhas(&(*raiz)->esq) + calcularFolhas(&(*raiz)->dir);
    }

    return 0;
}

int main(){
    No *raiz = NULL;

    inserir(&raiz, 12);
    inserir(&raiz,4);
    inserir(&raiz, 6);
    inserir(&raiz, 14);
    inserir(&raiz, 17);
    inserir(&raiz, 18);
    inserir(&raiz, 13);
    
    
    imprimir(&raiz);
    printf("\n");
    printf("%d\n",altura(&raiz));
    No *temp  = buscar(raiz, 14);
    printf("%d\n",temp->val);
    remover(&raiz,6);
    printf("%d folhas\n", calcularFolhas(&raiz));
    imprimir(&raiz);

    return 0;
}