#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Aresta{
	int u; //fonte
	int v; //destino
	float peso; //peso 
	const char *nomeEmp;
    //const char *enderecoEmp;
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

struct enc{
	//int ind;
	char str[256];
	
}; typedef struct enc enc;

int procuraElementoEnc(char s[256], enc *dict){
	for(int i = 0; i < 256; i++){
		if(strcmp(dict[i].str, s) == 0){ // se achou s em dict
			return i;
		}
	}	
	return -1;	
}

// LZW Compressão - Encode
int * encoding(char s[256]){
	enc *dict = (enc*)malloc(256 * sizeof(enc));		
	int code = 256;
	int indOutput = 0;
	int *output = (int*)malloc(256*sizeof(int));
	char ch[256] = "";
	char p[256] = "";
	char c[256] = "";
	char pc[550] = "";
	char aux[550] = "";
	
	strncat(p, &s[0], 1);
	
	for(int i = 0; i <= 255; i ++){
		ch[0] = '\0';
		char aux = i + '0';
		strncat(ch, &aux , 1);		
		strcat(dict[i].str, ch);		
	}	
	
	for(int i = 0; i < strlen(s); i++){
		if(i != strlen(s)-1){			
			strncat(c, &s[i+1], 1);
		}
		
		strcat(pc, p);
		strcat(pc, c);
		int procura = procuraElementoEnc(pc, dict);
		
		if(procura != -1){
			p[0] = '\0';
			strcat(p, pc);			
		}
		
		else{
			int procura_p = procuraElementoEnc(p, dict);
			output[indOutput] = procura_p;			
			indOutput++;			
			strcpy(dict[code].str, pc);
			code++;
			p[0] = '\0';
			strcpy(p, c);
		}		
		c[0] = '\0';		
	}	
	
	return output;			
}

// Cria grafo com V vértices e E arestas
Grafo* criaGrafo(int V, int E){	
	Grafo *grafo = (Grafo*)malloc(sizeof(Grafo));	
	grafo->aresta = (Aresta*)malloc(E * sizeof(Aresta));
	grafo->V = V;
	grafo->E = E;

	return grafo;
}

void destruirGrafo(Grafo *g) {
    free(g->aresta);
    free(g);
}

// Adiciona dados ao grafo
void adicionaArestaGrafo(Grafo *Grafo, int ind, int u, int v, float peso, const char *nomeEmp,  unsigned long int CNPJ, const char *produtos){
	Grafo->aresta[ind].u = u;
	Grafo->aresta[ind].v = v;
	Grafo->aresta[ind].peso = peso;
	Grafo->aresta[ind].nomeEmp = nomeEmp;
	//Grafo->aresta[ind].enderecoEmp = enderecoEmp;
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

void Destroy_Subset(subset *s) {
    free(s);
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
		printf("Nome empresa: %s - CNPJ: %lu\n", resultado[i].nomeEmp, resultado[i].CNPJ);	
		printf("Produtos: %s\n", resultado[i].produtos);
		printf("\n-----------------------------------------------------------------------------------------------------------\n");
		custoMin = custoMin + resultado[i].peso;
	}
	
	printf("Custo mínimo: %.2f\n", custoMin);
	printf("\n-----------------------------------------------------------------------------------------------------------\n");
	
	Destroy_Subset(subsets);
}


int main(){
	int V = 4; 
	int E = 5; 
	Grafo* grafo = criaGrafo(V, E);
	

	// Teste input no grafo e custo mínimo
	adicionaArestaGrafo(grafo, 0, 0, 1, 11.0, "AAA",  9999999, "teste;teste;teste");
	adicionaArestaGrafo(grafo, 1, 0, 2, 6.65, "CCC",  111211111, "teste;testea;testeb");
	adicionaArestaGrafo(grafo, 2, 0, 3, 5.92, "EEE",  11141111, "teste;testea;testeb");
	adicionaArestaGrafo(grafo, 3, 1, 3, 15.89, "GGG",  112311111, "teste;testea;testeb");
	adicionaArestaGrafo(grafo, 4, 2, 3, 3.72, "III",  11198111, "teste;testea;testeb");

	Kruskal(grafo);	
	int *e = encoding((char*)grafo->aresta[0].produtos);
	
	printf("\n------------------------------------------------- Encoding ------------------------------------------------- \n");
	printf("Índice: %d\n", 0);
	for(int i = 0; i < strlen(grafo->aresta[0].produtos); i++){
		printf("%d ", e[i]);
	}
	
	destruirGrafo(grafo);
	
	return 0;
}

