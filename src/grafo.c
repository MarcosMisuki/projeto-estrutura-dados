#include <stdio.h>
#include "grafo.h"

void grafo_inicializar(Grafo* g) {
    g->num_vertices = MAX_VERTICES;
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->matriz[i][j] = 0;
        }
    }
}

void grafo_adicionar_aresta(Grafo* g, int origem, int destino) {
    if (origem >= 0 && origem < MAX_VERTICES && destino >= 0 && destino < MAX_VERTICES) {
        g->matriz[origem][destino] = 1;
        g->matriz[destino][origem] = 1;
    }
}

void grafo_remover_aresta(Grafo* g, int origem, int destino) {
    if (origem >= 0 && origem < MAX_VERTICES && destino >= 0 && destino < MAX_VERTICES) {
        g->matriz[origem][destino] = 0;
        g->matriz[destino][origem] = 0;
    }
}

int grafo_existe_aresta(Grafo* g, int origem, int destino) {
    if (origem >= 0 && origem < MAX_VERTICES && destino >= 0 && destino < MAX_VERTICES) {
        return g->matriz[origem][destino];
    }
    return 0;
}

void grafo_bfs(Grafo* g, int inicio) {
    if (inicio < 0 || inicio >= MAX_VERTICES) {
        printf("[ERRO] ID fora do limite da rede.\n");
        return;
    }

    int visitados[MAX_VERTICES] = {0};
    int fila[MAX_VERTICES];
    int frente = 0, tras = 0;

    fila[tras++] = inicio;
    visitados[inicio] = 1;

    printf("\nEquipamentos alcancaveis a partir do ID %d: ", inicio);

    while (frente < tras) {
        int atual = fila[frente++];
        printf("%d ", atual);

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (g->matriz[atual][i] == 1 && !visitados[i]) {
                fila[tras++] = i;
                visitados[i] = 1;
            }
        }
    }
    printf("\n");
}

int grafo_existe_caminho(Grafo* g, int origem, int destino) {
    if (origem < 0 || origem >= MAX_VERTICES || destino < 0 || destino >= MAX_VERTICES) return 0;
    if (origem == destino) return 1;

    int visitados[MAX_VERTICES] = {0};
    int fila[MAX_VERTICES];
    int frente = 0, tras = 0;

    fila[tras++] = origem;
    visitados[origem] = 1;

    while (frente < tras) {
        int atual = fila[frente++];

        if (atual == destino) return 1;

        for (int i = 0; i < MAX_VERTICES; i++) {
            if (g->matriz[atual][i] == 1 && !visitados[i]) {
                fila[tras++] = i;
                visitados[i] = 1;
            }
        }
    }
    return 0;
}
