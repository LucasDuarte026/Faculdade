# Harvard Processor

Nesse repositório apresenta as imagens de um sintese do que é o processador feito por Harvard.

O processador criado pela Universidade de Harvard, frequentemente referido no contexto da Arquitetura de Harvard, é um tipo de design de processador que se distingue principalmente pela forma como armazena e acessa instruções e dados.

### Separação entre Memória de Instruções e Memória de Dados: 
   Ao contrário da Arquitetura de von Neumann, onde uma única memória é compartilhada para instruções e dados, a Arquitetura de Harvard possui memórias separadas para instruções e dados. Isso significa que o processador tem barramentos e caminhos de acesso distintos para cada tipo de memória, o que pode aumentar a velocidade de processamento, pois instruções e dados podem ser acessados simultaneamente.

### Desempenho e Eficiência: 
Devido à separação das memórias, o processador pode ler uma instrução e acessar um dado ao mesmo tempo, o que potencialmente dobra a taxa de transferência de dados em comparação com a arquitetura de von Neumann. Isso é particularmente útil em aplicações que exigem grande largura de banda de memória ou em sistemas de processamento de sinais digitais (DSPs).

 ###   Segurança e Estabilidade: 
A separação também pode aumentar a segurança e a estabilidade do sistema, pois as instruções do programa não podem ser facilmente corrompidas por alterações nos dados.

###    Aplicações Específicas:
 Embora ofereça várias vantagens, a Arquitetura de Harvard é mais comumente encontrada em sistemas especializados, como DSPs e microcontroladores, onde a eficiência e a velocidade de processamento são críticas. Ela é menos comum em computadores de uso geral devido à complexidade e ao custo adicionais de implementar memórias separadas e barramentos.

 ### Evolução e Variações: 
  Com o tempo, surgiram variações dessa arquitetura, como a Arquitetura de Harvard Modificada, que permite algum nível de sobreposição ou compartilhamento entre as memórias de dados e instruções, tentando equilibrar os benefícios da Arquitetura de Harvard com a flexibilidade da Arquitetura de von Neumann.

Em resumo, a Arquitetura de Harvard é notável pela sua abordagem de separação de memória para instruções e dados, oferecendo vantagens em termos de velocidade e segurança, mas com algumas limitações em termos de flexibilidade e custo. É uma escolha popular em sistemas onde o desempenho de processamento é uma prioridade.