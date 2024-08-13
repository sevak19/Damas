#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VAZIO '-'
#define PECA_BRANCA 'o'
#define DAMA_BRANCA 'O'
#define PECA_PRETA 'x'
#define DAMA_PRETA 'X'
#define MAX_MOVIMENTOS 100

typedef struct {
    char c1provisorio;
    int c1;
    int i1;
    char c2provisorio;
    int c2;
    int i2;
} Movimento;

void inicializaTabuleiro(char **tabuleiro, int tamanho);
void imprimeTabuleiro(char **tabuleiro, int tamanho);
void processaMovimentos(char *input, Movimento movimentos[], int *contador);
int movimentaPeca(char **tabuleiro, Movimento movimento, int jogador, int tamanho, int *quantCap);
int validaMovimento(char **tabuleiro, Movimento movimento, int jogador, int tamanho);
int eCaptura(char **tabuleiro, Movimento movimento, int jogador, int tamanho);

int main() {
    int tamanho;
    int quantCap1 = 0;
    int quantCap2 = 0;
    
    scanf("%d", &tamanho);
  
    while (getchar() != '\n');

    char **tabuleiro = malloc(tamanho * sizeof(char *));
    for (int i = 0; i < tamanho; i++) {
        tabuleiro[i] = malloc(tamanho * sizeof(char));
    }

    inicializaTabuleiro(tabuleiro, tamanho);

    char inputbrancas[1000];
    
    scanf("%999[^\n]", inputbrancas);

    Movimento movimentosBrancas[MAX_MOVIMENTOS];
    int contadorBrancas = 0;
    processaMovimentos(inputbrancas, movimentosBrancas, &contadorBrancas);

    char inputpretas[1000];
    
    scanf(" %[^\n]", inputpretas);

    Movimento movimentosPretas[MAX_MOVIMENTOS];
    int contadorPretas = 0;
    processaMovimentos(inputpretas, movimentosPretas, &contadorPretas);

    int contador;

    if (contadorPretas != contadorBrancas) {
        printf("O numero de movimentos passados aos dois jogadores deve ser sempre igual, jogada invalida.");
        return 0;
    } else {
        contador = contadorPretas;
    }

    for (int i = 0; i < contador; i++) {
        if (movimentaPeca(tabuleiro, movimentosBrancas[i], 1, tamanho, &quantCap1) == 0) {
            printf("MOVIMENTO (%c%i,%c%i) INVÁLIDO, JOGO FINALIZADO\n", movimentosBrancas[i].c1provisorio, movimentosBrancas[i].i1, movimentosBrancas[i].c2provisorio, movimentosBrancas[i].i2);
            return 0;
        }
        if (movimentaPeca(tabuleiro, movimentosPretas[i], 2, tamanho, &quantCap2) == 0) {
            printf("MOVIMENTO (%c%i,%c%i) INVÁLIDO, JOGO FINALIZADO\n", movimentosPretas[i].c1provisorio, movimentosPretas[i].i1, movimentosPretas[i].c2provisorio, movimentosPretas[i].i2);
            return 0;
        }
    }

    printf("\nTabuleiro Final:\n");
    imprimeTabuleiro(tabuleiro, tamanho);

    if(quantCap1 > quantCap2){
        printf("\nVencedor: Jogador 1");
    }else if(quantCap1 < quantCap2){
         printf("\nVencedor: Jogador 2");
    }else{
        printf("\nVencedor: Empate");
    }

    printf("\nQt Capturada Jogador 1: %i", quantCap1);
    printf("\nQt Capturada Jogador 2: %i", quantCap2);

    for (int i = 0; i < tamanho; i++) {
        free(tabuleiro[i]);
    }
    free(tabuleiro);

    return 0;
}

void inicializaTabuleiro(char **tabuleiro, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            if (i < (tamanho / 2 - 1) && (i + j) % 2 != 0) {
                tabuleiro[i][j] = PECA_PRETA;
            } else if (i > (tamanho / 2) && (i + j) % 2 != 0) {
                tabuleiro[i][j] = PECA_BRANCA;
            } else {
                tabuleiro[i][j] = VAZIO;
            }
        }
    }
}

