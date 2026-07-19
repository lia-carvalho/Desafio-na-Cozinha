#ifndef MODULO6_H
#define MODULO6_H

#include "receitas.h"

void iniciarModulo6(Receita** catalogo, int totalReceitas);

void sugerirMenuVipTempo(Receita* catalogo[], int totalReceitas, int tempoMaximo);
void sugerirMenuVipPreco(Receita* catalogo[], int totalReceitas, int precoMaximo);

#endif
