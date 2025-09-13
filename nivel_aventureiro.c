#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define AGUA 0
#define NAVIO 3

// Protótipos das funções
void inicializarTabuleiro(int tabuleiro[N][N]);
void exibirTabuleiro(int tabuleiro[N][N]);
int posicionarNavioHorizontal(int tabuleiro[N][N], int tamanho);
int posicionarNavioVertical(int tabuleiro[N][N], int tamanho);
int posicionarNavioDiagonal(int tabuleiro[N][N], int tamanho, int direcao);
int validarPosicaoDiagonal(int tabuleiro[N][N], int linha, int coluna, int tamanho, int direcao);

int main() {
    int tabuleiro[N][N];
    int naviosPosicionados = 0;
    
    srand(time(NULL));
    inicializarTabuleiro(tabuleiro);
    
    printf("🚀 NÍVEL AVENTUREIRO - BATALHA NAVAL\n");
    printf("📍 Posicionando 4 navios (2 tradicionais + 2 diagonais)...\n\n");
    
    // Navios tradicionais
    if (posicionarNavioHorizontal(tabuleiro, 3)) naviosPosicionados++;
    if (posicionarNavioVertical(tabuleiro, 3)) naviosPosicionados++;
    
    // Navios diagonais
    if (posicionarNavioDiagonal(tabuleiro, 3, 1)) naviosPosicionados++; // Diagonal principal
    if (posicionarNavioDiagonal(tabuleiro, 3, -1)) naviosPosicionados++; // Diagonal secundária
    
    printf("\n✅ Navios posicionados: %d/4\n", naviosPosicionados);
    exibirTabuleiro(tabuleiro);
    
    return 0;
}

void inicializarTabuleiro(int tabuleiro[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

void exibirTabuleiro(int tabuleiro[N][N]) {
    printf("   ");
    for (int j = 0; j < N; j++) {
        printf("%2d ", j);
    }
    printf("\n");
    
    for (int i = 0; i < N; i++) {
        printf("%2d ", i);
        for (int j = 0; j < N; j++) {
            printf("%2d ", tabuleiro[i][j]);
        }
        printf("\n");
    }
}

int posicionarNavioHorizontal(int tabuleiro[N][N], int tamanho) {
    int linha = rand() % N;
    int coluna = rand() % (N - tamanho + 1);
    
    // Verificar se a posição está livre
    for (int j = coluna; j < coluna + tamanho; j++) {
        if (tabuleiro[linha][j] != AGUA) {
            return 0; // Posição ocupada
        }
    }
    
    // Posicionar navio
    for (int j = coluna; j < coluna + tamanho; j++) {
        tabuleiro[linha][j] = NAVIO;
    }
    
    printf("📍 Navio horizontal posicionado em [%d][%d]-[%d][%d]\n", 
           linha, coluna, linha, coluna + tamanho - 1);
    return 1;
}

int posicionarNavioVertical(int tabuleiro[N][N], int tamanho) {
    int linha = rand() % (N - tamanho + 1);
    int coluna = rand() % N;
    
    // Verificar se a posição está livre
    for (int i = linha; i < linha + tamanho; i++) {
        if (tabuleiro[i][coluna] != AGUA) {
            return 0; // Posição ocupada
        }
    }
    
    // Posicionar navio
    for (int i = linha; i < linha + tamanho; i++) {
        tabuleiro[i][coluna] = NAVIO;
    }
    
    printf("📍 Navio vertical posicionado em [%d][%d]-[%d][%d]\n", 
           linha, coluna, linha + tamanho - 1, coluna);
    return 1;
}

int validarPosicaoDiagonal(int tabuleiro[N][N], int linha, int coluna, int tamanho, int direcao) {
    // direcao: 1 = diagonal principal, -1 = diagonal secundária
    
    if (direcao == 1) {
        // Verificar limites para diagonal principal (↘)
        if (linha + tamanho - 1 >= N || coluna + tamanho - 1 >= N) {
            return 0;
        }
        
        // Verificar se as posições estão livres
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna + i] != AGUA) {
                return 0;
            }
        }
    } else {
        // Verificar limites para diagonal secundária (↙)
        if (linha + tamanho - 1 >= N || coluna - tamanho + 1 < 0) {
            return 0;
        }
        
        // Verificar se as posições estão livres
        for (int i = 0; i < tamanho; i++) {
            if (tabuleiro[linha + i][coluna - i] != AGUA) {
                return 0;
            }
        }
    }
    
    return 1;
}

int posicionarNavioDiagonal(int tabuleiro[N][N], int tamanho, int direcao) {
    int tentativas = 0;
    int max_tentativas = 100;
    
    while (tentativas < max_tentativas) {
        int linha = rand() % N;
        int coluna = rand() % N;
        
        if (validarPosicaoDiagonal(tabuleiro, linha, coluna, tamanho, direcao)) {
            // Posicionar navio diagonal
            if (direcao == 1) {
                for (int i = 0; i < tamanho; i++) {
                    tabuleiro[linha + i][coluna + i] = NAVIO;
                }
                printf("📍 Navio diagonal principal posicionado em [%d][%d]-[%d][%d]\n", linha, coluna, linha + tamanho - 1, coluna + tamanho - 1);
            } else {
                for (int i = 0; i < tamanho; i++) {
                    tabuleiro[linha + i][coluna - i] = NAVIO;
                }
                printf("📍 Navio diagonal secundário posicionado em [%d][%d]-[%d][%d]\n", linha, coluna, linha + tamanho - 1, coluna - tamanho + 1);
            }
            return 1;
        }
        tentativas++;
    }
    
    printf("⚠️  Não foi possível posicionar navio diagonal após %d tentativas\n", max_tentativas);
    return 0;
}