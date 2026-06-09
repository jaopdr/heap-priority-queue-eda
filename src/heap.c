#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "heap.h"

void inicializar_heap(Heap *h) {
    h->tamanho = 0;
}

int heap_vazia(Heap *h) {
    return h->tamanho == 0;
}

int heap_cheia(Heap *h) {
    return h->tamanho == MAX_HEAP - 1;
}

int heap_inserir(Heap *h, Item item) {
    if (heap_cheia(h)) {
        return -1;
    }
    
    h->tamanho++;
    int i = h->tamanho;
    h->itens[i] = (Item*)malloc(sizeof(Item));
    *(h->itens[i]) = item;

    int iteracoes = 0;
    while (i > 1 && strcmp(h->itens[i]->matricula, h->itens[i/2]->matricula) > 0) {
        Item *temp = h->itens[i];
        h->itens[i] = h->itens[i / 2];
        h->itens[i / 2] = temp;
        i /= 2;
        iteracoes++;
    }
    
    return iteracoes;
}

Item* heap_remover(Heap *h) {
    if (heap_vazia(h)) {
        return NULL;
    }
    
    Item *removido = h->itens[1];
    h->itens[1] = h->itens[h->tamanho];
    h->tamanho--;

    int i = 1;
    while (2 * i <= h->tamanho) {
        int filho_esquerdo = 2 * i;
        int filho_direito = 2 * i + 1;
        int maior_filho = filho_esquerdo;

        if (filho_direito <= h->tamanho && strcmp(h->itens[filho_direito]->matricula, h->itens[filho_esquerdo]->matricula) > 0) {
            maior_filho = filho_direito;
        }

        if (strcmp(h->itens[i]->matricula, h->itens[maior_filho]->matricula) >= 0) {
            break;
        }

        Item *temp = h->itens[i];
        h->itens[i] = h->itens[maior_filho];
        h->itens[maior_filho] = temp;
        i = maior_filho;
    }
    
    return removido;
}

Item* heap_topo(Heap *h) {
    if (heap_vazia(h)) {
        return NULL;
    }
    return h->itens[1];
}

void imprimir_heap(Heap *h, int qtd) {
    for (int i = 1; i <= qtd && i <= h->tamanho; i++) {
        printf("%s %s %d %s\n", h->itens[i]->nome, h->itens[i]->matricula, h->itens[i]->ranking, h->itens[i]->curso);
    }
}