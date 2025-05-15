#include <stdio.h>

// Tamanho fixo do tabuleiro
#define TAMANHO_TABULEIRO 10

// Valor para representar água
#define AGUA 0

// Valor para representar partes dos navios
#define NAVIO 3

// Tamanho fixo dos navios
#define TAMANHO_NAVIO 3

// Função para verificar se o navio cabe no tabuleiro
int cabeNoTabuleiro(int linha, int coluna, char orientacao) {
    if (orientacao == 'H') {
        return (coluna + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    } else if (orientacao == 'V') {
        return (linha + TAMANHO_NAVIO <= TAMANHO_TABULEIRO);
    }
    return 0;
}

// Função para verificar se há sobreposição com outro navio
int haSobreposicao(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 'H') {
            if (tabuleiro[linha][coluna + i] != AGUA) return 1;
        } else if (orientacao == 'V') {
            if (tabuleiro[linha + i][coluna] != AGUA) return 1;
        }
    }
    return 0;
}

// Função para posicionar um navio no tabuleiro
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO], int linha, int coluna, char orientacao) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        if (orientacao == 'H') {
            tabuleiro[linha][coluna + i] = NAVIO;
        } else if (orientacao == 'V') {
            tabuleiro[linha + i][coluna] = NAVIO;
        }
    }
}

// Função para exibir o tabuleiro no console
void exibirTabuleiro(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO]) {
    printf("Tabuleiro:\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int main() {
    // Inicializa o tabuleiro com água (0)
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Coordenadas iniciais para o navio horizontal
    int linhaH = 2, colunaH = 4;

    // Coordenadas iniciais para o navio vertical
    int linhaV = 5, colunaV = 6;

    // Verifica se o navio horizontal pode ser posicionado
    if (cabeNoTabuleiro(linhaH, colunaH, 'H') &&
        !haSobreposicao(tabuleiro, linhaH, colunaH, 'H')) {
        posicionarNavio(tabuleiro, linhaH, colunaH, 'H');
    } else {
        printf("Erro: Não é possível posicionar o navio horizontal.\n");
        return 1;
    }

    // Verifica se o navio vertical pode ser posicionado
    if (cabeNoTabuleiro(linhaV, colunaV, 'V') &&
        !haSobreposicao(tabuleiro, linhaV, colunaV, 'V')) {
        posicionarNavio(tabuleiro, linhaV, colunaV, 'V');
    } else {
        printf("Erro: Não é possível posicionar o navio vertical.\n");
        return 1;
    }

    // Exibe o tabuleiro com os navios
    exibirTabuleiro(tabuleiro);

    return 0;
}
