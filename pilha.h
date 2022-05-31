#ifndef PILHA_H_INCLUDED
#define PILHA_H_INCLUDED
#include "pair.h"

typedef struct cell{
    ii c;
    struct cell *prox;
}cell;

typedef struct pilha{
        int size;
        struct cell *topo;
}pilha;

pilha *cria();
void insere(pilha *p, ii x);
void retira(pilha *p);
void destroi(pilha *p);

#endif // PILHA_H_INCLUDED
