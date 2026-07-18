#include <stdio.h>
#include <stdlib.h>
#include "receitas.h"

void sugerirMenuVipTempo(Receita* catalogo[], int totalReceitas, int tempoMaximo) {
   double **dp = (double **)malloc((totalReceitas + 1) * sizeof(double *));
    for (int i = 0; i <= totalReceitas; i++) {
        dp[i] = (double *)calloc((tempoMaximo + 1), sizeof(double));
    }

    for (int i = 1; i <= totalReceitas; i++) {
        for (int t = 1; t <= tempoMaximo; t++) {
            if (catalogo[i - 1]->tempoPreparo <= t) {
                double incluindo = catalogo[i - 1]->avaliacao + dp[i - 1][t - catalogo[i - 1]->tempoPreparo];
                double excluindo = dp[i - 1][t];
                dp[i][t] = (incluindo > excluindo) ? incluindo : excluindo;
            } else {
                dp[i][t] = dp[i - 1][t];
            }
        }
    }

    printf("Resultados Por Tempo\n");
    printf("Maior Avaliação PPossível: %.2f\n", dp[totalReceitas][tempoMaximo]);
    printf("Receitas Selecionadas:\n");

    int tempoRestante = tempoMaximo;
    for (int i = totalReceitas; i > 0; i--) {
        if (dp[i][tempoRestante] != dp[i - 1][tempoRestante]) {
            printf("Receita: %s, Tempo de Preparo: %d minutos, Avaliação: %.2f\n",
                   catalogo[i - 1]->nome, catalogo[i - 1]->tempoPreparo, catalogo[i - 1]->avaliacao);
            tempoRestante -= catalogo[i - 1]->tempoPreparo;
        }
        
    }

    printf("Tempo restante: %d minutos\n", tempoRestante);

    for (int i = 0; i <= totalReceitas; i++) {
        free(dp[i]);
    }
    free(dp);
}
