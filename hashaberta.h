#ifndef HASHABERTA_H
#define HASHABERTA_H
#include "lista.h"

typedef struct elementoAberta{
    TContato *contato;
    int situacao; //0 - nunca utilizado, 1 - ocupado, -1 excluido
}TElementoAberta;

typedef struct hashAberta{
    TElementoAberta *tabela;
    int quant;
    int tamanho;
    float fatorCarga;
}THashAberta;

void inicializaHashAberta (THashAberta *hashAberta, int tamanhoInicial, float fatorCarga);

unsigned long int hashCodeAberta(TContato *contato, THashAberta *hash);

THashAberta* inserirAberta(TContato *contato, THashAberta *hash);

THashAberta* expandeHashAberta(THashAberta *hash);

void saidaHashAberta(THashAberta *hash);

void listarAberta(THashAberta *hash);

TRetorno removerAberta(THashAberta *hash, TContato *contato);

TRetorno buscarHashAberta(THashAberta *hash, TContato *contato);

#endif // HASHABERTA_H

