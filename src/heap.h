#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>

#define MAX_HEAP 10001

typedef struct item {
    char nome[100];
    char matricula[20];
    int ranking;
    char curso[50];
} Item;

typedef struct heap {
    Item *itens[MAX_HEAP];
    int tamanho;
} Heap;

void inicializar_heap(Heap *h);
int  heap_inserir(Heap *h, Item item);
Item* heap_remover(Heap *h);
Item* heap_topo(Heap *h);
void imprimir_heap(Heap *h, int qtd);
int  heap_vazia(Heap *h);
int  heap_cheia(Heap *h);

#endif