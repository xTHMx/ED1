#include <stdio.h>
#include <stdlib.h>

typedef struct No{
    int val;
    short altura;
    struct No *esq, *dir;
}No;

short Max(short a, short b){ //diferenca entre alturas
    return (a>b)? a : b;
}

short Altura(No *no){ //altura do no
    if(no == NULL)
        return -1;
    else
        return no->altura;
}

short FatorBalanceamento(No *no){ //calcula o fator de balanceamento de um no
    if(no)
        return (Altura(no->dir) - Altura(no->esq));
    else
        return 0;
}

No* RotacaoEsquerda(No *no){
    No *dir , *menorDir;

    dir = no->dir;
    menorDir = dir->esq;

    no->dir = menorDir;
    dir->esq = no;

    no->altura = Max(Altura(no->esq), Altura(no->dir)) + 1;
    dir->altura = Max(Altura(dir->esq), Altura(dir->dir)) + 1;

    return dir;
}

No* RotacaoDireita(No *no){
    No *esq , *MaiorEsq;

    esq = no->esq;
    MaiorEsq = esq->dir;

    no->esq = MaiorEsq;
    esq->dir = no;

    no->altura = Max(Altura(no->esq), Altura(no->dir)) + 1;
    esq->altura = Max(Altura(esq->esq), Altura(esq->dir)) + 1;

    return esq;
}

No* RotacaoEsquerdaDupla(No *no){
    RotacaoDireita(no->dir);
    return RotacaoEsquerda(no);
}

No* RotacaoDireitaDupla(No *no){
    RotacaoEsquerda(no->esq);
    return RotacaoDireita(no);
}


No* Balancear(No *raiz){
    short fb = FatorBalanceamento(raiz);

    if(fb > 1 && FatorBalanceamento(raiz->esq) >= 0)
        raiz = RotacaoEsquerda(raiz);
    else if(fb < -1 && FatorBalanceamento(raiz->dir) <= 0)
        raiz = RotacaoDireita(raiz);
    else if(fb < -1 && FatorBalanceamento(raiz->dir) > 0)
        raiz = RotacaoEsquerdaDupla(raiz);
    else if(fb > 1 && FatorBalanceamento(raiz->esq) < 0)
        raiz = RotacaoDireitaDupla(raiz);

    return raiz;
}

No* inserir(No *raiz, int num){   

    if(raiz == NULL){
        No *new = malloc(sizeof(No));
        new->val = num;
        new->esq = NULL;
        new->dir = NULL;
        return new;
        printf("inserido!\n");
        
    }else{
        if(num < raiz->val){
            raiz->esq = inserir(raiz->esq, num);
            
        }else{
            raiz->dir = inserir(raiz->dir, num);
            
        }
    }

    raiz->altura = Max(Altura(raiz->esq), Altura(raiz->dir)) + 1;

    raiz = Balancear(raiz);

    return (raiz);
    
}

No* Remover(No *raiz, int chave){
    if(raiz != NULL){
        if(raiz->val == chave){
            if(raiz->esq == NULL && raiz->dir == NULL){
                free(raiz);
                return NULL;
            }else{
                if(raiz->esq != NULL && raiz->dir != NULL){
                    No *aux = raiz->esq;
                    while (aux->dir != NULL){
                        aux = aux->dir;
                    }
                    
                    raiz->val = aux->val;
                    aux->val = chave;
                    raiz->esq = Remover(raiz->esq, chave);

                    return raiz;

                }else{
                    No *aux;
                    if(raiz->esq != NULL){
                        aux = raiz->esq;
                    }else{
                        aux = raiz->dir;
                    }

                    free(raiz);
                    return aux;

                }
            }
        }else{
            if(chave < raiz->val){
                raiz->esq = Remover(raiz->esq, chave);
            }else{
                raiz->dir = Remover(raiz->dir, chave);
            }
        }

        raiz->altura = Max(Altura(raiz->esq), Altura(raiz->dir)) + 1;

        raiz = Balancear(raiz);

        return raiz;
    }
}


void imprimir(No *raiz){
    if(raiz != NULL){
        imprimir(raiz->esq);
        printf("%d ", raiz->val);
        imprimir(raiz->dir);
        
    }
}


int main(int argc, char const *argv[])
{
    No *raiz = NULL;

    raiz = inserir(raiz,12);
    raiz = inserir(raiz,14);
    raiz = inserir(raiz,13);
    raiz = inserir(raiz,16);
    raiz = inserir(raiz,20);

    printf("Ordem:");
    imprimir(raiz);
    printf("\nraiz: %d", raiz->val);

    raiz = Remover(raiz, 14);
    printf("\nraiz pos remocao: %d \n", raiz->val);
    imprimir(raiz);
    
    printf("\n");

    return 0;
}
