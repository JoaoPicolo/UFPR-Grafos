#ifndef _GRAFO_H
#define _GRAFO_H

#include <map>
#include <queue>
#include <string>
#include <vector>
#include <iostream>
#include <cstring>

using namespace std;

#define TAM_LINHA 2100

#define BRANCO " "
#define TAB "\t"
#define NOVA_LINHA "\n"
#define LINHA_VAZIA "\0"

#define BRANCO_CHAR ' '
#define TAB_CHAR '\t'
#define NOVA_LINHA_CHAR '\n'
#define LINHA_VAZIA_CHAR '\0'

//------------------------------------------------------------------------------
// Estados possiveis de um vertice
enum Estados {
    NAO_VISITADO,
    PROCESSANDO,
    PROCESSADO,
};

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um vértice 
// o vértice tem um nome, que é uma "string"

typedef struct vertice_t{
    string nome;
    int distancia;
    Estados estado;
    vector<int> vizinhos;
} vertice_t;

//------------------------------------------------------------------------------
// (apontador para) estrutura de dados para representar um grafo
// o grafo tem um nome, que é uma "string"
typedef struct grafo_t{
    vector<vertice_t> vertices;
} grafo_t;

//------------------------------------------------------------------------------
// desaloca toda a memória usada em *g
// 
// devolve 1 em caso de sucesso,
//         ou 
//         0, caso contrário

int destroi_grafo(grafo_t grafo);

//------------------------------------------------------------------------------
// lê um grafo de input.
// um grafo é um arquivo onde cada linha tem zero, uma ou duas
// strings (sequência de caracteres sem "whitespace").
// 
// devolve o grafo lido. Caso o arquivo esteja mal formado o
// comportamento da função é indefinido
grafo_t le_grafo(FILE *arquivo);



//------------------------------------------------------------------------------
// pede para o usuário entrar com um vértice.
string le_vertice(void);  

//------------------------------------------------------------------------------
// escreve o grafo g em output, no mesmo formato que o usado por le_grafo()
//
// devolve o grafo escrito,
//         ou 
//         NULL, em caso de erro 


//------------------------------------------------------------------------------
// devolve o coeficiente de agrupamento de g
// ou seja, o número de tríades fechadas divido pelo 
// total de tríades (ou seja, a soma de tríades abertas e fechadas).
// 

double coeficiente_proximidade(grafo_t grafo, string nome);

//------------------------------------------------------------------------------
#endif
