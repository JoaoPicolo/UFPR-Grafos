#include "grafo.h"

map<string, int> mapaVertices;

void valida_entrada(int argc) {
    if (argc < 2) {
        cout << "Forneca o arquivo de entrada como argumento\n";
        exit(1);
    }
}


string limpa_vertice(string nome) {
    string novoNome;

    for (int i = 0; i < nome.size(); i++) {
        if (nome[i] != BRANCO_CHAR && nome[i] != TAB_CHAR && nome[i] != NOVA_LINHA_CHAR) {
            novoNome.push_back(nome[i]);
        }
    }

    return novoNome;
}


vector<string> processa_linha(char linha[]) {
    string inicial = linha;
    vector<string> vertices;

    char *ptr; 
    ptr = strtok(linha, BRANCO);

    while (ptr != NULL) {  
        string valor = string(ptr);
        if (valor != BRANCO && valor != TAB && valor != NOVA_LINHA) {
            vertices.push_back(limpa_vertice(valor));
        }        

        ptr = strtok(NULL, BRANCO);  
    }

    return vertices;
}


vertice_t cria_vertice(string nome) {
    vertice_t vertice;
    vertice.nome = nome;
    vertice.distancia = 0;
    vertice.estado = NAO_VISITADO;
    vertice.vizinhos = vector<int>();

    return vertice;
}


int verifica_vertice(vector<vertice_t> &vertices, string nome) {
    int verticeIdx;

    if (!mapaVertices.count(nome)) {
        verticeIdx = vertices.size();
        mapaVertices[nome] = verticeIdx;
        vertices.push_back(cria_vertice(nome));

        return verticeIdx;
    }
    else {
        return mapaVertices[nome];
    }
}


void atualiza_vertices(vector<vertice_t> &vertices, vector<string> novosVertices) {
    int tamanho = novosVertices.size();
    if (tamanho == 1) {
        verifica_vertice(vertices, novosVertices[0]);
    }
    else if (tamanho == 2) {
        int vertice1Idx = verifica_vertice(vertices, novosVertices[0]);  
        int vertice2Idx = verifica_vertice(vertices, novosVertices[1]);
        vertices[vertice1Idx].vizinhos.push_back(vertice2Idx);
        vertices[vertice2Idx].vizinhos.push_back(vertice1Idx);
    }
    else {
        cout << "Linha possui uma quantidade diferente de 1 ou 2 vértices\n";
        exit(1);   
    }
}


grafo_t le_grafo(FILE *arquivo) {
    char linha[TAM_LINHA];
    grafo_t grafo;

    while (fgets(linha, sizeof(linha), arquivo)) {
        if (linha[strlen(linha)-1] == NOVA_LINHA_CHAR) {
            linha[strlen(linha)-1] = LINHA_VAZIA_CHAR;
        }

        string linhaString = string(linha);
        if (linhaString != LINHA_VAZIA) {
            vector<string> vertices = processa_linha(linha);
            atualiza_vertices(grafo.vertices, vertices);
        }
    }

    return grafo;
}


grafo_t processa_input(char *nomeArquivo) {
    FILE *arquivo;
	arquivo = fopen(nomeArquivo, "r");

    grafo_t grafo;
	if (arquivo == NULL) {
        cout << "Nao foi possivel abrir o arquivo " << nomeArquivo << "\n";
        exit(1);
	}
    else {
        grafo = le_grafo(arquivo);
		fclose(arquivo); 
    }

    return grafo;
}


string le_vertice(void) {
    string nomeVertice;
    cout << "Insira o nome do vertice a ser procurado: ";
    cin >> nomeVertice;

    bool encontrou = (mapaVertices.count(nomeVertice) != 0);
    while (!encontrou) {
        cout << "Vertice nao encontrado. Insira um nome valido: ";
        cin >> nomeVertice;
        encontrou = (mapaVertices.count(nomeVertice) != 0);
    }

    return nomeVertice;
}


void busca_largura(vector<vertice_t> &vertices, int raizIdx) {
    queue<int> v;
    v.push(raizIdx);
    vertices[raizIdx].estado = PROCESSANDO;

    while (v.size() > 0) {
        int verticeAtualIdx = v.front();
        v.pop();

        int numeroVizinhos = vertices[verticeAtualIdx].vizinhos.size();
        for (int i = 0; i < numeroVizinhos; i++) {
            int vizinhoIdx = vertices[verticeAtualIdx].vizinhos[i];

            if (vertices[vizinhoIdx].estado == NAO_VISITADO) {
                vertices[vizinhoIdx].distancia = vertices[verticeAtualIdx].distancia + 1;

                v.push(vizinhoIdx);
                vertices[vizinhoIdx].estado = PROCESSANDO;
            }
        }

        vertices[verticeAtualIdx].estado = PROCESSADO;
    }
}


bool ehConexo(vector<vertice_t> &vertices) {
    int numeroVertices = vertices.size();
    int qtdeZeros = 0;
    for (int i = 0; i < numeroVertices; i++) {
        if (vertices[i].distancia == 0) {
            qtdeZeros++;
        }
    }

    // Somente a raiz tem distância zero em um grafo conexo
    return (qtdeZeros == 1);
}


double coeficiente_proximidade(grafo_t grafo, string nome) {
    vector<vertice_t> vertices = grafo.vertices;
    int numeroVertices = vertices.size();

    double soma = 0.0;
    for (int i = 0; i < numeroVertices; i++) {
        soma += vertices[i].distancia;
    }

    return (double(numeroVertices) / soma);
}


int destroi_grafo(grafo_t grafo) {
    mapaVertices.clear();

    return 1;
}


int main(int argc, char *argv[]) {
    valida_entrada(argc);
    grafo_t grafo = processa_input(argv[1]);

    int numeroVertices = grafo.vertices.size();
    if (numeroVertices == 0) {
        cout << "Erro ao processar o grafo\n";
        exit(1);
    }
    else {
        string verticeEntrada = le_vertice();

        int verticeEntradaIdx = mapaVertices[verticeEntrada];
        busca_largura(grafo.vertices, verticeEntradaIdx);

        if (ehConexo(grafo.vertices)) {
            double resultado = coeficiente_proximidade(grafo, verticeEntrada);
            cout << "Coeficiente de proximidade igual a " << resultado << "\n";
        }
        else {
            cout << "Grafo não é conexo. Coeficiente de proximida não pode ser calculado.\n";
        }
    }

    return !destroi_grafo(grafo);
}