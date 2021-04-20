#ifndef PROJETO_H
#define PROJETO_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define ORDEM 3

struct registro{
	char *nome;	
	int idade;
	char *endereco;	
	char * email;

};
typedef struct registro registro;

struct t_bplus{
	int *chaves;
	int num_chaves;
	void **ponteiro;
	bool ehFolha; 
	struct t_bplus *pai;
	struct t_bplus *prox;

};
typedef struct t_bplus node;

void insere_fila(node *t);
node * retira_fila(void);
void imprime_registros(node *const raiz);




#endif