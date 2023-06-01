#include <stdio.h>
#include <stdlib.h>
//#include <string.h>

#define tam_fila 100  //tamanho max. fila

typedef struct fila{
  int A[tam_fila];    //Simplificacao
  int inicio, fim;
} fila;


//Cria uma fila vazia
void Define(fila *f) {
   f->fim = 0;
   f->inicio = 0;
   //Obs: ponteiro de início atrasado: aponta para uma posição anterior ao início
}

//retorna se a lista esta vazia
int isEmpty(fila *f){
    if(f->inicio == f->fim)
        return 1;
    return 0; 
}

//Adiciona um elemento no fim da fila f (1 caso verdadeiro)
//Note que uma posição da fila nunca será preenchida
int Insert(fila *f, int elem) {	
   if (f->inicio == ((f->fim + 1) % tam_fila)) //cheia?
      return 0;

   f->fim = (f->fim + 1) % tam_fila;
   f->A[f->fim] = elem;
    return 1;
}

//Remove um elemento do início da fila q (retorna true se sucesso, false c.c.)
int Remove(fila *f, int *elem) {
   if (f->inicio == f->fim) //vazia?
      return 0;
   f->inicio = (f->inicio + 1) % tam_fila;
   *elem = f->A[f->inicio];
   return 1;
}

//cria uma matriz de adjacencia a partir de um arquivo
int** insertGraph(){
    FILE *f = fopen("digrafo.txt","r");
    int n, i, j, cur_num, temp_num, pos=0;

    fscanf(f, "%d", &n); //passa o numero de nos para o tamanho da matriz

    int **mat = malloc(n*sizeof(int*)); //aloca ponteiros dentro de ponteiros
    for(i=0; i < n; i++){
        mat[i] = malloc(n*sizeof(int)); //aloca os ponteiros de dentro
        *mat[i] = 0;  //define 0 como padrao
    }

    cur_num = 0; //no do grafo atual

    //memset(mat, 0, n*n*sizeof(int));

    while(fscanf(f, "%d", &cur_num) > 0){
        fscanf(f, "%d", &pos);   
        fscanf(f, "%d", &mat[cur_num][pos]);
    }

    fclose(f);

    return mat;

}


//matriz A (de adj.): representa as conexões entre as cidades 0,...,N-1, 
//vetor 'dist': dist[i] é a distância da cidade fixada 'c' até cada cidade 'i'
int main() {
	//Inicialização da matriz com as cidades interconectadas

    int **A;
	int *dist;
	int i = 0, j, c = 0, n;
	fila F;

    FILE *f = fopen("digrafo.txt", "r"); //le o tamanho
    fscanf(f, "%d", &n);
    fclose(f);

    dist = malloc(n*sizeof(int));
    A = insertGraph(); //passa a matriz alocada para o ponteiro

	for (j=0; j<n; j++)  
	    dist[j] = n;       //Seta dist[j] = inf, todo j
    
	dist[c] = 0;
    Define(&F);           //Cria fila
    Insert(&F,c);         //Insere na fila

    //Roda até que todos os nós tenham sido checados pelo critério abaixo: 
	//tira da fila uma cidade i, e coloca na fila as cidades vizinhas j com distancias ñ computadas
    while (!isEmpty(&F)) 
	{ 
       Remove(&F,&i);       //Remove da fila (i é o elemento corrente a partir daqui)
       for (j=0; j < n; j++)
          if (A[i][j] != 0 && dist[j] >= n) //Se i tem conexao com j E j ainda nao checado
		  {
             dist[j] = dist[i] + A[i][j];
             Insert(&F,j);
          }
    }
	
	//Imprime vetor de distâncias de 'c' para as demais cidades 'i'
	for (i=0; i<n; i++)
	   printf("dist[%d]: %d\n", i, dist[i]);

}