#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dados.h"
#include "bst.h"
#include "grafo.h"

// ESTRUTURA DA PILHA (OPÇÃO 11 - HISTÓRICO)
#define MAX_HIST 100
typedef struct {
    char acoes[MAX_HIST][150];
    int topo;
} Pilha;

void pilha_inicializar(Pilha* p) { p->topo = -1; }

void pilha_empilhar(Pilha* p, const char* msg) {
    if (p->topo < MAX_HIST - 1) {
        p->topo++;
        strcpy(p->acoes[p->topo], msg);
    }
}

void pilha_mostrar(Pilha* p) {
    if (p->topo == -1) {
        printf("\nO historico de acoes esta vazio.\n");
        return;
    }
    printf("\n--- HISTORICO DE ACOES (Mais recentes no topo) ---\n");
    for (int i = p->topo; i >= 0; i--) {
        printf("[%02d] -> %s\n", p->topo - i + 1, p->acoes[i]);
    }
}
// ------------------------------------------------

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

int ler_texto(char *buffer, int tamanho) {
    if (fgets(buffer, tamanho, stdin) != NULL) {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len - 1] == '\n') buffer[len - 1] = '\0';
        else limpar_buffer();
        return 1;
    }
    return 0;
}

int ler_inteiro(int *valor) {
    char buffer[50];
    if (ler_texto(buffer, sizeof(buffer))) {
        char *endptr;
        *valor = strtol(buffer, &endptr, 10);
        if (endptr != buffer && *endptr == '\0') return 1;
    }
    return 0;
}

int main() {
    int opcao = -1;
    NoBST* raiz = NULL;
    Grafo rede;
    Pilha historico;

    grafo_inicializar(&rede);
    pilha_inicializar(&historico);

    char msg_temp[150]; // Usado para formatar as mensagens do historico

    while (opcao != 0) {
        printf("\n============================================\n");
        printf("       SISTEMA DE ESTRUTURA DE DADOS\n");
        printf("============================================\n");
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
            printf("\n[ERRO] Entrada invalida.\n");
            continue;
        }

        switch (opcao) {
            case 1: {
                Registro novo;
                int sucesso = 0;
                printf("\n--- CADASTRO ---\n");
                printf("ID (numero inteiro): ");
                while(!ler_inteiro(&novo.id)) printf("Apenas numeros: ");

                printf("Nome do equipamento: "); ler_texto(novo.nome, 80);
                printf("Tipo: "); ler_texto(novo.tipo_equipamento, 80);
                printf("Localizacao: "); ler_texto(novo.localizacao, 80);

                raiz = bst_inserir(raiz, novo, &sucesso);
                if (sucesso) {
                    printf("\n[SUCESSO] ID %d cadastrado!\n", novo.id);
                    sprintf(msg_temp, "Cadastrou o equipamento ID %d (%s)", novo.id, novo.nome);
                    pilha_empilhar(&historico, msg_temp);
                } else {
                    printf("\n[ERRO] ID %d ja existe.\n", novo.id);
                }
                break;
            }
            case 2: {
                int id_busca;
                printf("\nDigite o ID para buscar: ");
                ler_inteiro(&id_busca);
                NoBST* achado = bst_buscar(raiz, id_busca);
                if (achado) printf("\n[ENCONTRADO] Nome: %s | Local: %s\n", achado->dados.nome, achado->dados.localizacao);
                else printf("\n[AVISO] ID %d nao encontrado.\n", id_busca);
                break;
            }
            case 3: {
                int id_remover;
                int sucesso = 0;
                printf("\n--- REMOVER REGISTRO E VERTICE ---\n");
                printf("Digite o ID para excluir: ");
                ler_inteiro(&id_remover);

                raiz = bst_remover(raiz, id_remover, &sucesso);
                if (sucesso) {
                    // Apaga todas as conexoes do grafo relacionadas a esse ID
                    for (int i = 0; i < MAX_VERTICES; i++) {
                        grafo_remover_aresta(&rede, id_remover, i);
                    }
                    printf("\n[SUCESSO] ID %d removido da Arvore e da Rede!\n", id_remover);
                    sprintf(msg_temp, "Removeu o equipamento ID %d do sistema", id_remover);
                    pilha_empilhar(&historico, msg_temp);
                } else {
                    printf("\n[ERRO] ID %d nao encontrado.\n", id_remover);
                }
                break;
            }
            case 4:
                printf("\n--- LISTAGEM DE EQUIPAMENTOS (ORDEM DE ID) ---\n");
                if (raiz == NULL) printf("Nenhum equipamento cadastrado.\n");
                else bst_em_ordem(raiz);
                break;
            case 5:
                bst_exibir_por_nome(raiz);
                break;
            case 6: {
                int id1, id2;
                printf("\nConectar ID 1: "); ler_inteiro(&id1);
                printf("Conectar ID 2: "); ler_inteiro(&id2);
                grafo_adicionar_aresta(&rede, id1, id2);
                printf("\n[SUCESSO] Conexao criada entre %d e %d!\n", id1, id2);
                sprintf(msg_temp, "Criou uma conexao de rede entre os IDs %d e %d", id1, id2);
                pilha_empilhar(&historico, msg_temp);
                break;
            }
            case 7: {
                int id1, id2;
                printf("\nDesconectar ID 1: "); ler_inteiro(&id1);
                printf("Desconectar ID 2: "); ler_inteiro(&id2);
                grafo_remover_aresta(&rede, id1, id2);
                printf("\n[SUCESSO] Conexao entre %d e %d removida!\n", id1, id2);
                sprintf(msg_temp, "Removeu a conexao de rede entre os IDs %d e %d", id1, id2);
                pilha_empilhar(&historico, msg_temp);
                break;
            }
            case 8: {
                int id1, id2;
                printf("\nID 1: "); ler_inteiro(&id1);
                printf("ID 2: "); ler_inteiro(&id2);
                if (grafo_existe_aresta(&rede, id1, id2)) printf("\n-> CONECTADOS.\n");
                else printf("\n-> DESCONECTADOS.\n");
                break;
            }
            case 9: {
                int inicio;
                printf("\nID de inicio para BFS: "); ler_inteiro(&inicio);
                grafo_bfs(&rede, inicio);
                break;
            }
            case 10: {
                int id1, id2;
                printf("\nOrigem: "); ler_inteiro(&id1);
                printf("Destino: "); ler_inteiro(&id2);
                if (grafo_existe_caminho(&rede, id1, id2)) printf("\n-> CAMINHO LIVRE.\n");
                else printf("\n-> REDE INACESSIVEL.\n");
                break;
            }
            case 11:
                pilha_mostrar(&historico);
                break;
            case 0:
                printf("\nEncerrando o sistema...\n");
                break;
            default:
                printf("\n[ERRO] Opcao inexistente!\n");
        }
    }
    return 0;
}
