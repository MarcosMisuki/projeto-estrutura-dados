#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

// Função interna para criar um novo nó na memória
NoBST* criar_no(Registro reg) {
    NoBST* novo = (NoBST*)malloc(sizeof(NoBST));
    if (novo != NULL) {
        novo->dados = reg;
        novo->esq = NULL;
        novo->dir = NULL;
    }
    return novo;
}

// Inserção recursiva na BST
NoBST* bst_inserir(NoBST* raiz, Registro novo_registro, int* sucesso) {
    // Se a árvore/subárvore estiver vazia, cria o nó aqui
    if (raiz == NULL) {
        *sucesso = 1;
        return criar_no(novo_registro);
    }

    // Regra de unicidade: IDs não podem se repetir
    if (novo_registro.id == raiz->dados.id) {
        *sucesso = 0; // Falha de ID já existente
    }
    // Se o ID novo for menor, desce para a esquerda
    else if (novo_registro.id < raiz->dados.id) {
        raiz->esq = bst_inserir(raiz->esq, novo_registro, sucesso);
    }
    // Se o ID novo for maior, desce para a direita
    else {
        raiz->dir = bst_inserir(raiz->dir, novo_registro, sucesso);
    }

    return raiz;
}

// Percurso Em-Ordem (Esquerda, Raiz, Direita) - lista os IDs em ordem crescente
void bst_em_ordem(NoBST* raiz) {
    if (raiz != NULL) {
        bst_em_ordem(raiz->esq);
        printf("ID: %d | Nome: %s | Tipo: %s | Local: %s\n",
               raiz->dados.id, raiz->dados.nome,
               raiz->dados.tipo_equipamento, raiz->dados.localizacao);
        bst_em_ordem(raiz->dir);
    }
}

// Busca recursiva
NoBST* bst_buscar(NoBST* raiz, int id) {
    // Se a árvore estiver vazia ou se achou o ID no nó atual
    if (raiz == NULL || raiz->dados.id == id) {
        return raiz;
    }

    // Se o ID procurado for menor, busca na subárvore esquerda
    if (id < raiz->dados.id) {
        return bst_buscar(raiz->esq, id);
    }

    // Caso contrário, busca na subárvore direita
    return bst_buscar(raiz->dir, id);
}

// Funcao auxiliar para achar o menor nó (usada na remocao)
NoBST* bst_minimo(NoBST* raiz) {
    NoBST* atual = raiz;
    while (atual && atual->esq != NULL) atual = atual->esq;
    return atual;
}

// Opcao 3: Remove da arvore
NoBST* bst_remover(NoBST* raiz, int id, int* sucesso) {
    if (raiz == NULL) return NULL;

    if (id < raiz->dados.id) {
        raiz->esq = bst_remover(raiz->esq, id, sucesso);
    } else if (id > raiz->dados.id) {
        raiz->dir = bst_remover(raiz->dir, id, sucesso);
    } else {
        *sucesso = 1;
        // Nó com 1 ou 0 filhos
        if (raiz->esq == NULL) {
            NoBST* temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            NoBST* temp = raiz->esq;
            free(raiz);
            return temp;
        }
        // Nó com 2 filhos
        NoBST* temp = bst_minimo(raiz->dir);
        raiz->dados = temp->dados;
        raiz->dir = bst_remover(raiz->dir, temp->dados.id, sucesso);
    }
    return raiz;
}

// Funcoes auxiliares para Opcao 5
void contar_nos(NoBST* raiz, int* cont) {
    if (raiz != NULL) {
        contar_nos(raiz->esq, cont);
        (*cont)++;
        contar_nos(raiz->dir, cont);
    }
}

void preencher_vetor(NoBST* raiz, Registro* vetor, int* i) {
    if (raiz != NULL) {
        preencher_vetor(raiz->esq, vetor, i);
        vetor[*i] = raiz->dados;
        (*i)++;
        preencher_vetor(raiz->dir, vetor, i);
    }
}

// Opcao 5: Joga a arvore num vetor, ordena e exibe
void bst_exibir_por_nome(NoBST* raiz) {
    if (raiz == NULL) {
        printf("\nNenhum equipamento cadastrado.\n");
        return;
    }

    int qtd = 0;
    contar_nos(raiz, &qtd);
    Registro* vetor = (Registro*)malloc(qtd * sizeof(Registro));
    int i = 0;
    preencher_vetor(raiz, vetor, &i);

    // Bubble Sort por nome
    for (int a = 0; a < qtd - 1; a++) {
        for (int b = 0; b < qtd - a - 1; b++) {
            if (strcmp(vetor[b].nome, vetor[b+1].nome) > 0) {
                Registro temp = vetor[b];
                vetor[b] = vetor[b+1];
                vetor[b+1] = temp;
            }
        }
    }

    printf("\n--- EQUIPAMENTOS ORDENADOS POR NOME ---\n");
    for (int a = 0; a < qtd; a++) {
        printf("Nome: %-15s | ID: %d | Tipo: %s\n", vetor[a].nome, vetor[a].id, vetor[a].tipo_equipamento);
    }
    free(vetor);
}

