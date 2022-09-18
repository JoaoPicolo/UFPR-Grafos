Trabalho de Algoritmo e Teoria dos Grafos
Professor: Murilo da Silva

Alunos: João Picolo  -  GRR20182659
        Calebe Helpa -  GRR20190359

- Método de execução
   $ make
   $ ./grafo <arquivo de entrada.txt>
   $ Insira o nome do vertice a ser procurado: <vertice>

- Descrição
   Para a execução do programa basta compilá-lo antes com o comando make e então executar
   o programa 'grafo' com o arquivo de entrada como argumento. Por exemplo, suponha que o arquivo
   de entrada grafo.txt está localizado na pastas testes/, o programa deve ser executado da seguinte forma:

   $ make
   $ ./grafo testes/grafo.txt

   Inicialmente o programa irá validar a entrada e construir internamente a estrutura do grafo que foi
   passado como argumento, caso não haja erro na leitura o programa irá solicitar ao usuário que seja
   digitado o vértice sob o qual deverá ser calculado o coeficiente de proximidade. O programa só aceitará
   vértices válidos e não irá encerrar enquanto essa informação não for fornecida pelo usuário.

- Observações
   1. Com a permissão dada pelo professor, escolhemos por implementar este trabalho em C++;
   2. Para a execução do programa está sendo utilizado apenas o arquivo 'grafo.cpp', no qual se encontra a
      main, de forma que os arquivos entregues na versão final sejam apenas este README.TXT, grafo.cpp,
      grafo.h e makefile;
   3. Ainda com a permissão dada, o arquivo grafo.h foi alterado de forma a usar os tipos definidos
      pelo C++;
   4. A entrada do trabalho segue o seguinte formato, utilizando o espaço como separador:
      <vértice1> <vértice2>;
   5. O gerenciamento de memória é feito de forma automática pelo C++, sendo necessário apenas limpar
      as estruturas de dados utilizadas na função 'destroi_grafo()';
   6. Para o funcionamento correto do algoritmo o grafo passado deve ser conexo. Caso não seja, o grafo
      é lido porém o sistema envia uma mensagem de erro para o usuário ao final da execução.
   7. Não foi implementada a função de escrever o grafo presente no arquivo 'grafo.h' original fornecido pelo
      professor visto que o header desta função não havia sido definido nem no arquivo 'grafo.h' e nem no arquivo 'grafo.c'.

- Estruturas
   > Vértice
      A estrutura vertice_t possui os seguintes campos:
         string nome;
         int distancia;
         Estados estado;
         vector<int> vizinhos;
      
      nome         - Nome do vértice definido pelo arquivo de entrada;
      distancia    - Distância definida pela busca em largura do vértice atual à raiz;
      estado       - Estado no vértice durante a busca em largura, pode conter um dos seguintes valores:
                     NAO_VISITADO, PROCESSANDO, PROCESSADO;
      vizinhos     - Vetor que contém os índices dos vizinhos no vetor de vértices da estrutura grafo.

   > Grafo
      A estrutura grafo_t possui o seguinte campo:
         vector<vertice_t> vertices;

      vertices     - Vetor de estruturas vértice que armazena todos os vértices lidos do arquivo de entrada.

- Algoritmo
      1 - O arquivo passado como argumento é associado a um ponteiro do tipo FILE pela função fopen.
      Cada linha do arquivo representa uma aresta do grafo, cada aresta possui duas strings separadas por um 
      'whitespace' onde cada string representa um vértice da aresta. Pode-se ainda ter apenas uma string em uma linha
      do arquivo, mas isto pode indicar que o grafo não será conexo e isto ocorrerá caso o vértice atual não seja
      associado a nenhum outro no futuro.

      2 - Um laço de leitura é realizado até o final do arquivo passando por todas as linhas. Cada linha será
      carregada em um buffer. Para cada linha, cada vértice lido é atribuido a uma posição no vetor vertices 
      da estrutura grafo_t. É realizada uma verificação para identificar se todos os vértices do vetor vertices
      estão na estrutura grafo_t, caso não se encontrem os vértices são criados na estrutura. As arestas são
      atribuídas aos vértices adicionando o indíce do outro vértice da linha em seu vetor de vizinhos. 

      3 - O algoritmo então recebe da entrada padrão uma string que será o vértice raiz. Caso ele exista, o
      algoritmo segue para o próximo passo. Caso não exista, é enviada uma mensagem de erro e é solicitado
      que o usuário envie um nome de vértice existente.

      4 - O vertice raiz é inserido na fila de execução da busca em largura para determinar seu grau de centralidade.
      A busca em largura termina apenas quando a fila de execução se torna vazia, funcionando em loop para cada
      um de seus vértices. O loop é iniciado ao retirar o primeiro elemento da fila. Todos os vizinhos do vértice
      retirado serão processados. O estado de cada um dos vizinhos é verificado ao serem processados. Caso seja
      NAO_VISITADO, seu estado é modificado para PROCESSANDO, o campo pai do vizinho processado torna-se o vértice
      retirado da fila e o vizinho processado recebe como distância a distância do pai + 1. O vizinho processado é
      adicionado ao grafo ao final da fila de execução. Se o estado do vizinho processado for PROCESSANDO, este
      é ignorado. Finalizando o loop, o estado do vértice retirado da fila recebe PROCESSADO, indicando que todas
      as suas arestas foram processadas. O processo é repetido até que todos os vértices tenham como estado
      PROCESSADO.

      5 - Com a árvore gerada pela busca em largura, o número de vértices do grafo é dividido pela soma de todas
      as distâncias dos vértices até a raiz, essa é a medida de centralidade do vértice escolhido.

      6 - Por fim, a medida de centralidade obtida é impressa na tela.
