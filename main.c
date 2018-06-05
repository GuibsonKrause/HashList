#include "arquivo.h"

int main()
{
    clock_t tempo;
    float hora, minuto, segundo;

    tempo = clock();

    execucao(); // Toda a parte logica do trabalho.

    segundo = (clock() - tempo) / (double)CLOCKS_PER_SEC;
    minuto = segundo / 60;
    hora = minuto / 60;
    printf("\nTempo: %.2f segundos\n", segundo);
    printf("Tempo: %.2f minutos\n", minuto);
    printf("Tempo: %.4f horas\n", hora);

    return 0;
}

