## Objetivo
Este trabalho consiste na construção e utilização de estrutura hierárquica denominada trie (do inglês "retrieval", sendo também conhecida como árvore de prefixos ou ainda árvore digital) para a indexação e recuperação eficiente de palavras em grandes arquivos de dicionários (mantidos em memória secundária). A implementação deverá resolver dois problemas listados a seguir.

### Primeiro problema: identificação de prefixos
Construir a trie, em memória principal, a partir das palavras (definidas entre colchetes) de um arquivo de dicionário, conforme o exemplo acima. A partir deste ponto, a aplicação deverá receber uma série de palavras quaisquer (pertencentes ou não ao dicionário) e responder se trata de um prefixo (a mensagem **P is prefix of N words** deve ser produzida, onde P é o nome da palavra e N é a quantidade de palavras) ou não (a mensagem **P is not prefix** deve ser produzida na saída padrão).

### Segundo problema: indexação de arquivo de dicionário
A construção da trie deve considerar a localização da palavra no arquivo e o tamanho da linha que a define. Para isto, ao criar o nó correspondente ao último caracter da palavra, deve-se atribuir a posição do caracter inicial (incluindo o abre-colchetes **[**), seguida pelo comprimento da linha (não inclui o caracter de mudança de linha) na qual esta palavra foi definida no arquivo de dicionário. Caso a palavra recebida pela aplicação exista no dicionário, estes dois inteiros devem ser determinados. Importante: uma palavra existente no dicionário também pode ser prefixo de outra; neste caso, o caracter final da palavra será encontrado em um nó não-folha da trie e duas linhas deverão ser produzidas na saída padrão, a mensagem **P is prefix of N words** na primeira linha, e **P is in (D,C)** na linha seguinte (sendo D a posição, e C o comprimento).

### Exemplo

- Entrada:

dicionario1.dic bear bell bid bu bull buy but sell stock stop 0

- Saída:

bear is prefix of 1 words  
bear is at (0,149)  
bell is prefix of 1 words  
bell is at (150,122)  
bid is prefix of 1 words  
bid is at (273,82)  
bu is prefix of 2 words  
bull is prefix of 1 words  
bull is at (356,113)  
buy is prefix of 1 words  
buy is at (470,67)  
but is not prefix  
sell is prefix of 1 words  
sell is at (538,97)  
stock is prefix of 1 words  
stock is at (636,79)  
stop is prefix of 1 words  
stop is at (716,92)  
