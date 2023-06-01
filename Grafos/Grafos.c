#include <stdio.h>
#include <stdlib.h> 

typedef struct no {
	int id;
	int val;
	struct no *prox;
}No;

typedef struct grafo {
	int nNo;     //número de nós
	No *vertices; //array de vértices
}Grafo;

//Cria um nó do grafo
No *CreateNo (int id, int val) {
	No *new = malloc(sizeof(No));
	new->id = id;
	new->prox = NULL;
	new->val = val;
	return new;
}

//Adiciona um nó no grafo
void addNo (No *n, int id, int val) {
	No *new = CreateNo(id, val);

	if(n == NULL){
		return;
	}

	//Encontra a última posição na lista de adj. ref. nó n
	while(n->prox != NULL){ 
		n = n->prox;
	}
	n->prox = new;
}

//Imprime a lista de todos os nós adjacentes ao nó corrente n
void printNo(No *n){
	while(n != NULL){
		printf("-> [%d, val: %d]", n->id, n->val);
		n = n->prox;
	}
}

//Define um grafo vazio
Grafo *createGraph(){
	Grafo *G = malloc(sizeof(Grafo));
	G->vertices = NULL;
	G->nNo = 0;
	return G;
}

//Efetuar a leitura do grafo via arquivo
void readGraph(Grafo *G, const char *filename){ 
    FILE *f = fopen(filename, "r");
	int bsize = 20;
	int i, ori, des, val;
	char buffer[bsize];

	fgets(buffer, bsize, f);
	sscanf(buffer, "%d", &G->nNo);
	G->vertices = malloc(G->nNo * sizeof(No));

	//loop pe lista principal
	for(i=0; i < G->nNo; i++){
		(G->vertices +i)->id = i;
		(G->vertices +i)->val = -1;
		(G->vertices +i)->prox = NULL;
	}

	//leitura e passagem de valores
	while(!feof(f)){
		fgets(buffer, bsize, f);
		sscanf(buffer, "%d %d %d", &ori, &des, &val);
		//printf("%d %d %d\n", ori, des, val);
		addNo((G->vertices + ori), des, val);
	}

	fclose(f);
    
}

//Imprime o grafo a partir das listas de adjacencia
void printGraph(Grafo *G) {
	int i;
	printf("\nGrafo - Lista de Adjacencia\n\n");
	for(i = 0; i < G->nNo; i++){
		printf("(%d)", (G->vertices + i)->id);
		printNo((G->vertices + i));
		printf("\n");	
	}
}

int main(int argc, char const *argv[]){
	Grafo *g = createGraph();
	
	readGraph(g, "digrafo.txt");
	printGraph(g);
	
	return 0;
}
