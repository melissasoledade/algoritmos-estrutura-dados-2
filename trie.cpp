#include "trie.h"

// DICA: Estude o arquivo trie.h antes de iniciar a sua implementacao!

no *criarNo(void) {
    // IMPLEMENTAR !!!
    // Dica: Aloca um no, atribua o tipo como 'I' e todos os filhos como NULL.
    int i;
	no *novo = (no *)malloc(sizeof(no));
	
	if(novo != NULL){
		novo->tipo = 'I';
		
		for(i = 0; i<TAMANHO_ALFABETO; i++)
			novo->filho[i] = NULL;
	}
	
	return novo;
}

void apagarArvore(no *raiz) {
    // IMPLEMENTAR !!!
    // Dica 1: Desaloque todos os nos filhos e depois desaloca o no atual.
    // Dica 2: Usar recursao facilita!
	
	int i;
	
	if (raiz == NULL) {
		return;
	}    
	
	for (i=0; i<TAMANHO_ALFABETO; i++) {
		apagarArvore(raiz->filho[i]);
	}
	  
	free(raiz);
}

void adicionarPalavra(char *palavra, no *raiz) {
    // IMPLEMENTAR !!!
    // Dica 1: Use um laco iterativo de 0 ate strlen(palavra)
    // Dica 2: Criar o no com a funcao criarNo (caso nao existir)
    // Dica 3: Utilize a macro CHAR_TO_INDEX (ver trie.h) para converter o caractere para o indice filho
    // Dica 4: Nao esqueca de mudar o tipo para 'P' no ultimo noh que representa o ultimo caractere
	int nivel = 0, indice;
	no *tmp = raiz;
	
	for(nivel=0; nivel<strlen(palavra); nivel++){
		indice = CHAR_TO_INDEX(palavra[nivel]);
		if(tmp->filho[indice]==NULL)
			tmp->filho[indice] = criarNo();
		tmp = tmp->filho[indice];		
	}
	tmp->tipo = 'P';
}

int buscaPalavra(char *palavra, no *raiz) {
    // IMPLEMENTAR !!!
    // Dica 1: Funcao similar ao adicionarPalavra
    // Dica 2: Se o ultimo noh que representa o ultimo caractere for do tipo 'I', a palavra nao existe
    // IMPORTANTE:
    //   retorne 0 se a palavra nao exite
    //   retorne 1 se a palavra existir
    int i, indice;
	no *tmp = raiz;
	
	for(i=0; i<strlen(palavra); i++){
		indice = CHAR_TO_INDEX(palavra[i]);
		
		if(tmp->filho[indice] != NULL)
			tmp = tmp->filho[indice];
		else
			break;
	}
	
	if(palavra[i] == '\0' && tmp->tipo == 'P')
		return 1;
	else
		return 0;
}

int numeroDeNos(no *r) {	
    // IMPLEMENTAR !!!
    // Dica: A funcao pode ser muito simples se utilizar recursao
	
	int nos = 0, i;
	
	if(r == NULL){
		return 0;
	}
	
	for(i = 0; i<TAMANHO_ALFABETO; i++){
		nos = nos + numeroDeNos(r->filho[i]);
	}
	nos++;
	
	return nos; 
}

int numeroDePalavras(no *r) {
    // IMPLEMENTAR !!!
    // Dica: Similar a funcao numeroDeNos, mas contabilize apenas os tipos 'P', que representa as palavras
	int i, palavras = 0;
	
    if(r == NULL){
		return 0;
	}
	
	for(i = 0; i<TAMANHO_ALFABETO; i++){
		palavras = palavras + numeroDePalavras(r->filho[i]);
	}
	
	if(r->tipo == 'P'){
		palavras++;
	}
	
	return palavras;
}

int max(int a, int b){
	// máximo entre a e b
	if(a > b){
		return a;
	}
	else{
		return b;
	}
}

int altura(no *r) {
    // IMPLEMENTAR !!!
    // Dica: A funcao pode ser muito simples se utilizar recursao
	int i, a = 0;
	
    if(r == NULL){
		return 0;
	}
	
	for(i = 0; i<TAMANHO_ALFABETO; i++){
		a = max(a, altura(r->filho[i]));
	}
	a++;
	
	return a - 1;
}

void removerPalavra(char *palavra, no *raiz) {
    // IMPLEMENTAR !!!
    // Nota: Esta funcao eh a mais elaborada. Recomendo criar funcoes auxiliares e utilizar recursao
}
