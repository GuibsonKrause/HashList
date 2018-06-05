#ifndef HASHFECHADA_H
#define HASHFECHADA_H
#include "lista.h"
/*------------------------------------------STRUCTS--------------------------------------------------*/

typedef struct HashFechada
{
    TLista *tabela;
    int tam;
}THashFechada;

/*-----------------------------------------CHAMADA DAS FUNCOES--------------------------------------------*/

THashFechada criaHashFechada(int tam);

unsigned long int hashCodeFechada(TContato *c, THashFechada *h);

void insereHashFechada(THashFechada *hash, TContato *contato);

TRetorno removerHashFechada(THashFechada *hash, TContato *contato);

void listarHashFechada(THashFechada *hash);

void saidaHashFechada(THashFechada *hash);

TRetorno buscarHashFechada(THashFechada *hash, TContato *contato);

#endif // HASHFECHADA_H

