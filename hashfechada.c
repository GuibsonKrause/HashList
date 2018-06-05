#include "lista.h"
#include "hashfechada.h"
#include <string.h>

THashFechada criaHashFechada(int tam)
{
    int i;
    THashFechada hash;
    hash.tam = tam;
    hash.tabela = (TLista *) malloc (tam * sizeof (TLista));

    for (i = 0; i < tam; i++)
    {
        // Usar o metodo de iniciar lista da biblioteca de lista.
        inicializarLista(&hash.tabela[i]);
    }

    return hash;

}

unsigned long int hashCodeFechada(TContato *c, THashFechada *h)
{
    unsigned long int tam = 1, code;
    int lenght = strlen(c->nome);
    int i = 0;
    while (i < 3 && i <= lenght)
    {
        tam *= c->nome[i];
        i++;
    }
    code = tam % h->tam;
    return code;
}

void insereHashFechada(THashFechada *hash, TContato *contato)
{
    int code = hashCodeFechada(contato, hash);
    // Metodo da biblioteca lista.
    insereOrdenado(contato, &hash->tabela[code]);
}

TRetorno removerHashFechada(THashFechada *hash, TContato *contato)
{
    int code = hashCodeFechada(contato, hash);
    TRetorno *ret;
    ret = (TRetorno*) malloc (sizeof (TRetorno));

    // Metodo da biblioteca lista.
    *ret = remover(&hash->tabela[code], contato);

    return *ret;
}

void listarHashFechada(THashFechada *hash)
{
    int i;
    for (i = 0; i < hash->tam; i++)
    {
        // Metodo da biblioteca lista.
        listar(&hash->tabela[i]);
    }
}

void saidaHashFechada(THashFechada *hash)
{
    FILE *arq;
    char urlSaidafechada[] = "saidaHashFechada.txt";
    arq = fopen(urlSaidafechada, "a");
    TRetorno ret;
    int i;
    char string[500000];

    for (i = 0; i < hash->tam; i++)
    {
        // Passa o "i" para imprimir a indice na outra funcao.
        ret = saidaFechada(&hash->tabela[i], i);
        // Concatena todos os resultados para gerar a string do final do arquivo.
        strcat(string, ret.string);
        strcat(string, ";");
    }

    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo de saidaHashAberta\n");
    else
        fprintf(arq,"%s\n", string);
    fclose(arq);
}

TRetorno buscarHashFechada(THashFechada *hash, TContato *contato)
{
    TRetorno *ret;
    ret = (TRetorno*) malloc (sizeof (TRetorno));
    int code = hashCodeFechada(contato, hash);

    // Metodo da biblioteca lista.
    *ret = buscar(&hash->tabela[code], contato);

    return *ret;
}




