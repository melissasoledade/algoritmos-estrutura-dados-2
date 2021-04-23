#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge{
	int u;
	int v;
	int peso;
};typedef struct Edge Edge;

struct Grafo{
	int V;
	int E;
	Edge * edge;
};typedef struct Grafo Grafo;

struct subset{
	int pai;
	int rank;
};typedef struct subset subset;


// Cria grafo com V vértices e E arestas
Grafo* criaGrafo(int V, int E){
	Grafo* grafo = (Grafo*)malloc(sizeof(Grafo));
	grafo->V = V;
	grafo->E = E;
	grafo->edge = (Edge*)malloc(E * sizeof(Edge));

	return grafo;
}

void Make_Set(subset subconjuntos[], int i) {
    subconjuntos[i].pai = i;
    subconjuntos[i].rank = 0;
}

subset *Make_Subset(int tamanho) {
    subset *subconjuntos = (subset*) malloc(tamanho * sizeof(subset));
    for (int i=0; i<tamanho; i++) {
        Make_Set(subconjuntos, i);
    }
    return subconjuntos;
}

// função de Find_Set set que procura o representante (pai) do elemento i com compressao de caminho.
int Find_Set(subset subconjuntos[], int i){

	if (i != subconjuntos[i].pai){
		subconjuntos[i].pai = Find_Set(subconjuntos, subconjuntos[i].pai);
	}	

	return subconjuntos[i].pai;
}

// função de union que junta os conjuntos de x e y com uniao ponderada.
void Union(subset subconjuntos[], int x, int y){
	x = Find_Set(subconjuntos, x);
	y = Find_Set(subconjuntos, y);	
	
	if(subconjuntos[x].rank > subconjuntos[y].rank){
		subconjuntos[y].pai = x;
	}
	else{
		subconjuntos[x].pai = y;		
		if(subconjuntos[x].rank == subconjuntos[y].rank){
			subconjuntos[y].rank++;
		}		
	}	
}

// compara Edges pelo peso
int compara(const void* x, const void* y){	
	Edge* i = (Edge*)x;
	Edge* j = (Edge*)y;	
	return i->peso > j->peso;	
}

void Kruskal(Grafo* grafo){
	int V = grafo->V;
	Edge resultado[V]; // Tnis will store the resultadoant MST
	int e = 0; // An index variable, used for resultado[]
	int i = 0; // An index variable, used for sorted edges

	
	qsort(grafo->edge, grafo->E, sizeof(grafo->edge[0]), compara);
	subset* subsets = Make_Subset(V);

	for (int v = 0; v < V; ++v)
	{
		subsets[v].pai = v;
		subsets[v].rank = 0;
	}

	
	while (e < V - 1 && i < grafo->E)
	{
		
		Edge prox = grafo->edge[i++];

		int x = Find_Set(subsets, prox.u);
		int y = Find_Set(subsets, prox.v);

		
		if (x != y) {
			resultado[e++] = prox;
			Union(subsets, x, y);
		}
		
	}

	

	int custoMin = 0;
	for (i = 0; i < e; ++i){
		printf("%d - %d - %d\n", resultado[i].u, resultado[i].v, resultado[i].peso);		
		custoMin = custoMin + resultado[i].peso;
	}
	
	printf("Custo mínimo: %d\n", custoMin);
}


int main(){

	int V = 4; 
	int E = 5; 
	Grafo* grafo = criaGrafo(V, E);

	// add edge 0-1
	grafo->edge[0].u = 0;
	grafo->edge[0].v = 1;
	grafo->edge[0].peso = 10;

	// add edge 0-2
	grafo->edge[1].u = 0;
	grafo->edge[1].v = 2;
	grafo->edge[1].peso = 6;

	// add edge 0-3
	grafo->edge[2].u = 0;
	grafo->edge[2].v = 3;
	grafo->edge[2].peso = 5;

	// add edge 1-3
	grafo->edge[3].u = 1;
	grafo->edge[3].v = 3;
	grafo->edge[3].peso = 15;

	// add edge 2-3
	grafo->edge[4].u = 2;
	grafo->edge[4].v = 3;
	grafo->edge[4].peso = 4;


	// Function call
	Kruskal(grafo);

	return 0;
}

// This code is contributed by rathbhupendra
