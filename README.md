# Sistema de Gerenciamento de Redes

Projeto prático desenvolvido para a disciplina de Estruturas de Dados (FATEC), com foco na aplicação de Árvores, Grafos e Pilhas em C.

## Estruturas Utilizadas
* **Árvore Binária de Busca (BST):** Cadastro, busca, remoção e ordenação de equipamentos de rede pelos seus IDs e Nomes.
* **Grafo (Matriz de Adjacência):** Mapeamento topológico das conexões (arestas) entre os equipamentos, verificação de rotas e Busca em Largura (BFS) para alcance de rede.
* **Pilha (Stack):** Registro do histórico de ações e operações realizadas pelo usuário durante a execução.

## Como Compilar e Executar
O projeto foi desenvolvido na IDE Code::Blocks utilizando o compilador GCC.
1. Abra o arquivo `sistema_dados.cbp` no Code::Blocks.
2. Pressione `F9` (Build and Run).
3. Utilize o menu interativo no terminal para navegar pelas 11 opções do sistema.

## Testes Realizados
Os testes de inserção, remoção, roteamento (caminho livre/inacessível) e ordenação (Bubble Sort) foram validados via terminal e estão documentados no Relatório Técnico em PDF.