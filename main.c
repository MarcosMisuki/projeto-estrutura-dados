#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "bst.h"
#include "grafo.h"

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_texto(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') {
            buffer[len - 1] = '\0';
        } else {
            limpar_buffer();
        }
        return 1;
    }
    return 0;
}

int ler_inteiro(int *valor) {
    char buffer[50];
    if (ler_texto(buffer, sizeof(buffer))) {
        char *endptr;
        *valor = strtol(buffer, &endptr, 10);
        if (endptr != buffer && *endptr == '\0') {
            return 1;
        }
    }
    return 0;
}

int main() {
    int opcao = -1;
    NoBST* raiz = NULL; // Inicializa a nossa árvore vazia
    Grafo rede;         // Cria a estrutura da rede
    grafo_inicializar(&rede); // Zera todas as conexões

    while (opcao != 0) {
        printf("       SISTEMA DE ESTRUTURA DE DADOS\n");
        printf(" 1 - Cadastrar registro (cria vertice)\n");
        printf(" 2 - Buscar registro (BST)\n");
        printf(" 3 - Remover registro e vertice/arestas\n");
        printf(" 4 - Listar registros (BST em-ordem)\n");
        printf(" 5 - Ordenar e exibir registros por nome\n");
        printf(" 6 - Adicionar conexao (aresta)\n");
        printf(" 7 - Remover conexao (aresta)\n");
        printf(" 8 - Consultar conexao direta\n");
        printf(" 9 - Listar alcancaveis (BFS + lista)\n");
        printf("10 - Verificar caminho entre dois IDs\n");
        printf("11 - Consultar historico (pilha)\n");
        printf(" 0 - Encerrar\n");
        printf("============================================\n");
        printf("Escolha uma opcao: ");

        if (!ler_inteiro(&opcao)) {
            printf("\n[ERRO] Entrada invalida. Por favor, digite apenas numeros.\n");
            continue;
        }

        switch (opcao) {
            case 1: {
                Registro novo;
                int sucesso = 0;

                printf("\n--- CADASTRO DE EQUIPAMENTO ---\n");
                printf("Digite o ID (numero inteiro): ");
                while(!ler_inteiro(&novo.id)) {
                    printf("ID invalido. Digite apenas numeros: ");
                }

                printf("Digite o Nome do equipamento: ");
                ler_texto(novo.nome, 80);

                printf("Digite o Tipo (Ex: Roteador, Switch): ");
                ler_texto(novo.tipo_equipamento, 80);

                printf("Digite a Localizacao: ");
                ler_texto(novo.localizacao, 80);

                raiz = bst_inserir(raiz, novo, &sucesso);

                if (sucesso) {
                    printf("\n[SUCESSO] Equipamento ID %d cadastrado na Arvore!\n", novo.id);
                } else {
                    printf("\n[ERRO] O ID %d ja existe no sistema. Cadastro cancelado.\n", novo.id);
                }
                break;
            }
            case 2:
                printf("\n-> Funcao (Buscar registro) em desenvolvimento para as proximas etapas...\n");
                break;
            case 3:
                printf("\n-> Funcao (Remover registro) em desenvolvimento para as proximas etapas...\n");
                break;
            case 5:
                printf("\n-> Funcao (Ordenar registros) em desenvolvimento para as proximas etapas...\n");
                break;
            case 4:
                printf("\n--- LISTAGEM DE EQUIPAMENTOS (ORDEM DE ID) ---\n");
                if (raiz == NULL) {
                    printf("Nenhum equipamento cadastrado no sistema.\n");
                } else {
                    bst_em_ordem(raiz);
                }
                break;
            case 6: {
                int id1, id2;
                printf("\n--- ADICIONAR CONEXAO DE REDE ---\n");
                printf("Digite o ID do primeiro equipamento: ");
                ler_inteiro(&id1);
                printf("Digite o ID do segundo equipamento: ");
                ler_inteiro(&id2);

                grafo_adicionar_aresta(&rede, id1, id2);
                printf("\n[SUCESSO] Conexao criada entre %d e %d!\n", id1, id2);
                break;
            }
            case 7: {
                int id1, id2;
                printf("\n--- REMOVER CONEXAO DE REDE ---\n");
                printf("Digite o ID do primeiro equipamento: ");
                ler_inteiro(&id1);
                printf("Digite o ID do segundo equipamento: ");
                ler_inteiro(&id2);

                grafo_remover_aresta(&rede, id1, id2);
                printf("\n[SUCESSO] Conexao entre %d e %d removida!\n", id1, id2);
                break;
            }
            case 8: {
                int id1, id2;
                printf("\n--- CONSULTAR CONEXAO DIRETA ---\n");
                printf("Digite o ID do primeiro equipamento: ");
                ler_inteiro(&id1);
                printf("Digite o ID do segundo equipamento: ");
                ler_inteiro(&id2);

                if (grafo_existe_aresta(&rede, id1, id2)) {
                    printf("\n-> Status: CONECTADOS. Ha um cabo de rede entre %d e %d.\n", id1, id2);
                } else {
                    printf("\n-> Status: DESCONECTADOS. Nao ha ligacao direta entre %d e %d.\n", id1, id2);
                }
                break;
            }
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                if (opcao > 4 && opcao < 12) {
                    printf("\n-> Funcao em desenvolvimento nas proximas etapas...\n");
                } else {
                    printf("\n[ERRO] Opcao inexistente!\n");
                }
        }
    }
    return 0;
}
