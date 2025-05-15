#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_HABILIDADE 5
#define AGUA 0
#define NAVIO 3
#define HABILIDADE 5
#define TAMANHO_NAVIO 3

// Funções auxiliares para tabuleiro e navios (iguais às versões anteriores)
int cabeNoTabuleiro(int linha, int coluna, char orientacao) {
    if (orientacao == 'H') return (coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    if (orientacao == 'V') return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    return 0;
}

int cabeNaDiagonal(int linha, int coluna, char diagonal) {
    if (diagonal == 'P') return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    if (diagonal == 'S') return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna - TAMANHO_NAVIO + 1 >= 0);
    return 0;
}

int haSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'P') { l += i; c += i; }
        else if (orientacao == 'S') { l += i; c -= i; }

        if (tabuleiro[l][c] != AGUA) return 1;
    }
    return 0;
}

void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') c += i;
        else if (orientacao == 'V') l += i;
        else if (orientacao == 'P') { l += i; c += i; }
        else if (orientacao == 'S') { l += i; c -= i; }

        tabuleiro[l][c] = NAVIO;
    }
}

// Cria matriz de cone apontando para baixo
void criarCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= TAMANHO_HABILIDADE / 2 - i && j <= TAMANHO_HABILIDADE / 2 + i)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz em cruz
void criarCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == TAMANHO_HABILIDADE / 2 || j == TAMANHO_HABILIDADE / 2)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Cria matriz em forma de octaedro (losango)
void criarOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                matriz[i][j] = 1;
            else
                matriz[i][j] = 0;
        }
    }
}

// Sobrepõe a matriz de habilidade no tabuleiro com valor 5
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int offset = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            int l = origemLinha - offset + i;
            int c = origemColuna - offset + j;

            if (l >= 0 && l < TAMANHO_TABULEIRO && c >= 0 && c < TAMANHO_TABULEIRO) {
                if (habilidade[i][j] == 1 && tabuleiro[l][c] != NAVIO) {
                    tabuleiro[l][c] = HABILIDADE;
                }
            }
        }
    }
}

// Exibe o tabuleiro com legendas
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nLegenda: 0=Água  3=Navio  5=Habilidade\n\nTabuleiro:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Posiciona 4 navios
    if (cabeNoTabuleiro(1, 2, 'H') && !haSobreposicao(tabuleiro, 1, 2, 'H'))
        posicionarNavio(tabuleiro, 1, 2, 'H');
    if (cabeNoTabuleiro(4, 5, 'V') && !haSobreposicao(tabuleiro, 4, 5, 'V'))
        posicionarNavio(tabuleiro, 4, 5, 'V');
    if (cabeNaDiagonal(6, 1, 'P') && !haSobreposicao(tabuleiro, 6, 1, 'P'))
        posicionarNavio(tabuleiro, 6, 1, 'P');
    if (cabeNaDiagonal(0, 9, 'S') && !haSobreposicao(tabuleiro, 0, 9, 'S'))
        posicionarNavio(tabuleiro, 0, 9, 'S');

    // Criação das habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    criarCone(cone);
    criarCruz(cruz);
    criarOctaedro(octaedro);

    // Aplica habilidades no tabuleiro
    aplicarHabilidade(tabuleiro, cone, 2, 2);      // Cone no centro (2,2)
    aplicarHabilidade(tabuleiro, cruz, 5, 5);      // Cruz no centro (5,5)
    aplicarHabilidade(tabuleiro, octaedro, 7, 7);  // Octaedro no centro (7,7)

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
