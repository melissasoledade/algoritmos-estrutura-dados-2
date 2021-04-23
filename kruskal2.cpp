#include <bits/stdc++.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge{
	int src;
	int dest;
	int weight;
};typedef struct Edge Edge;

struct Graph{
	int V;
	int E;
	Edge * edge;
};typedef struct Graph Graph;

struct subset{
	int pai;
	int rank;
};typedef struct subset subset;


// Creates a graph with V vertices and E edges
Graph* createGraph(int V, int E)
{
	Graph* graph = (Graph*)malloc(sizeof(Graph));
	graph->V = V;
	graph->E = E;
	graph->edge = (Edge*)malloc(E * sizeof(Edge));

	return graph;
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


// compara Edges pelo weight
int compara(const void* x, const void* y){	
	Edge* i = (Edge*)x;
	Edge* j = (Edge*)y;	
	return i->weight > j->weight;	
}

void KruskalMST(Graph* graph)
{
	int V = graph->V;
	Edge result[V]; // Tnis will store the resultant MST
	int e = 0; // An index variable, used for result[]
	int i = 0; // An index variable, used for sorted edges

	
	qsort(graph->edge, graph->E, sizeof(graph->edge[0]), compara);
	subset* subsets = Make_Subset(V);

	for (int v = 0; v < V; ++v)
	{
		subsets[v].pai = v;
		subsets[v].rank = 0;
	}

	
	while (e < V - 1 && i < graph->E)
	{
		
		Edge next_edge = graph->edge[i++];

		int x = Find_Set(subsets, next_edge.src);
		int y = Find_Set(subsets, next_edge.dest);

		
		if (x != y) {
			result[e++] = next_edge;
			Union(subsets, x, y);
		}
		// Else discard the next_edge
	}

	

	int minimumCost = 0;
	for (i = 0; i < e; ++i){
		printf("%d - %d - %d\n", result[i].src, result[i].dest, result[i].weight);		
		minimumCost = minimumCost + result[i].weight;
	}
	
	printf("Custo mínimo: %d\n", minimumCost);
}

// Driver code
int main()
{

	int V = 4; // Number of vertices in graph
	int E = 5; // Number of edges in graph
	Graph* graph = createGraph(V, E);

	// add edge 0-1
	graph->edge[0].src = 0;
	graph->edge[0].dest = 1;
	graph->edge[0].weight = 10;

	// add edge 0-2
	graph->edge[1].src = 0;
	graph->edge[1].dest = 2;
	graph->edge[1].weight = 6;

	// add edge 0-3
	graph->edge[2].src = 0;
	graph->edge[2].dest = 3;
	graph->edge[2].weight = 5;

	// add edge 1-3
	graph->edge[3].src = 1;
	graph->edge[3].dest = 3;
	graph->edge[3].weight = 15;

	// add edge 2-3
	graph->edge[4].src = 2;
	graph->edge[4].dest = 3;
	graph->edge[4].weight = 4;


	// Function call
	KruskalMST(graph);

	return 0;
}

// This code is contributed by rathbhupendra
