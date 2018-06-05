#include "arquivo.h"
#define TAM_INICIAL 100000
#define FATOR 0.95

void execucao()
{
    THashFechada hashFechada = criaHashFechada(1000);
    TContato *contato;
    TLista *lista = inicLista();
    THashAberta *hashAberta = (THashAberta *) malloc (sizeof(THashAberta));
    TRetorno *retLista, *retAberta, *retFechada;
    retLista = (TRetorno*) malloc (sizeof (TRetorno));
    retAberta = (TRetorno*) malloc (sizeof (TRetorno));
    retFechada = (TRetorno*) malloc (sizeof (TRetorno));


    char urlEntrada[] = "entrada_mil.txt",urlOperacoes[] = "operacoes.txt", info[100],
            *psRetorno, urlBusca[] = "buscas.txt";
    FILE *arq, *arqBusca;


    inicializaHashAberta(hashAberta,TAM_INICIAL, FATOR);

    arq = fopen(urlEntrada, "r");

    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo de entrada\n");
    else
    {
        while( (fgets(info, sizeof(info), arq))!=NULL )
        {
            contato = (TContato*) malloc (sizeof (TContato));
            psRetorno = strtok(info, ";");
            strcpy(contato->nome, psRetorno);
            /* Nas proximas chamadas, deve-se passar um ponteiro �nulo�.
                 * Isto �indica� para a funcao que a pesquisa deve continuar
                 * no ponteiro anterior. */
            psRetorno = strtok('\0', "");

            /* Um valor nulo (NULL) eh considerado sempre falso em comparacoes booleanas. */
            if(psRetorno)
            {
                if (verificaBarraN(psRetorno) == 1)
                {
                    // Usado para tirar o \n do fim da string.
                    psRetorno = strtok(psRetorno, "\n");
                }
                strcpy(contato->telefone, psRetorno);
            }
            insereOrdenado(contato, lista);
            insereHashFechada(&hashFechada, contato);
            hashAberta = inserirAberta(contato, hashAberta);
        }
    }
    fclose(arq);

    arq = fopen(urlOperacoes, "r");
    if (arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo de operacoes\n");
    else
    {
        while( (fgets(info, sizeof(info), arq))!=NULL )
        {
            contato = (TContato*) malloc (sizeof (TContato));
            psRetorno = strtok(info, ";");

            if (strcmp(psRetorno, "E") == 0)
            {
                contato = (TContato*) malloc (sizeof (TContato));

                psRetorno = strtok('\0', "\n");
                strcpy(contato->nome, psRetorno);

                *retLista = remover(lista, contato);
                *retFechada = removerHashFechada(&hashFechada, contato);
                strcpy(contato->telefone, retLista->contato.telefone);
                *retAberta = removerAberta(hashAberta, contato);

                while (retLista->ret == 1)
                {
                    *retLista = remover(lista, contato);
                    *retFechada = removerHashFechada(&hashFechada, contato);
                    strcpy(contato->telefone, retLista->contato.telefone);
                    *retAberta = removerAberta(hashAberta, contato);
                }
                free(contato);

            }
            else if (strcmp(psRetorno, "I") == 0)
            {
                contato = (TContato*) malloc (sizeof (TContato));
                psRetorno = strtok('\0', ";");
                strcpy(contato->nome, psRetorno);
                /* Nas proximas chamadas, deve-se passar um ponteiro �nulo�.
                     * Isto �indica� para a funcao que a pesquisa deve continuar
                     * no ponteiro anterior. */
                psRetorno = strtok('\0', "");

                // Um valor nulo (NULL) eh considerado sempre falso em comparacoes booleanas.
                if(psRetorno)
                {
                    if (verificaBarraN(psRetorno) == 1)
                    {
                        // Usado para tirar o \n do fim da string
                        psRetorno = strtok(psRetorno, "\n");
                    }
                    strcpy(contato->telefone, psRetorno);
                }
                insereOrdenado(contato, lista);
                insereHashFechada(&hashFechada, contato);
                hashAberta = inserirAberta(contato, hashAberta);
            }
            else if (strcmp(psRetorno, "B") == 0)
            {
                arqBusca = fopen(urlBusca, "a");

                psRetorno = strtok('\0', ";");
                strcpy(contato->nome, psRetorno);
                /* Nas proximas chamadas, deve-se passar um ponteiro �nulo�.
                    * Isto �indica� para a funcao que a pesquisa deve continuar
                    * no ponteiro anterior. */
                psRetorno = strtok('\0', "");
                /* Um valor nulo (NULL) eh considerado sempre falso em comparacoes booleanas. */
                if(psRetorno)
                {
                    if (verificaBarraN(psRetorno) == 1)
                    {
                        // Usado para tirar o \n do fim da string.
                        psRetorno = strtok(psRetorno, "\n");
                    }
                    strcpy(contato->telefone, psRetorno);
                }
                *retLista = buscar(lista, contato);
                *retFechada = buscarHashFechada(&hashFechada, contato);
                *retAberta = buscarHashAberta(hashAberta, contato);

                // Arquivo de saida de busca.
                if(arqBusca == NULL)
                    printf("Erro, nao foi possivel abrir o arquivo de busca\n");
                else
                {
                    fprintf(arqBusca, "%s;%s;%d;%d;%d;%d;%d;%d\n", contato->nome,
                            contato->telefone, retLista->ret, retLista->verific, retFechada->ret,
                            retFechada->verific, retAberta->ret, retAberta->verific);
                }
                fclose(arqBusca);
            }
        }
    }
    fclose(arq);
    // Arquivo de saida hashAberta
    saidaHashAberta(hashAberta);
    // Arquivo de saida hashFechada
    saidaHashFechada(&hashFechada);
}

