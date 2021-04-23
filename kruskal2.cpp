#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aresta{
	int u; //fonte
	int v; //destino
	float peso; //peso -> custo gasolina + pedágio
};typedef struct Aresta Aresta;

struct Grafo{
	int V;
	int E;
	Aresta * aresta;
};typedef struct Grafo Grafo;

struct subset{
	int pai;
	int rank;
};typedef struct subset subset;


// Cria grafo com V vértices e E arestas
Grafo* criaGrafo(int V, int E){	
	Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));	
	grafo->aresta = (Aresta*)malloc(E * sizeof(Aresta));
	grafo->V = V;
	grafo->E = E;

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

// compara arestas pelo peso
int compara(const void* x, const void* y){	
	Aresta* i = (Aresta*)x;
	Aresta* j = (Aresta*)y;	
	return i->peso > j->peso;	
}

void Kruskal(Grafo* grafo){
	int V = grafo->V, e = 0, i = 0;
	float custoMin = 0.00;
	Aresta resultado[V]; 	
	qsort(grafo->aresta, grafo->E, sizeof(grafo->aresta[0]), compara);
	subset* subsets = Make_Subset(V);
		
	while (e < V - 1 && i < grafo->E){
		
		Aresta prox = grafo->aresta[i++];
		int x = Find_Set(subsets, prox.u);
		int y = Find_Set(subsets, prox.v);
		
		if (x != y) {
			resultado[e++] = prox;
			Union(subsets, x, y);
		}
		
	}	
	
	for (i = 0; i < e; ++i){
		printf("Fonte: %d - Destino: %d - Peso: %.2f\n", resultado[i].u, resultado[i].v, resultado[i].peso);		
		custoMin = custoMin + resultado[i].peso;
	}
	
	printf("Custo mínimo: %.2f\n", custoMin);
}


int main(){

	int V = 4; 
	int E = 5; 
	Grafo* grafo = criaGrafo(V, E);

	// add aresta 0-1
	grafo->aresta[0].u = 0;
	grafo->aresta[0].v = 1;
	grafo->aresta[0].peso = 10;

	// add aresta 0-2
	grafo->aresta[1].u = 0;
	grafo->aresta[1].v = 2;
	grafo->aresta[1].peso = 6;

	// add aresta 0-3
	grafo->aresta[2].u = 0;
	grafo->aresta[2].v = 3;
	grafo->aresta[2].peso = 5;

	// add aresta 1-3
	grafo->aresta[3].u = 1;
	grafo->aresta[3].v = 3;
	grafo->aresta[3].peso = 15;

	// add aresta 2-3
	grafo->aresta[4].u = 2;
	grafo->aresta[4].v = 3;
	grafo->aresta[4].peso = 4;



	Kruskal(grafo);

	return 0;
}

