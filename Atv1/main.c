
//dupla -> Tulio e Deus ( nao achei ninguem pra fazer grupo :( )

#include "lista.h"

int main(){
    Lista l;
    Elem temp;
    
    int i, num, idade, chave;
    char str[30];
    
    criaLista(&l);
    
    printf("Digite o numero de valores a ser inserido: ");
    scanf("%d", &num);
    
    for(i = 0; i < num; i++){
        printf("Digite a chave, nome e idade do individuo (separados por espaco): \n");
        scanf(" %d %s %d", &chave, str, &idade);
        criaElem(&temp, chave, str, idade);
        inserirElemOrd(temp, &l);
    }
    
    
    Tamanho(&l);
    
    printf("\nDigite a chave a ser procurada: ");
    scanf(" %d", &chave);
    Imprimir(chave, &l);
    
    printf("\nDigite a chave do elemento para remove-lo: ");
    scanf(" %d", &chave);
    RemoverPorChave(chave, &l);
    
    printf("\nDigite a chave a ser procurada: "); //dica : procure o elemento removido para testar
    scanf(" %d", &chave);
    Imprimir(chave, &l);
  
    return 0;
}
