#ifndef GRAFO_H
#define GRAFO_H

#define MAX_VERTICES 100 // Limite de equipamentos na nossa matriz

typedef struct {
    int matriz[MAX_VERTICES][MAX_VERTICES];
    int num_vertices;
} Grafo;

void grafo_inicializar(Grafo* g);
void grafo_adicionar_aresta(Grafo* g, int origem, int destino);
void grafo_remover_aresta(Grafo* g, int origem, int destino);
int grafo_existe_aresta(Grafo* g, int origem, int destino);

#endif
