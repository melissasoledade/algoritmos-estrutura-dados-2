#include "uf.h"

grafo* criarGrafo(int V, int E) {
    grafo* g = (grafo*) malloc( sizeof(grafo) );
    g->V = V;
    g->E = E;
    g->VetorDeArestas = (aresta*) malloc(g->E * sizeof(aresta) );
    return g;
}

void destruirGrafo(grafo *g) {
    free(g->VetorDeArestas);
    free(g);
}

subset *Make_Subset(int tamanho) {
    subset *subconjuntos = (subset*) malloc(tamanho * sizeof(subset));
    for (int i=0; i<tamanho; i++) {
        Make_Set(subconjuntos, i);
    }
    return subconjuntos;
}

void Destroy_Subset(subset *s) {
    free(s);
}

void Make_Set(subset subconjuntos[], int i) {
    subconjuntos[i].pai = i;
    subconjuntos[i].rank = 0;
}

// Funcao que procura o representante (pai) do elemento i com compressao de caminho.
int Find_Set(subset subconjuntos[], int i) {
    if(i != subconjuntos[i].pai){
		subconjuntos[i].pai = Find_Set(subconjuntos, subconjuntos[i].pai);
	}	
    return subconjuntos[i].pai;
}

// Funcao que junta os conjuntos de x e y com uniao ponderada.
void Union(subset subconjuntos[], int x, int y) {
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


bool Mesma_Componente(subset subconjuntos[], int u, int v){
	if(Find_Set(subconjuntos, u) == Find_Set(subconjuntos, v) ){
		return true;
	}
	else{
		return false;
	}	
}


// Funcao utilizada para verificar se o grafo tem ou nao ciclo
bool TemCiclo( grafo* g ) {
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    bool tem_ciclo = false;
    subset *s = Make_Subset(g->V);
	
    // DICA: Faca um laco de 0 ate g->E unindo os vertices.
    //       Caso os verticies ja pertencerem ao memso componente conexo (usar Find_Set),
    //       significa que o grafo tem um ciclo.
	
	for(int i = 0; i < g->E; i++){
		int x = g->VetorDeArestas[i].origem;
		int y = g->VetorDeArestas[i].destino;
		
		if(Mesma_Componente(s, x, y)){
			tem_ciclo = true;
		}
		
		Union(s, x, y);
	}
	
    Destroy_Subset(s);
    return tem_ciclo;
}

int QuantidadeComponentesConexas( grafo* g ) {
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    subset *s = Make_Subset(g->V);
    for(int i=0; i<g->E; i++) {
        int rx = Find_Set(s, g->VetorDeArestas[i].origem);
        int ry = Find_Set(s, g->VetorDeArestas[i].destino);
        if (rx!=ry)
        	Union(s, rx, ry);
    }
	int nc=0;
    // DICA: Quando o elemento i for o mesmo que o pai[i] (se representante), significa que representa um componente conexo.
    //       Basta contar a quantidade de vertices nesta situacao...
	
	for(int i = 0; i < g->V; i++){
		if(i == Find_Set(s, i)){
			nc++;
		}
	}
	
    Destroy_Subset(s);
    return nc;
}


int MaiorComponenteConexa( grafo* g ) {
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // DICA: Inicio similar a funcao anterior, mas eh preciso contar quantos vertices tem cada
    //       componente conexo para descobrir qual eh de maior quantidade.
    //       Tente criar um vetor auxiliar (tamanho g->V), percorrer todos os vertices e
    //       incrementar o no representante (pai) para cada vertice. Assim, basta buscar a maior contagem.
	
	if(g->V <= 0){
		return 0;
	}
	
	subset *s = Make_Subset(g->V);
	  for(int i=0; i<g->E; i++) {
        int rx = Find_Set(s, g->VetorDeArestas[i].origem);
        int ry = Find_Set(s, g->VetorDeArestas[i].destino);
        if (rx!=ry)
        	Union(s, rx, ry);
    }
	
	int max = 0;
	int *vetor = (int *)malloc((g->V) * sizeof(int));
	
	for(int i = 0; i < g->V; i++){
		int ind = Find_Set(s, i);
		vetor[ind]++;
	}
	
	for(int i = 0; i < g->V; i++){
		if(max < vetor[i]){
			max = vetor[i];
		}
	}
	
	free(vetor);
	Destroy_Subset(s);
	
    return max;
}

int compara(const void *x, const void *y){
	//compara arestas pelo peso
	
	Aresta *i = (Aresta*)x;
	Aresta *j = (Aresta*)y;
	
	return i->peso > j->peso;
	
}

int SomaPesoArestasDaArvoreGeradoraMinima( grafo* g ) {
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // IMPLEMENTAR !!!
    // DICA: Use o algoritmo de Kruskal (disponivel no slide):
    //       Ordene as arestas por peso e crie um contador que soma todos os pesos
    //       utilizados na formacao da Arvore Geradora Minima.
	
	//Aresta *resultante = (Aresta *)malloc((g->V)*sizeof(Aresta));
	Aresta resultante[g->V];	
	qsort(g->VetorDeArestas, g->E, sizeof(g->VetorDeArestas[0]), compara); //ordena qsort por peso
	
	subset *s = Make_Subset(g->V);
	
	int x = 0, y = 0;
	while(x < g->V - 1 && y < g->E){
		Aresta prox = g->VetorDeArestas[y++];
		
		int a = Find_Set(s, prox.origem);
		int b = Find_Set(s, prox.destino);
		
		if(a != b){
			resultante[x++] = prox;
			Union(s, a, b);
		}
		
	}
	
	int count = 0;	
	for(int i = 0; i < x; ++i){
		count += resultante[i].peso;
		
	}
	
	Destroy_Subset(s);
    return count;
}
