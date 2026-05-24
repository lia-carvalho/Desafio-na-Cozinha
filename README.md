# Desafio na Cozinha
Trabalho da disciplina de Algoritmos e Estrutura de Dados  II - semestre 2026/1

## Sobre o Projeto
O "Desafio na Cozinha" é um sistema inteligente desenvolvido em C para o gerenciamento de receitas e menus de um restaurante.

**Objetivo:** organizar o acervo culinário do restaurante, permitindo buscas eficientes, recomendações automáticas e otimização na escolha dos pratos.

## Fonte de Dados
 A base de dados utilizada foi obtida da API pública TheMealDB e salva localmente em um arquivo CSV, contendo 59 receitas.


  - **Extração de dados:** A API forneceu receitas com os campos *Id*, *Nome*, *Categoria*, *País*, *Ingredientes*, *Modo de preparo* e *URL*. 
  - **Geração de dados:** Os outros campos necessários para o trabalho como *Tempo de Preparo*, *Custo* e *Avaliação* foram adicionados de maneira aleatória na planilha.
  - **Adaptações:** No arquivo final foram removidos os campos Modo de Preparo e URL. Vírgulas foram substituídas por travessões para garantir que a função `strtok` da linguagem C pudesse separar as colunas corretamente durante a leitura do arquivo.

## Estruturas de Dados Implementadas
### 1. Tabela Hash

    Onde foi aplicada: No armazenamento das receitas, no Modo Investigação, e nas funções de Busca por Ingrediente e Busca por Categoria.

    Justificativa: Escolhida pela eficiência de tempo O(1) no acesso médio aos dados. O tratamento de colisões foi feito utilizando listas encadeadas. 

### 2. Árvore Trie

    Onde foi apliacada: Utilizada no Modo Consulta Rápida para buscar receitas por nome e prefixo.

    Justificativa: Escolhida por ser eficiente na busca por prefixos.

### 3. Algoritmo Guloso

    Onde foi aplicado: Utilizado no Modo Chef para recomendação de pratos (Menu Econômico e Menu Rápido).

    Justificativa: A abordagem gulosa resolve o problema da recomendação ao fazer a melhor escolha local possível. No Menu Econômico, é avaliado o custo benefício de cada prato, ou seja, avaliação/preço. No Menu Rápido, a escolha gulosa prioriza os pratos que levam o menor tempo de preparo.

## Funções do Sistema
### 1. Módulo 1 - Livro de Receitas

Carrega, armazena e lista as receitas disponíveis no sistema.

### 2. Módulo 2 - Busca Rápida
Localiza receitas por:
- ID
- Nome
- Categoria
- Prefixo

### 3. Módulo 3 - Organização de Ingredientes

Permite consultar uma receita a partir de um ingrediente específico.

### 4. Módulo 4 - Recomendação do Chef
Sugere receitas com base em restrições personalizadas, como custo, tempo de preparo, avaliação ou ingredientes.

### Modo Investigação 
Verifica a integridade dos dados e a existência de receitas corrompidas, detectando:
- Receitas alteradas desde sua inserção no sistema.
- Receitas inconsistentes (com valores numéricos inválidos).
- Receitas duplicadas.


