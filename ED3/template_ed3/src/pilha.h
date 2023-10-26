#ifndef PILHA_H
#define PILHA_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
typedef struct pilha{
    int data;
    int size;
    struct pilha *prev;
     
}PILHA;

PILHA *new_pilha();
bool push_pilha(int elem);
int pop_pilha();


#endif