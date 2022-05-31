#include <stdlib.h>
#include "pilha.h"

pilha *cria() {
    pilha *p = (pilha*) malloc(sizeof(pilha));
    p->size = 0;
    p->topo = NULL;
    return p;
}

void insere(pilha *p, ii x) {
    cell *novo = (cell*) malloc(sizeof(cell));
    novo->c = x;

    if(p->size == 0) {
        p->topo = novo;
        novo->prox = NULL;
    }
    else {
        novo->prox = p->topo;
        p->topo = novo;
    }
    p->size++;
    return;
}

void retira(pilha *p) {
    if(p->size == 0) return;
    cell *aux = p->topo;
    p->topo = p->topo->prox;
    free(aux);
    p->size--;
    return;
}

void destroi(pilha *p) {
    while(p->size) retira(p);
    free(p);
    return;
}
