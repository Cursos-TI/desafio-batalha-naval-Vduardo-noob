#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define AGUA 0
#define NAVIO 3
#define TAMANHO_NAVIO 3

// Função para verificar se o navio cabe no tabuleiro (horizontal ou vertical)
int cabeNoTabuleiro(int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        return (coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    } else if (orientacao == 'V') {
        return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    }
    return 0;
}

// Função para verificar se o navio cabe na diagonal principal ou secundária
int cabeNaDiagonal(int linha, int coluna, char diagonal) {
    if (diagonal == 'P') { // Principal (linha++, coluna++)
        return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    } else if (diagonal == 'S') { // Secundária (linha++, coluna--)
        return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO && coluna - TAMANHO_NAVIO + 1 >= 0);
    }
    return 0;
}

// Verifica sobreposição em qualquer orientação
int haSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') {
            c += i;
        } else if (orientacao == 'V') {
            l += i;
        } else if (orientacao == 'P') {
            l += i;
            c += i;
        } else if (orientacao == 'S') {
            l += i;
            c -= i;
        }

        if (tabuleiro[l][c] != AGUA) return 1;
    }
    return 0;
}

// Posiciona o navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int l = linha, c = coluna;
        if (orientacao == 'H') {
            c += i;
        } else if (orientacao == 'V') {
            l += i;
        } else if (orientacao == 'P') {
            l += i;
            c += i;
        } else if (orientacao == 'S') {
            l += i;
            c -= i;
        }

        tabuleiro[l][c] = NAVIO;
    }
}

// Exibe o tabuleiro
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("\nTabuleiro:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializa o tabuleiro com água
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // NAVIO 1 - Horizontal
    int linhaH = 1, colunaH = 2;
    if (cabeNoTabuleiro(linhaH, colunaH, 'H') &&
        !haSobreposicao(tabuleiro, linhaH, colunaH, 'H')) {
        posicionarNavio(tabuleiro, linhaH, colunaH, 'H');
    } else {
        printf("Erro ao posicionar navio horizontal.\n");
        return 1;
    }

    // NAVIO 2 - Vertical
    int linhaV = 4, colunaV = 5;
    if (cabeNoTabuleiro(linhaV, colunaV, 'V') &&
        !haSobreposicao(tabuleiro, linhaV, colunaV, 'V')) {
        posicionarNavio(tabuleiro, linhaV, colunaV, 'V');
    } else {
        printf("Erro ao posicionar navio vertical.\n");
        return 1;
    }

    // NAVIO 3 - Diagonal Principal
    int linhaP = 6, colunaP = 1;
    if (cabeNaDiagonal(linhaP, colunaP, 'P') &&
        !haSobreposicao(tabuleiro, linhaP, colunaP, 'P')) {
        posicionarNavio(tabuleiro, linhaP, colunaP, 'P');
    } else {
        printf("Erro ao posicionar navio diagonal principal.\n");
        return 1;
    }

    // NAVIO 4 - Diagonal Secundária
    int linhaS = 0, colunaS = 9;
    if (cabeNaDiagonal(linhaS, colunaS, 'S') &&
        !haSobreposicao(tabuleiro, linhaS, colunaS, 'S')) {
        posicionarNavio(tabuleiro, linhaS, colunaS, 'S');
    } else {
        printf("Erro ao posicionar navio diagonal secundária.\n");
        return 1;
    }

    // Exibe o tabuleiro final
    exibirTabuleiro(tabuleiro);

    return 0;
}
