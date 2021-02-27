#include <stdlib.h>
#include "btree.h"


btNo *criarNo(const unsigned char ordem){
	// Função auxiliar btCriar
	btNo *no = (btNo*)malloc(sizeof(btNo));
	no->ehFolha = 1;
	no->numChaves = 0;
	no->chaves = (int*)malloc(sizeof(*no->chaves) * ordem );
	no->filhos = (btNo**)malloc(sizeof(*no->filhos) * (ordem+1) );
	
	return no;
}

bTree btCriar(const unsigned char ordem) {
    bTree b;
	b.ordem = ordem;
	b.raiz = criarNo(ordem);	
	
    return b;
}

void btDestruir(btNo *no){
	if(no == NULL){
		return;
	}
	
	if(!no->ehFolha){
		for(int i = 0; i < no->numChaves+1; i++){
			btDestruir(no->filhos[i]);
		}
	}
	
	free(no->chaves);
	free(no->filhos);
	free(no);
	
}

void btDestruir(bTree b) {
	btDestruir(b.raiz);
    
}

int buscarChave(int n, const int *a, int chave){
	
	int lo = -1, hi = n, mid;
	while(lo + 1 < hi){
		mid = (lo+hi)/2;
		
		if(a[mid] == chave){
			return mid;
		}
		else if(a[mid] < chave){
			lo = mid;
		}
		else{
			hi = mid;
		}
		
	}
	
}

int btBuscar(btNo *b, int chave){
	int pos;
	if(b->numChaves == 0){
		return 0;
	}
	
	pos = buscarChave(b->numChaves, b->chaves, chave);
	
	if(pos < b->numChaves && b->chaves[pos] == chave){
		return 1; //chave encontrada
	}
	else{
		return(!b->ehFolha && btBuscar(b->filhos[pos], chave));  //chave não encontrada, tenta nó filho
	}
}

int btBuscar(bTree b, int chave) {
    return btBuscar(b.raiz, chave);    
}


btNo *inserirInterno(btNo *b, int chave, int *mediana, const unsigned char ordem){
	int pos, mid;
	btNo *b2;
	
	pos = buscarChave(b->numChaves, b->chaves, chave);
	
	if(pos < b->numChaves && b->chaves[pos] == chave){
		return 0;
	}
	
	if(b->ehFolha){
		for(int i = b->numChaves; i >pos; i--){
			b->chaves[i] = b->chaves[i-1];			
		}
		b->chaves[pos] = chave;		
		b->numChaves++;
	}
	else{		
		b2 = inserirInterno(b->filhos[pos], chave, &mid, ordem);
		if(b2){
			for(int i = b->numChaves; i >pos; i--){
				b->chaves[i] = b->chaves[i-1];
				b->filhos[i+1] = b->filhos[i];
		    }
			
			b->chaves[pos] = mid;
			b->filhos[pos+1] = b2;
			b->numChaves++;
		}		
		
	}
	
	if(b->numChaves >= ordem){
		mid = b->numChaves/2;
		*mediana = b->chaves[mid];
		b2 = criarNo(ordem);
		b2->numChaves = b->numChaves - mid - 1;
		b2->ehFolha = b->ehFolha;
		
		for(int i = mid+1; i < b->numChaves+1; i++){
			b2->chaves[(i-(mid+1))] = b->chaves[i];
		}
		
		if(!b->ehFolha){
			for(int i = mid+1; i < b->numChaves+1; i++){
				b2->filhos[(i-(mid+1))] = b->filhos[i];
			}
		}
		
		b->numChaves = mid;
		return b2;
		
	}
	else{
		return 0;
	}
	
}

void btInserir(bTree b, int chave) {
	btNo *b1;
	btNo *b2;
	int mediana;
	
	b2 = inserirInterno(b.raiz, chave, &mediana, b.ordem);
	
	if(b2){
		b1 = criarNo(b.ordem);
		
		for(unsigned char i = 0; i < b.ordem; i++){
			b1->chaves[i] = b.raiz->chaves[i];
			b1->filhos[i] = b.raiz->filhos[i];			
		}
		
		b1->filhos[b.ordem] = b.raiz->filhos[b.ordem];
		b1->ehFolha = b.raiz->ehFolha;
		b.raiz->ehFolha = 0;
		b1->numChaves = b.raiz->numChaves;
		b.raiz->numChaves = 1;
		
		b.raiz->chaves[0] = mediana;
		b.raiz->filhos[0] = b1;
		b.raiz->filhos[1] = b2;
		
	}
    
}

int btAltura(bTree b) {
	int altura = 1;
	btNo * tmp;
	
	for(tmp = b.raiz; !tmp->ehFolha; tmp = tmp->filhos[0]){
		altura++;
	}
    
    return altura;
}

int btContaNos(btNo *b){	
	
	if(b->ehFolha){
		return 1;
	}
	
	int conta = 1; 
	
	for(int i = 0; i < b->numChaves + 1; i++){
		conta+= btContaNos(b->filhos[i]);
	}
	
	return conta;
}

int btContaNos(bTree b) {
    return btContaNos(b.raiz);
    
}

int btContaChaves(btNo *t){
	if(t->ehFolha){
		return t->numChaves;
	}
	
	int conta = 0;
		
	for(int i = 0; i < t->numChaves + 1; i++){
		conta += btContaChaves(t->filhos[i]);
		
	}
	
	return conta + t->numChaves;
}

int btContaChaves(bTree t) {
	return btContaChaves(t.raiz);  
}
