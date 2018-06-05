#include "lista.h"
#include <string.h>

TLista *inicLista()
{
    TLista *l = (TLista*) malloc (sizeof (TLista));
    l->prim = NULL;
    l->ult = NULL;
    return l;
}

TLista inicializarLista(TLista * lista)
{
    lista->prim = NULL;
    lista->ult = NULL;
}

int listaVazia (TLista *l)
{
    if (l->prim == NULL)
        return 1;
    else
        return 0;
}

void insereOrdenado (TContato *contato, TLista *l)
{
    TElemento *novo = (TElemento*) malloc (sizeof (TElemento));
    TElemento *p = l->prim, *aux = l->prim;

    novo->contato = contato;
    novo->prox = NULL;
    novo->ant = NULL;
    l->tam = 0;

    if (listaVazia(l))
    {
        // lista vazia.
        l->prim = novo;
    }
    else
    {
        // percorre lista.
        while ((p != NULL)&& strcmp(p->contato->nome, novo->contato->nome) <= 0)
        {
            aux = p;
            p = p->prox;
        }

        // Novo eh menor do que todos da lista.
        if (p == aux)
        {
            novo->ant = NULL;
            l->prim->ant = novo;
            novo->prox = l->prim;
            l->prim = novo;
            l->tam++;
        }
        // Novo eh maior do que todos da lista.
        else if (p == NULL)
        {
            aux->prox = novo;
            novo->ant = aux;
            novo->prox = NULL;
            l->tam++;
        }
        // se "j" eh menor do que "i" significa que o novo estah no meio.
        else
        {
            aux->prox->ant = novo;
            novo->prox = aux->prox;
            novo->ant = aux;
            aux->prox = novo;
            l->tam++;
        }
    }
}

void listar(TLista *l)
{
    int i = 1;
    TElemento *atual = (TElemento*)malloc(sizeof(TElemento));
    atual = l->prim;

    if (atual == NULL)
    {
        printf("A lista esta vazia!\n");
        return;
    }

    while(atual != NULL)
    {
        printf("\nComponete %d da lista\n", i);
        printf("\nNome: %s\n",atual->contato->nome);
        printf("Telefone: %s\n", atual->contato->telefone);
        atual = atual->prox;
        i++;
    }//while.
}

TRetorno saidaFechada(TLista *l, int i)
{
    TRetorno *ret;
    ret = (TRetorno*) malloc (sizeof (TRetorno));
    int count = 0;
    FILE *arq;
    char string[500000], strCount[500000];
    char urlSaidafechada[] = "saidaHashFechada.txt";
    arq = fopen(urlSaidafechada, "a");
    TElemento *atual = (TElemento*)malloc(sizeof(TElemento));
    atual = l->prim;

    if(arq == NULL)
        printf("Erro, nao foi possivel abrir o arquivo de saidaHashAberta\n");

    if (atual == NULL) // lista vazia
    {
        fprintf(arq,"%d;vazio;vazio\n",i);
        sprintf(string, "%d", i); // int to string
        strcat(string, ";"); // concatena strings
        sprintf(strCount, "%d", count);
        strcat(string, strCount);


        fclose(arq);
        strcpy(ret->string, string);
        return *ret;
    }

    while(atual != NULL)
    {
        fprintf(arq,"%d;%s;%s;\n", i, atual->contato->nome, atual->contato->telefone);
        count++;
        atual = atual->prox;
    }//while.
    sprintf(string, "%d", i); // int to string
    strcat(string, ";"); // concatena strings
    sprintf(strCount, "%d", count);
    strcat(string, strCount);


    fclose(arq);
    strcpy(ret->string, string);
    return *ret;
}

// busca elemento na lista.
TRetorno buscar(TLista *l, TContato *contato)
{
    int verific = 0;
    TElemento *aux;
    TRetorno *ret;
    ret = (TRetorno*) malloc (sizeof (TRetorno));

    // se lista vazia retorna -1.
    if (listaVazia(l))
    {
        ret->ret = 0;
        return *ret;
    }
    else
    {
        aux = l->prim;
        // percorre a lista enquanto o nome buscado for maior do que o comparado.
        while ((aux != NULL) && (strcmp(aux->contato->nome, contato->nome) < 0))
        {
            aux = aux->prox;
            verific++;
        }
        if (aux == NULL || (strcmp(aux->contato->nome, contato->nome) > 0))
        {
            ret->ret = 0;
            ret->verific = verific;
            // elemento nao encontrado e quantidade de buscas feitas.
            return *ret;
        }
    }

    ret->verific = verific;
    ret->ret = 1;
    // elemento encontrado e quantidade de buscas feitas ate encontrar.
    return *ret;
}

TRetorno remover(TLista *l, TContato *contato)
{
    TElemento *ante, *aux;
    TRetorno *ret;
    ret = (TRetorno*) malloc (sizeof (TRetorno));

    aux = l->prim;
    ante = NULL;

    // se lista vazia retorna -1.
    if (listaVazia(l))
    {
        ret->ret = -1;
        return *ret;
    }
    else
    {
        // percorre a lista enquanto o nome buscado for maior do que o comparado.
        while ((aux != NULL) && (strcmp(aux->contato->nome, contato->nome) < 0))
        {
            ante = aux;
            aux = aux->prox;
        }
        // elemento nao foi encontrado.
        if (aux == NULL || (strcmp(aux->contato->nome, contato->nome) > 0))
        {
            ret->ret = 0;
            return *ret;
        }
        // esta no meio.
        if (aux != l->prim && aux != l->ult)
            ante->prox = aux->prox;
        else
        {
            // esta no inicio.
            if (aux == l->prim)
                l->prim = l->prim->prox;
            // esta no fim.
            if (aux == l->ult)
            {
                l->ult = ante;
                // unico.
                if (ante != NULL)
                    ante->prox = NULL;
            }
        }
        // Telefone utilizado para remover da hash aberta.
        strcpy(ret->contato.telefone, aux->contato->telefone);
        free(aux);
        ret->ret = 1;
        // elemento removido.
        return *ret;
    }
}

// Verifica se a string contem um \n que atrapalha da comparacao.
int verificaBarraN(char string[])
{
    int i, lenght = strlen(string);
    for (i = 0; i <= lenght; i++)
    {
        if (string[i] == '\n')
            return 1;
    }
    return 0;
}

