#include <stdio.h>

#define N 10
#define AGUA 0
#define NAVIO 3

/* Board helpers */
void inicializarTabuleiro(int tab[N][N]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            tab[i][j] = AGUA;
}

int podePosicionarHorizontal(int tab[N][N], int linha, int coluna, int comprimento) {
    // Verificar se cabe na horizontal
    if (coluna + comprimento > N) return 0;
    
    // Verificar se não há navio no caminho
    for (int j = coluna; j < coluna + comprimento; j++) {
        if (tab[linha][j] != AGUA) return 0;
    }
    return 1;
}

int podePosicionarVertical(int tab[N][N], int linha, int coluna, int comprimento) {
    // Verificar se cabe na vertical
    if (linha + comprimento > N) return 0;
    
    // Verificar se não há navio no caminho
    for (int i = linha; i < linha + comprimento; i++) {
        if (tab[i][coluna] != AGUA) return 0;
    }
    return 1;
}

void posicionarNavioHorizontal(int tab[N][N], int linha, int coluna, int comprimento) {
    for (int j = coluna; j < coluna + comprimento; j++) {
        tab[linha][j] = NAVIO;
    }
}

void posicionarNavioVertical(int tab[N][N], int linha, int coluna, int comprimento) {
    for (int i = linha; i < linha + comprimento; i++) {
        tab[i][coluna] = NAVIO;
    }
}

void imprimirTabuleiro(int tab[N][N]) {
    printf("   "); 
    for (int j = 0; j < N; j++) 
        printf("%2d ", j); 
    printf("\n");
    
    printf("   "); 
    for (int j = 0; j < N; j++) 
        printf("---");    
    printf("\n");
    
    for (int i = 0; i < N; i++) {
        printf("%2d|", i);
        for (int j = 0; j < N; j++) 
            printf("%2d ", tab[i][j]);
        printf("\n");
    }
}

int main(void) {
    int tabuleiro[N][N];

    inicializarTabuleiro(tabuleiro);
    
    // Navio 1: Horizontal na posição (2, 1)
    int linha_h = 2, coluna_h = 1;
    if (podePosicionarHorizontal(tabuleiro, linha_h, coluna_h, 3)) {
        posicionarNavioHorizontal(tabuleiro, linha_h, coluna_h, 3);
        printf("Navio horizontal posicionado em (%d,%d)\n", linha_h, coluna_h);
    } else {
        printf("ERRO: Não foi possível posicionar navio horizontal em (%d,%d)\n", linha_h, coluna_h);
    }
    
    // Navio 2: Vertical na posição (5, 6)
    int linha_v = 5, coluna_v = 6;
    if (podePosicionarVertical(tabuleiro, linha_v, coluna_v, 3)) {
        posicionarNavioVertical(tabuleiro, linha_v, coluna_v, 3);
        printf("Navio vertical posicionado em (%d,%d)\n", linha_v, coluna_v);
    } else {
        printf("ERRO: Não foi possível posicionar navio vertical em (%d,%d)\n", linha_v, coluna_v);
    }
    
    printf("\nTabuleiro Final:\n");
    printf("0 = Agua, 3 = Navio\n\n");
    imprimirTabuleiro(tabuleiro);
    
    return 0;
}