void imprimeTabuleiro(char **tabuleiro, int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        for (int j = 0; j < tamanho; j++) {
            printf("%c", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

void processaMovimentos(char *input, Movimento movimentos[], int *contador) {
    *contador = 0;
    char *ptr = input;
    while (*ptr) {
        if (*ptr == '(') {
            sscanf(ptr, "(%c%i,%c%i)", &movimentos[*contador].c1provisorio, &movimentos[*contador].i1, &movimentos[*contador].c2provisorio, &movimentos[*contador].i2);
            (*contador)++;
        }
        ptr++;
    }
}

int movimentaPeca(char **tabuleiro, Movimento movimento, int jogador, int tamanho, int *quantCap) {
    char letras[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int seguranca = 0;
    for (int i = 0; i < tamanho; i++) {
        if (movimento.c1provisorio == letras[i]) {
            movimento.c1 = i;
            seguranca++;
        }
        if (movimento.c2provisorio == letras[i]) {
            movimento.c2 = i;
            seguranca++;
        }
    }
    if (seguranca != 2) {
        return 0;
    }
    if (validaMovimento(tabuleiro, movimento, jogador, tamanho)) {
        char peca = tabuleiro[tamanho+(movimento.i1*(-1))][movimento.c1];
        tabuleiro[tamanho+(movimento.i1*(-1))][movimento.c1] = VAZIO;
        tabuleiro[tamanho+(movimento.i2*(-1))][movimento.c2] = peca;

        if (eCaptura(tabuleiro, movimento, jogador, tamanho)) {
            int di = abs((tamanho+(movimento.i2*(-1))) - (tamanho+(movimento.i1*(-1))));
            int dc = abs(movimento.c2 - movimento.c1);
            if (peca == DAMA_BRANCA || peca == DAMA_PRETA) {
                int dirI = ((tamanho+(movimento.i2*(-1))) - (tamanho+(movimento.i1*(-1)))) / di;
                int dirC = (movimento.c2 - movimento.c1) / dc;
                for (int i = 1; i < di; i++) {
                    int capturadoI = (tamanho+(movimento.i1*(-1))) + dirI * i;
                    int capturadoC = movimento.c1 + dirC * i;
                    if (tabuleiro[capturadoI][capturadoC] != VAZIO) {
                        tabuleiro[capturadoI][capturadoC] = VAZIO;
                        (*quantCap)++;
                    }
                }
            } else {
                int capturadoI = ((tamanho+(movimento.i1*(-1))) + (tamanho+(movimento.i2*(-1)))) / 2;
                int capturadoC = (movimento.c1 + movimento.c2) / 2;
                tabuleiro[capturadoI][capturadoC] = VAZIO;
                (*quantCap)++;
            }
        }
        
        for (int j = 0; j < tamanho; j++) {
            if (tabuleiro[0][j] == PECA_BRANCA) {
                tabuleiro[0][j] = DAMA_BRANCA;
            }
            if (tabuleiro[tamanho-1][j] == PECA_PRETA) {
                tabuleiro[tamanho-1][j] = DAMA_PRETA;
            }
        }
        
        return 1;
    }

    return 0;
}

int validaMovimento(char **tabuleiro, Movimento movimento, int jogador, int tamanho) {
    if (movimento.i1 < 0 || movimento.i1 > tamanho || movimento.c1 < 0 || movimento.c1 >= tamanho ||
        movimento.i2 < 0 || movimento.i2 > tamanho || movimento.c2 < 0 || movimento.c2 >= tamanho) {
        return 0;
    }

    char peca = tabuleiro[tamanho+(movimento.i1*(-1))][movimento.c1];
    if ((jogador == 1 && (peca != PECA_BRANCA && peca != DAMA_BRANCA)) ||
        (jogador == 2 && (peca != PECA_PRETA && peca != DAMA_PRETA))) {
        return 0;
    }

    if (tabuleiro[tamanho+(movimento.i2*(-1))][movimento.c2] != VAZIO) {
        return 0;
    }

    int di = abs(movimento.i2 - movimento.i1);
    int dc = abs(movimento.c2 - movimento.c1);
    int dirI = ((tamanho+(movimento.i2*(-1))) - (tamanho+(movimento.i1*(-1)))) / di;
    int dirC = (movimento.c2 - movimento.c1) / dc;


    for (int i = 1; i < di; i++) {
        int capturadoI = (tamanho+(movimento.i1*(-1))) + dirI * i;
        int capturadoC = movimento.c1 + dirC * i;
        if(peca == DAMA_BRANCA && tabuleiro[capturadoI][capturadoC] == PECA_BRANCA){
            return 0;
        }else if(peca == DAMA_PRETA && tabuleiro[capturadoI][capturadoC] == PECA_PRETA){
            return 0;
        }
    }

    if (peca == PECA_BRANCA || peca == PECA_PRETA) {
        if (di < 1 || dc < 1 || di > 2 || dc > 2) {
            return 0;
        }
        for (int i = 1; i < di; i++) {
            int espacoI = (tamanho+(movimento.i1*(-1))) + dirI * i;
            int espacoC = movimento.c1 + dirC * i;
            char Espaco = tabuleiro[espacoI][espacoC];
            if(di==2 && Espaco == VAZIO){
                return 0;
            }
        }
    } else if (peca == DAMA_BRANCA || peca == DAMA_PRETA) {
        if (di != dc) {
            return 0;
        }
    }

    return 1;
}

int eCaptura(char **tabuleiro, Movimento movimento, int jogador, int tamanho) {
    int di = abs(movimento.i2 - movimento.i1);
    int dc = abs(movimento.c2 - movimento.c1);

    if (di == 2 && dc == 2) {
        int capturadoI = ((tamanho+(movimento.i1*(-1))) + (tamanho+(movimento.i2*(-1)))) / 2;
        int capturadoC = (movimento.c1 + movimento.c2) / 2;
        char pecaCapturada = tabuleiro[capturadoI][capturadoC];

        if ((jogador == 1 && (pecaCapturada == PECA_PRETA || pecaCapturada == DAMA_PRETA)) ||
            (jogador == 2 && (pecaCapturada == PECA_BRANCA || pecaCapturada == DAMA_BRANCA))) {
            return 1;
        }
    }else if (di > 2 && dc > 2) {
        int dirI = ((tamanho+(movimento.i2*(-1))) - (tamanho+(movimento.i1*(-1)))) / di;
        int dirC = (movimento.c2 - movimento.c1) / dc;
        for (int i = 1; i < di; i++) {
            int capturadoI = (tamanho+(movimento.i1*(-1))) + dirI * i;
            int capturadoC = movimento.c1 + dirC * i;
            char pecaCapturada = tabuleiro[capturadoI][capturadoC];
            if ((jogador == 1 && (pecaCapturada == PECA_PRETA || pecaCapturada == DAMA_PRETA)) ||
                (jogador == 2 && (pecaCapturada == PECA_BRANCA || pecaCapturada == DAMA_BRANCA))) {
                return 1;
            }
        }
    }

    return 0;
}
