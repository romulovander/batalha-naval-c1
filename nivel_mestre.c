#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 10
#define AGUA 0
#define NAVIO 3

// Protótipos das funções
void inicializarTabuleiro(int tabuleiro[N][N]);
void exibirTabuleiro(int tabuleiro[N][N]);
// Protótipos das habilidades especiais
int posicionarCone(int tabuleiro[N][N], int linha, int coluna);
int validarPosicaoCone(int tabuleiro[N][N], int linha, int coluna);

int main() {
    int tabuleiro[N][N];
    int conesPosicionados = 0;
    
    srand(time(NULL));
    inicializarTabuleiro(tabuleiro);
    
    printf("🏆 NÍVEL MESTRE - BATALHA NAVAL COM HABILIDADES ESPECIAIS\n");
    printf("📍 Testando posicionamento de Cone...\n\n");
    
    // Tentar posicionar 3 cones em posições aleatórias
    for (int i = 0; i < 10; i++) {
        int linha = rand() % N;
        int coluna = rand() % N;
        
        printf("Tentando posicionar cone em [%d][%d]\n", linha, coluna);
        
        if (posicionarCone(tabuleiro, linha, coluna)) {
            conesPosicionados++;
            if (conesPosicionados >= 3) break;
        }
    }
    
    printf("\n✅ Cones posicionados: %d/3\n", conesPosicionados);
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

// Função para validar posição do Cone
int validarPosicaoCone(int tabuleiro[N][N], int linha, int coluna) {
    // Verificar se o cone cabe no tabuleiro
    if (linha + 2 >= N || coluna - 1 < 0 || coluna + 1 >= N) {
        return 0; // Fora dos limites
    }
    
    // Verificar se todas as posições estão livres
    // Centro (ponta do cone)
    if (tabuleiro[linha][coluna] != AGUA) return 0;
    // Base do cone
    if (tabuleiro[linha + 1][coluna - 1] != AGUA) return 0;
    if (tabuleiro[linha + 1][coluna] != AGUA) return 0;
    if (tabuleiro[linha + 1][coluna + 1] != AGUA) return 0;
    if (tabuleiro[linha + 2][coluna] != AGUA) return 0;
    
    return 1; // Posição válida
}

// Função para posicionar Cone
int posicionarCone(int tabuleiro[N][N], int linha, int coluna) {
    if (validarPosicaoCone(tabuleiro, linha, coluna)) {
        // Posicionar o cone (formato ▲)
        tabuleiro[linha][coluna] = NAVIO;       // Ponta do cone
        tabuleiro[linha + 1][coluna - 1] = NAVIO; // Base esquerda
        tabuleiro[linha + 1][coluna] = NAVIO;     // Centro da base  
        tabuleiro[linha + 1][coluna + 1] = NAVIO; // Base direita
        tabuleiro[linha + 2][coluna] = NAVIO;     // Fundo do cone
        
        printf("🔷 Cone posicionado em [%d][%d] (formato ▲)\n", linha, coluna);
        return 1; // Sucesso
    }
    return 0; // Falha
}