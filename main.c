#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Função de validação segura de entrada (requisito 9)

//Função para limpar o lixo deixado no teclado
void limpar_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Le os textos com espaços e evita que estouros de limite quebrem o menu
int ler_texto(char *buffer, int tamanho){
    if (fgets(buffer, tamanho, stdin) != NULL){
        size_t len = strlen(buffer);
        //se último caractere for Enter (\n), substuimos por fim de string (\0)
        if (len > 0 && buffer[len-1] == '\n'){
            buffer[len-1]= '\0';
        }else{
        // Se não encontrou o \n, significa que o usuário digitou mais de 79 caracteres.
            // Precisamos descartar o excedente para não contaminar a próxima leitura.
            limpar_buffer();
        }
        return 1;
    }
    return 0;
}

// Le os números convertendo o texto, evitando loops infinitos se o usuário digitar letras
int ler_inteiro(int *valor) {
    char buffer[50];
    if (ler_texto(buffer, sizeof(buffer))) {
        char *endptr;
        // strtol é a forma recomendada e segura de converter string para int em C
        *valor = strtol(buffer, &endptr, 10);

        // Verifica se a conversão foi bem sucedida e se não sobraram letras no final
        if (endptr != buffer && *endptr == '\0') {
            return 1;
        }
    }
    return 0;
}

//Menu principal
int main() {
    int opcao = -1;

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
            printf("\n[ERRO] Entrada invalida. Por favor, digite apenas numeros.\n");
            continue; // Volta para o inicio do loop sem quebrar o programa
        }

        switch (opcao) {
            case 1:
                printf("\n-> Funcao: Cadastrar registro (Modulo BST e Grafo a conectar)\n");
                break;
            case 2:
                printf("\n-> Funcao: Buscar registro (Modulo BST a conectar)\n");
                break;
            case 3:
                printf("\n-> Funcao: Remover registro (Modulo BST e Grafo a conectar)\n");
                break;
            case 4:
                printf("\n-> Funcao: Listar em-ordem (Modulo BST a conectar)\n");
                break;
            case 5:
                printf("\n-> Funcao: Ordenar registros (Modulo de Ordenacao a conectar)\n");
                break;
            case 6:
                printf("\n-> Funcao: Adicionar conexao (Modulo Grafo a conectar)\n");
                break;
            case 7:
                printf("\n-> Funcao: Remover conexao (Modulo Grafo a conectar)\n");
                break;
            case 8:
                printf("\n-> Funcao: Consultar conexao (Modulo Grafo a conectar)\n");
                break;
            case 9:
                printf("\n-> Funcao: Listar alcancaveis (Modulo BFS a conectar)\n");
                break;
            case 10:
                printf("\n-> Funcao: Verificar caminho (Modulo Grafo a conectar)\n");
                break;
            case 11:
                printf("\n-> Funcao: Consultar historico (Modulo Pilha a conectar)\n");
                break;
            case 0:
                printf("\nEncerrando o sistema e liberando memoria alocada...\n");
                break;
            default:
                printf("\n[ERRO] Opcao inexistente! Escolha um numero entre 0 e 11.\n");
        }
    }

    return 0;
}
