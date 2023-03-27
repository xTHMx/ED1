//TAD: lista seq.
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX 100

//-------------------------Estruturas-----------------------------

typedef struct Dados{
   char nome[30];
   int idade;
} Dados;

typedef struct Elem{
   int chave;
   Dados data;
} Elem;

typedef struct Lista{
   int size; 
   Elem Arr[MAX+1];
} Lista;


//----------------------Funções---------------------
bool isVazia(Lista *L); //se lista estiver vazia
bool isCheia(Lista *L); //se lista estiver cheia
void criaLista(Lista *L); //inicializa a lista

void criaElem(Elem *e, int ch, char nome[], int idade); //passa valores ao elemento temporario
bool inserirElemOrd(Elem e, Lista *L); //insere elemento ja ordenado

void Imprimir(int ch, Lista *L); //imprimi o valor de um elemento procurado pela chave
int Tamanho(Lista *L); //tamanho da lista

int buscaBinaria(int ch, Lista *L); //algoritimo padrao de procura
bool RemoverPorChave(int ch, Lista *L); //remove elemento por chave

