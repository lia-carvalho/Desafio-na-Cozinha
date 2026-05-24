#ifndef chef_h
#define chef_h

#include "receitas.h"
#include "trie.h"


ListaReceitas* gerarRapido(Receita** catalogo, int totalReceitas, int tempo);
ListaReceitas* gerarEconomico(Receita** catalogo, int totalReceitas, double orcamento);

#endif
