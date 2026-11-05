#ifndef BST_H
#define BST_H

// Árvore guardando registros, mas o que é um registro, ela precisa saber
#include "dados.h"


typedef struct NoBST {
    Registro dados;
    struct NoBST* esq;
    struct NoBST* dir;
} NoBST;

//Existirá uma função para inserir
NoBST* bst_inserir(NoBST* raiz, Registro novo_registro, int* sucesso);
void bst_em_ordem(NoBST* raiz);
NoBST* bst_buscar(NoBST* raiz, int id);

#endif
