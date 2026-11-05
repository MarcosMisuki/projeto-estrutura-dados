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
