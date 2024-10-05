# Projeto 1- Computação Embarcada

  ### Este projeto foi desenvolvido com o propósito de nos desafiar a aplicar na prática os conhecimentos adquiridos em teoria e nos laboratórios durante as aulas, integrando-os em uma única implementação. 
  
  Criamos um jogo com duas fases distintas. A primeira fase é um jogo da memória com dois LEDs, um vermelho e um verde. O programa exibe ao usuário uma sequência aleatória de luzes, e o jogador deve reproduzi-la corretamente usando botões. Ao acertar a sequência, o jogador avança para a segunda fase, que consiste em resolver questões matemáticas, variando de expressões simples a intermediárias, também de forma aleatória. O jogador começa essa fase com duas vidas, podendo perdê-las ao errar uma resposta ou esgotar o tempo. Se o jogador acertar pelo menos 9 das 10 questões, ele avança para a pergunta final, de maior dificuldade. Ao concluir todas as fases com sucesso, uma mensagem de vitória aparece, acompanhada por uma música de celebração.

  ### No desenvolvimento do nosso projeto, utilizamos os seguintes componentes: 
Uma placa Arduino Uno para controle e processamento, um LED vermelho e um LED verde para feedback visual, três botões para interação do usuário, três resistores para controle de corrente, um buzzer para sinalização sonora e um display LCD 16x2 para exibir informações e instruções durante o jogo.

  Iniciamos o projeto utilizando o Tinkercad, uma plataforma online que permite visualizar e simular o circuito sem a necessidade de montar o hardware fisicamente. 
  Após montarmos o circuito virtualmente, passamos para a implementação do código e desenvolvimento da lógica do jogo. Começamos declarando as variáveis e criando os arrays para armazenar as perguntas e respostas, além dos arrays para o jogo de memória. Em seguida, implementamos as funções relacionadas aos sons, como as de vitória, derrota e perda de tempo, bem como as funções de verificação de acertos e erros.  Depois disso, desenvolvemos as principais funções do projeto, incluindo a lógica do jogo da memória e o jogo das perguntas, garantindo que tudo funcionasse conforme o planejado. 
  Por fim, integramos todos os elementos no loop principal, que organiza e coordena as diferentes partes do jogo. Esse processo exigiu ajustes e refinamentos para garantir o funcionamento correto e eficiente do sistema.

  ### Segue abaixo o codigo completo do projeto:

  [projeto1](main.c)

  ### Segue abaixo o video do projeto funcionando:
  
  [cases_dentro_do_jogo_funcionando](https://youtu.be/TrhOZ5ztLOI)
  #### OBS: a parte do som no tinkercad não funciona, mas quando apresentamos na aula no fisico funcionou corretamente.

  ### A solução que adotamos para enfrentar os desafios propostos no projeto envolveu o uso de arrays para armazenar as sequências de LEDs, as respostas do usuário sobre a sequência, além de arrays separados para perguntas e respostas. Dessa forma, conseguimos comparar as respostas com base nos índices (para as perguntas) ou na quantidade (para as sequências de LEDs). 

Também utilizamos a função `random()` para tornar a ordem das sequências e das perguntas aleatória. No entanto, cometemos um deslize ao não utilizar `randomSeed()`, o que fez com que as sequências, embora aleatórias, seguissem um padrão repetitivo em cada execução do programa. Esse detalhe poderia ter sido evitado com o uso correto da semente para gerar uma aleatoriedade mais eficiente.

Essa abordagem facilitou o desenvolvimento e organização do projeto, porém, enfrentamos algumas dificuldades que servem como lições importantes para futuros projetos:

   **Atenção aos Detalhes:**
Ao trabalhar com hardware, pequenos detalhes podem causar grandes problemas. Um exemplo foi a declaração incorreta dos botões, onde um erro simples na atribuição dos pinos levou a diagnósticos incorretos sobre problemas no código. Aprendemos que verificar detalhadamente a configuração física é tão importante quanto a lógica do software.

   **Soluções de Design:**
Inicialmente, planejamos implementar um jogo com perguntas mais extensas, mas, por limitações do display LCD de 16x2, optamos por fazer perguntas matemáticas curtas. Somente após concluirmos o projeto percebemos que poderíamos ter pesquisado soluções mais criativas, como dividir as perguntas em partes ou usar rolagem de texto, o que teria permitido perguntas mais complexas sem comprometer a experiência do jogo.

Essas dificuldades nos mostraram a importância de uma abordagem mais cuidadosa tanto no planejamento quanto na implementação, além de reforçar a necessidade de explorar melhor as ferramentas disponíveis para superar limitações técnicas.
  

    
