#ifndef DADOS_H
#define DADOS_H

//Apenas para declarar o formato dos dados
// O #ifndef serve para impedir que esse código seja lido duas vezes por engano

typedef struct {
    int id;
    char nome[80];
    char tipo_equipamento[80];
    char localizacao[80];
} Registro;

#endif // DADOS_H
