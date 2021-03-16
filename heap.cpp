#include "heap.h"
#include "internal.h"

// ATENCAO!!! ATENCAO!!! ATENCAO!!!
// ATENCAO!!! ATENCAO!!! ATENCAO!!!
// ATENCAO!!! ATENCAO!!! ATENCAO!!!
// --- CONSIDERE O INDICE ZERO (A[0]) A QUANTIDADE DE ELEMENTOS
// --- CONSIDERE QUE O VETOR VAI DE 1 ATE N (E NAO DE 0 ATE N-1)
// --- CONSIDERE QUE O VETOR JA TEM UM TAMANHO SUFICIENTEMENTE GRANDE PARA A INSERCAO

void MaxHeapify (tipoChave A[], int i)
{
    // IMPLEMENTAR
    // OBS.: O indice i vai de 1 ate A[0]
	
	int m = A[0];
	int e = 2*i;
	int d = (2*i + 1);
	int max;
	
	if(e <= m && A[e] > A[i]){
		max = e;
	}
	else{
		max = i;
	}
	
	if(d <= m && A[d] > A[max]){
		max = d;
	}
	
	if(max != i){
		int b = A[i];
		A[i] = A[max];
		A[max] = b;
		MaxHeapify(A,max);
	}
}

void BuildMaxHeap(tipoChave A[])
{
    // IMPLEMENTAR
    // OBS.: Chamar a funcao MaxHeapify
	
	int n = A[0];
	
	for(int i = n/2; i >= 1; i--){
		MaxHeapify(A, i);
	}
}

void HeapSort(tipoChave A[])
{
    // IMPLEMENTAR
    // DICA: Como a funcao MaxHeapify nao tem o argumento tamanho (como nos slides),
    //       armazene o tamanho atual (t = A[0]), decremente A[0] antes de chamar
    //       MaxHeapify, entao restaure o valor A[0] = t no final.
	
	BuildMaxHeap(A);
	int t = A[0];
	
	
	for(int i = t; i >= 2; i--){
		//troca
		int b = A[1];
		A[1] = A[i];
		A[i] = b;
		
		
		A[0] = A[0] - 1;
		MaxHeapify(A, 1);	
				
	}
	A[0] = t;	
	
}

tipoChave HeapMaximum(tipoChave A[])
{
    // IMPLEMENTAR
    // OBS.: Nao esqueca que o primeiro elemento eh o A[1]
    return A[1];
}

tipoChave HeapExtractMax(tipoChave A[])
{
    // IMPLEMENTAR
    // OBS.: Nao precisa tratar o caso do vetor vazio!
	
	tipoChave max = HeapMaximum(A);	
	int tam = A[0];
	A[1] = A[tam];
	tam = tam - 1;
	MaxHeapify(A, 1);
	
	return max;
}

void HeapIncreaseKey(tipoChave A[], int i, tipoChave key)
{
    // IMPLEMENTAR
    // OBS.: Nao precisa tratar o caso da chave alterada for menor que a chave atual!
	
	A[i] = key;
	while(i > 1 && A[i/2] < A[i]){
		//troca
		tipoChave b = A[i];
		A[i] = A[i/2];
		A[i/2] = b;
		
		i = i/2;		
	}
}

void MaxHeapInsert(tipoChave A[], tipoChave key)
{
    // IMPLEMENTAR
    // OBS.: Nao esquecer de aumentar a quantidade de elementos, ou seja, A[0]++
	
	A[0]++;
	int t = A[0];
	A[t] = key;	
	
	HeapIncreaseKey(A,t,key);
	
}
