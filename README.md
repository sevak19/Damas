# Simulação de Damas

# Descrição
Este projeto desenvolve uma simulação do jogo de damas, explorando diferentes dimensões de tabuleiro (8x8, 10x10 e 12x12) e adaptando regras simplificadas para o código. A simulação visa prever os possíveis desfechos de partidas reais, determinando o vencedor, o estado final do tabuleiro e o número de peças eliminadas de cada lado.

# Funcionamento
O código recebe como entrada o tipo de tabuleiro, as jogadas dos dois jogadores, e processa os movimentos conforme as regras específicas definidas. As peças são movimentadas em direções diagonais, com a captura sendo possível quando há um espaço vago após a peça adversária. O jogo termina quando todas as jogadas são executadas corretamente ou quando ocorre um movimento inválido, sendo exibido o estado final do tabuleiro e o vencedor.

# Exemplo de Entradas e Saídas

**Entrada 1:**

8 [(C3, D4), (D4, B6), (E3, D4), (D4, F6), (G3, F4), (H2, F4), (F4, E5), (E5, C3)]  
[(B6, C5), (C7, A5), (F6, E5), (G7, E5), (E5, G3), (D6, C5), (C5, D4), (E7, F6)]

**Saída 1:**

Tabuleiro Final:  
-x-x-x-x  
x-------  
-----x-x  
x-------  
--------  
o-o-----  
-o-o-o--  
o-o-o-o

Vencedor: Jogador 1  
Qt Capturada Jogador 1: 4  
Qt Capturada Jogador 2: 3

**Entrada 2:**

8 [(I6, H5), (B6, C5)]  
[(C3, D4), (D4, B6)]

**Saída 2:**

MOVIMENTO (I6, H5) INVÁLIDO, JOGO FINALIZADO

# Conclusão
Este projeto oferece uma simulação detalhada do jogo de damas, possibilitando a análise de diferentes cenários de partidas e ajudando a compreender a dinâmica e estratégias envolvidas. O código é ideal para estudos e aplicações que envolvem lógica de jogos de tabuleiro.
