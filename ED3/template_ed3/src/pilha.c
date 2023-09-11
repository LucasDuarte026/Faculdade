#include "pilha.h"

PILHA *new_pilha()
{
    PILHA *new_pilha = (PILHA *)malloc(1 * (sizeof(PILHA)));
    new_pilha->size = 0;
    new_pilha->data = 0;
    new_pilha->prev = NULL;

    return new_pilha;
}

bool push_pilha(int elem)
{
}

int pop_pilha()
{
}
