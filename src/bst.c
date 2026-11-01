#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Aqui trazemos as funções de bst.h
#include "bst.h"

//Inserção
NoBST* bst_inserir(NoBST* raiz, Registro novo_registro, int* sucesso) {
    if (raiz == NULL) {
        // No caso de árvore vazia, ou chegamos na posição certa (uma folha)
        NoBST* novo = (NoBST*)malloc(sizeof(NoBST));
        if (novo == NULL){
            *sucesso =0; //aconteceu uma falha na alocação de memória
            return NULL;
        }

        novo->dados=novo_registro;
        novo->esq=NULL;
        novo->dir=NULL;
        *sucesso = 1;
        return novo;
    }

    if (novo_registro.id < raiz->dados.id) {
        //ID menor vai sempre a esquerda
        raiz->esq = bst_inserir(raiz->esq, novo_registro, sucesso);
    } else if (novo_registro.id > raiz->dados.id) {
        //ID Maior sempre vai para a direita
        raiz->dir =bst_inserir(raiz->dir, novo_registro, sucesso);
    } else {
        // ID já existe (NÃO PODE EXISTIR VALORES DUPLICADOS)
        *sucesso=0;
    }

    return raiz;
}
