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
// Protótipos da habilidade Cruz
int posicionarCruz(int tabuleiro[N][N], int linha, int coluna);
int validarPosicaoCruz(int tabuleiro[N][N], int linha, int coluna);
// Protótipos da habilidade Octaedro  
int posicionarOctaedro(int tabuleiro[N][N], int linha, int coluna);
int validarPosicaoOctaedro(int tabuleiro[N][N], int linha, int coluna);

int main() {

    int tabuleiro[N][N];
    int formasPosicionadas = 0;
    
    srand(time(NULL));
    inicializarTabuleiro(tabuleiro);
    
    printf("🏆 NÍVEL MESTRE - BATALHA NAVAL COM HABILIDADES ESPECIAIS\n");
    printf("📍 Testando Cone ▲, Cruz ✝️ e Octaedro 🔶...\n\n");
    
    // Tentar posicionar 1 de cada forma especial
    for (int i = 0; i < 30; i++) {
        int linha = rand() % N;
        int coluna = rand() % N;
        
        if (formasPosicionadas < 1 && posicionarCone(tabuleiro, linha, coluna)) {
            formasPosicionadas++;
        }
        else if (formasPosicionadas < 2 && posicionarCruz(tabuleiro, linha, coluna)) {
            formasPosicionadas++;
        }
        else if (formasPosicionadas < 3 && posicionarOctaedro(tabuleiro, linha, coluna)) {
            formasPosicionadas++;
        }
        
        if (formasPosicionadas >= 3) break;
    }
    
    printf("\n✅ Formas especiais posicionadas: %d/3\n", formasPosicionadas);
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
// Função para validar posição da Cruz
int validarPosicaoCruz(int tabuleiro[N][N], int linha, int coluna) {
    // Verificar se a cruz cabe no tabuleiro
    if (linha - 1 < 0 || linha + 1 >= N || coluna - 1 < 0 || coluna + 1 >= N) {
        return 0; // Fora dos limites
    }
    
    // Verificar se todas as posições estão livres
    if (tabuleiro[linha][coluna] != AGUA) return 0;     // Centro
    if (tabuleiro[linha - 1][coluna] != AGUA) return 0; // Norte
    if (tabuleiro[linha + 1][coluna] != AGUA) return 0; // Sul
    if (tabuleiro[linha][coluna - 1] != AGUA) return 0; // Oeste
    if (tabuleiro[linha][coluna + 1] != AGUA) return 0; // Leste
    
    return 1; // Posição válida
}

// Função para posicionar Cruz
int posicionarCruz(int tabuleiro[N][N], int linha, int coluna) {
    if (validarPosicaoCruz(tabuleiro, linha, coluna)) {
        // Posicionar a cruz (formato ✝)
        tabuleiro[linha][coluna] = NAVIO;       // Centro
        tabuleiro[linha - 1][coluna] = NAVIO;   // Norte
        tabuleiro[linha + 1][coluna] = NAVIO;   // Sul
        tabuleiro[linha][coluna - 1] = NAVIO;   // Oeste
        tabuleiro[linha][coluna + 1] = NAVIO;   // Leste
        
        printf("✝️  Cruz posicionada em [%d][%d] (formato +)\n", linha, coluna);
        return 1; // Sucesso
    }
    return 0; // Falha
}

// Função para validar posição do Octaedro
int validarPosicaoOctaedro(int tabuleiro[N][N], int linha, int coluna) {
    // Verificar se o octaedro cabe no tabuleiro (formato ◇)
    if (linha - 1 < 0 || linha + 1 >= N || coluna - 1 < 0 || coluna + 1 >= N) {
        return 0; // Fora dos limites
    }
    
    // Verificar se todas as posições estão livres
    if (tabuleiro[linha][coluna] != AGUA) return 0;         // Centro
    if (tabuleiro[linha - 1][coluna] != AGUA) return 0;     // Norte
    if (tabuleiro[linha + 1][coluna] != AGUA) return 0;     // Sul
    if (tabuleiro[linha][coluna - 1] != AGUA) return 0;     // Oeste
    if (tabuleiro[linha][coluna + 1] != AGUA) return 0;     // Leste
    if (tabuleiro[linha - 1][coluna - 1] != AGUA) return 0; // Noroeste
    if (tabuleiro[linha - 1][coluna + 1] != AGUA) return 0; // Nordeste
    if (tabuleiro[linha + 1][coluna - 1] != AGUA) return 0; // Sudoeste
    if (tabuleiro[linha + 1][coluna + 1] != AGUA) return 0; // Sudeste
    
    return 1; // Posição válida
}

// Função para posicionar Octaedro
int posicionarOctaedro(int tabuleiro[N][N], int linha, int coluna) {
    if (validarPosicaoOctaedro(tabuleiro, linha, coluna)) {
        // Posicionar o octaedro (formato ◇)
        tabuleiro[linha][coluna] = NAVIO;           // Centro
        tabuleiro[linha - 1][coluna] = NAVIO;       // Norte
        tabuleiro[linha + 1][coluna] = NAVIO;       // Sul
        tabuleiro[linha][coluna - 1] = NAVIO;       // Oeste
        tabuleiro[linha][coluna + 1] = NAVIO;       // Leste
        tabuleiro[linha - 1][coluna - 1] = NAVIO;   // Noroeste
        tabuleiro[linha - 1][coluna + 1] = NAVIO;   // Nordeste
        tabuleiro[linha + 1][coluna - 1] = NAVIO;   // Sudoeste
        tabuleiro[linha + 1][coluna + 1] = NAVIO;   // Sudeste
        
        printf("🔶 Octaedro posicionado em [%d][%d] (formato ◇)\n", linha, coluna);
        return 1; // Sucesso
    }
    return 0; // Falha
}

