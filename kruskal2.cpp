#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aresta{
	int u; //fonte
	int v; //destino
	float peso; //peso -> custo gasolina + pedágio	
	const char *nomeEmp;
    const char *enderecoEmp;
	unsigned long int CNPJ;
	const char *produtos;
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

// Adiciona dados ao grafo
void adicionaArestaGrafo(Grafo *Grafo, int ind, int u, int v, float peso, const char *nomeEmp, const char *enderecoEmp, unsigned long int CNPJ, const char *produtos){
	Grafo->aresta[ind].u = u;
	Grafo->aresta[ind].v = v;
	Grafo->aresta[ind].peso = peso;
	Grafo->aresta[ind].nomeEmp = nomeEmp;
	Grafo->aresta[ind].enderecoEmp = enderecoEmp;
	Grafo->aresta[ind].CNPJ = CNPJ;
	Grafo->aresta[ind].produtos = produtos;	
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

// Algoritmo de Kruskal. Encontra a árvore geradora mínima em um grafo, resultando em todos os pontos (vértices) que devem ser percorridos e o peso total do caminho
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
		printf("\n-----------------------------------------------------------------------------------------------------------\n");
		printf("Fonte: %d - Destino: %d - Peso: %.2f\n", resultado[i].u, resultado[i].v, resultado[i].peso);
		printf("Nome empresa: %s - CNPJ: %lu - Endereço: %s\n", resultado[i].nomeEmp, resultado[i].CNPJ, resultado[i].enderecoEmp);	
		printf("Produtos: %s\n", resultado[i].produtos);
		printf("\n-----------------------------------------------------------------------------------------------------------\n");
		custoMin = custoMin + resultado[i].peso;
	}
	
	printf("Custo mínimo: %.2f\n", custoMin);
	printf("\n-----------------------------------------------------------------------------------------------------------\n");
}


int main(){
	int V = 4; 
	int E = 5; 
	Grafo* grafo = criaGrafo(V, E);
	

	// Teste input no grafo e custo mínimo
	adicionaArestaGrafo(grafo, 0, 0, 1, 11.0, "AAA", "NBB", 9999999, "teste;teste;teste");
	adicionaArestaGrafo(grafo, 1, 0, 2, 6.65, "CCC", "DDD", 111211111, "teste;testea;testeb");
	adicionaArestaGrafo(grafo, 2, 0, 3, 5.92, "EEE", "FFF", 11141111, "teste;testea;testeb");
	adicionaArestaGrafo(grafo, 3, 1, 3, 15.89, "GGG", "HHH", 112311111, "teste;testea;testeb");
	adicionaArestaGrafo(grafo, 4, 2, 3, 3.72, "III", "JJJ", 11198111, "teste;testea;testeb");

	Kruskal(grafo);

	return 0;
}

