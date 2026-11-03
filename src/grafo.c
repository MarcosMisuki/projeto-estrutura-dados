#include <stdio.h>
#include "grafo.h"

// Preenche a matriz com zeros (nenhuma conexão inicial)
void grafo_inicializar(Grafo* g) {
    g->num_vertices = MAX_VERTICES;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

// Cria uma ligação bidirecional entre dois IDs
void grafo_adicionar_aresta(Grafo* g, int origem, int destino) {
    if (origem >= 0 && origem < MAX_VERTICES && destino >= 0 && destino < MAX_VERTICES) {
        g->matriz[origem][destino] = 1;
        g->matriz[destino][origem] = 1;
    }
}

// Desfaz a ligação entre dois IDs
void grafo_remover_aresta(Grafo* g, int origem, int destino) {
    if (origem >= 0 && origem < MAX_VERTICES && destino >= 0 && destino < MAX_VERTICES) {
        g->matriz[origem][destino] = 0;
        g->matriz[destino][origem] = 0;
    }
}

// Verifica se dois IDs estão ligados diretamente
int grafo_existe_aresta(Grafo* g, int origem, int destino) {
    if (origem >= 0 && origem < MAX_VERTICES && destino >= 0 && destino < MAX_VERTICES) {
        return g->matriz[origem][destino];
    }
    return 0;
}
