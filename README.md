# Desafio na Cozinha
Trabalho da disciplina de Algoritmos e Estrutura de Dados  II - semestre 2026/1

## Sobre o Projeto
O "Desafio na Cozinha" é um sistema inteligente desenvolvido em C para o gerenciamento de receitas e menus de um restaurante.

**Objetivo:** organizar o acervo culinário do restaurante, permitindo buscas eficientes, recomendações automáticas e otimização na escolha dos pratos.

## Fonte de Dados
 A base de dados utilizada foi obtida da API pública TheMealDB e salva localmente em um arquivo CSV, contendo 59 receitas.


  - **Extração de dados:** A API forneceu receitas com os campos *Id*, *Nome*, *Categoria*, *País*, *Ingredientes*, *Modo de preparo* e *URL*. 
  - **Geração de dados:** Os outros campos necessários para o trabalho como *Tempo de Preparo*, *Custo*, *Avaliação* e *Dependências* foram adicionados de maneira aleatória na planilha.
  - **Adaptações:** No arquivo final foram removidos os campos Modo de Preparo e URL. Vírgulas foram substituídas por travessões para garantir que a função `strtok` da linguagem C pudesse separar as colunas corretamente durante a leitura do arquivo.

## Estruturas de Dados Implementadas
### 1. Tabela Hash

    Onde foi aplicada: No armazenamento das receitas, no Modo Investigação e na função Busca por Categoria.

    Justificativa: Escolhida pela eficiência de tempo O(1) no acesso médio aos dados. O tratamento de colisões foi feito utilizando listas encadeadas. 

### 2. Árvore Trie

    Onde foi apliacada: Utilizada no Modo Consulta Rápida para buscar receitas por prefixo.

    Justificativa: Escolhida por ser eficiente na busca por prefixos.

### 3. Algoritmo Guloso

    Onde foi aplicado: Utilizado no Modo Chef para recomendação de pratos (Menu Econômico e Menu Rápido).

    Justificativa: A abordagem gulosa resolve o problema da recomendação ao fazer a melhor escolha local possível. No Menu Econômico, é avaliado o custo benefício de cada prato, ou seja, avaliação/preço. No Menu Rápido, a escolha gulosa prioriza os pratos que levam o menor tempo de preparo.

### 4. Grafos

    Onde foi aplicado: Módulo 5 (Oficina de Produção), Modo Investigação e Módulo 8 (Navegação de Emergência).

    Justificativa: Estrutura ideal para mapear relações. 
    A Busca em Profundidade (DFS) foi utilizada para rastrear a ordem de preparos e detectar ciclos (dependências inválidas). A Busca em Largura (BFS) foi aplicada em um mapa logístico para encontrar rotas mais curtas e seguras.

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

### 5. Módulo 5 - Oficina de Produção
Focado na logística da cozinha, permite verificar preparos anteriores (pré-requisitos de uma receita) e analisa a rede de dependências do cardápio.

### 6.  Modo Investigação 
Verifica a integridade dos dados e a existência de receitas corrompidas, detectando:
- Receitas alteradas desde sua inserção no sistema.
- Receitas inconsistentes (com valores numéricos inválidos).
- Receitas duplicadas.

Verifica inconsistências Operacionais: detecção de Ciclos.

### 7. Modo Logística

### 8. Menu Degustação VIP

### 9. Laboratório de Inovação do Chef
Apresenta soluções avançadas de algoritmos para a expansão do restaurante:
- **Navegação de Emergência:** Calcula rotas seguras entre regiões utilizando grafos e BFS.
- **Comunidades Gastronômicas:** Descobre e agrupa receitas semelhantes formando famílias culinárias (Union-Find).

## Como Executar
Requisitos:
 Compilador GCC instalado.

 Abra o terminal na pasta `src`.

 Compile os arquivos com o comando:
 
    gcc main.c hash.c trie.c ingredientes.c chef.c -o sistema

Execute o programa:

    Windows: .\sistema.exe
    Linux: ./sistema
