#ifndef LISTA_H
#define LISTA_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Contato
{
    char telefone[50];
    char nome[50];
}TContato;

typedef struct Elemento
{
    TContato *contato;
    struct Elemento *ant, *prox;
}TElemento;

typedef struct lista
{
    struct Elemento *prim, *ult;
    int tam;
}TLista;

typedef struct retorno
{
    int ret, verific;
    TContato contato;
    char string[500000];
}TRetorno;

TLista *inicLista();

TLista inicializarLista(TLista * lista);

int listaVazia (TLista *l);

void insereOrdenado (TContato *contato, TLista *l);

//void insereNoFim (TLista *l);

void listar(TLista *l);

TRetorno saidaFechada(TLista *l, int i);

TRetorno buscar(TLista *l, TContato *contato);

TRetorno remover(TLista *l, TContato *contato);

int verificaBarraN(char string[]);

#endif // LISTA_H

