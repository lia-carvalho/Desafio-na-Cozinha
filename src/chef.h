#ifndef chef_h
#define chef_h

#include "receitas.h"
#include "trie.h"

ListaReceitas* menuEconomico(Receita** todas, int total, double orcamento);
ListaReceitas menuRapido(Receita** todas, int total, int tempo);
void imprimirResultados(ListaReceitas* lista);

#endif
