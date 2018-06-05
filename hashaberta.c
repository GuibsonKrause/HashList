#include "lista.h"
#include "hashaberta.h"
#include <string.h>

THashAberta* expandeHashAberta(THashAberta *hash);

void inicializaHashAberta (THashAberta *hashAberta, int tamanhoInicial, float fatorCarga)
{
    hashAberta->quant = 0;
    hashAberta->tamanho = tamanhoInicial;
    hashAberta->fatorCarga = fatorCarga;
    hashAberta->tabela = (TElementoAberta*) malloc (tamanhoInicial * sizeof(TElementoAberta));

    int i;
    for (i =0; i< tamanhoInicial; i++)
    {
        hashAberta->tabela[i].situacao = 0;
    }
}

unsigned long int hashCodeAberta(TContato *contato, THashAberta *hash)
{
    unsigned long int code, tel;
    /* long int strtol(const char *str, char **endptr, int base)
     *  converts the initial part of the string in str to a long
     *  int value according to the given base,*/
    tel = strtol(contato->telefone, '\0', 10);
    code = tel % hash->tamanho;
    return code;
}

THashAberta* inserirAberta(TContato *contato, THashAberta *hash)
{
    //verifico se e necessario expandir.
    if (( (float)hash->quant/(float)hash->tamanho) > hash->fatorCarga)
        hash = expandeHashAberta(hash);

    unsigned long int code = hashCodeAberta(contato, hash);
    //Achar primeira posicao nao ocupada a partir do codigo calculado (note a circularidade).
    while (hash->tabela[code].situacao == 1)
        code = (code + 1) % hash->tamanho;

    hash->tabela[code].contato = contato;
    hash->tabela[code].situacao = 1;
    hash->quant++;
    return hash;
}

THashAberta* expandeHashAberta(THashAberta *hash)
{
    int i;
    //Aloco uma nova hash com o dobro do tamanho da orginal.
    THashAberta *novaHash;
    novaHash = (THashAberta *) malloc (sizeof(THashAberta));
    inicializaHashAberta(novaHash, hash->tamanho * 2, hash->fatorCarga);

    //Transfiro os elementos da hash antiga para a nova.
    for (i = 0; i < hash->tamanho; i++)
    {
        if (hash->tabela[i].situacao==1)
            inserirAberta((hash->tabela[i].contato), novaHash);
    }
    //desaloco a tabela da hash antiga e depois a hash em si.
    free(hash->tabela);
    free (hash);
    return novaHash;
}

void saidaHashAberta(THashAberta *hash)
{
    FILE *arq;
    char urlSaidaAberta[] = "saidaHashAberta.txt";
    arq = fopen(urlSaidaAberta, "a");
    unsigned long int code;
    int i, flag, coli = 0, nColi = 0;

    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo de saidaHashAberta\n");

    for (i = 0; i < hash->tamanho; i++)
    {
        if (hash->tabela[i].situacao == 1)
        {
            code = hashCodeAberta(hash->tabela[i].contato, hash);
            if(i == code)
            {
                // Nao ocorreu colisoes
                flag = 1;
                nColi++;
            }
            else
            {
                // Ocorreu colisoes
                flag = 0;
                coli++;
            }
            // Escreve no arquivo.
            fprintf(arq,"%d;%s;%s;%d\n", i, hash->tabela[i].contato->nome,hash->tabela[i].contato->telefone,flag);
        }
    }
    fprintf(arq,"%d;%d", nColi, coli);
    fclose(arq);
}

void listarAberta(THashAberta *hash)
{
    int i;

    for (i = 0; i < hash->tamanho; i++)
    {
        if (hash->tabela[i].situacao == 1)
            printf("\n Indice = %d - Telefone = %s - Nome = %s\n Situacao: %d\n",
                   i, hash->tabela[i].contato->telefone, hash->tabela[i].contato->nome,
                   hash->tabela[i].situacao);
    }
}

TRetorno removerAberta(THashAberta *hash, TContato *contato)
{
    unsigned long int code = hashCodeAberta(contato, hash);
    TRetorno *ret;
    ret = (TRetorno*) malloc (sizeof (TRetorno));
    while(hash->tabela[code].situacao != 0)
    {
        while (hash->tabela[code].situacao == -1)
        {
            // Hash code maior que a hash, entao elemento nao existe.
            if (code >= hash->tamanho)
            {
                ret->ret = 0;
                return *ret;
            }
            code++;
        }

        if (hash->tabela[code].situacao == 0)
        {
            ret->ret = 0;
            //Elemento nao existe.
            return *ret;
        }

        if (hash->tabela[code].contato == NULL)
        {
            ret->ret = 0;
        }

        // Elemento encontrado.
        if (strcmp(hash->tabela[code].contato->telefone, contato->telefone) == 0)
        {
            hash->tabela[code].situacao = -1;
            hash->tabela[code].contato = NULL;
            ret->ret = 1;
            return *ret;
        }

        code++;
    }
    //Elemento nao existe.
    return *ret;
}

TRetorno buscarHashAberta(THashAberta *hash, TContato *contato)
{
    unsigned long int code = hashCodeAberta(contato, hash);
    int verific = 0;
    TRetorno *ret;
    ret = (TRetorno*) malloc (sizeof (TRetorno));
    while(hash->tabela[code].situacao != 0)
    {
        while (hash->tabela[code].situacao == -1)
        {
            // Hash code maior que a hash, entao elemento nao existe.
            if (code >= hash->tamanho)
            {
                ret->ret = 0;
                ret->verific = verific;
                return *ret;
            }
            // Elemento removido, pula para o proximo.
            code++;
        }

        if (hash->tabela[code].situacao == 0)
        {
            ret->ret = 0;
            ret->verific = verific;
            //Elemento nao existe.
            return *ret;
        }

        if (hash->tabela[code].contato == NULL)
        {
            ret->ret = 0;
        }

        // Elemento encontrado.
        if (strcmp(hash->tabela[code].contato->telefone, contato->telefone) == 0)
        {
            ret->ret = 1;
            ret->verific = verific;
            return *ret;
        }

        code++;
        verific ++;
    }
}

