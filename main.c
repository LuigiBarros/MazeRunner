#include <stdio.h>
#include <stdlib.h>
#include "gconio.h"

#define LABIRINTOS 5
#define TAMANHO 10
#define MAXCANDIDATOS 4
//SETAS:
#define KEY_UP 119 // W
#define KEY_DOWN 115 // S
#define KEY_ENTER 13 // Enter
#define KEY_LEFT 97 // A
#define KEY_RIGHT 100 // D
#define KEY_ESC 27 // Esc

typedef struct linhaColuna{
    int linha;
    int coluna;
} LC;

int colunasIniciais[LABIRINTOS] = {1,1,2,1,3};
int labirintos[LABIRINTOS][TAMANHO][TAMANHO] = {
        { // Labirinto 0
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 1, 1, 1, 1, 1},
            {1, 1, 1, 1, 0, 1, 0, 0, 0, 1},
            {1, 1, 1, 1, 0, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 0, 0, 1, 1, 0, 1},
            {1, 1, 1, 0, 1, 0, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
            {1, 1, 0, 0, 1, 1, 0, 0, 0, 1},
            {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 1, 1, 1, 1}
        },
        { // Labirinto 1
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 0, 0, 0, 1, 1, 1, 1},
            {1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
            {1, 0, 1, 0, 1, 0, 0, 0, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 1, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 1, 1, 0, 1}
        },
        { // Labirinto 2
            {1, 1, 0, 1, 1, 1, 1, 1, 1, 1},
            {1, 1, 0, 1, 0, 0, 1, 0, 0, 1},
            {1, 0, 0, 1, 0, 1, 1, 0, 1, 1},
            {1, 0, 1, 1, 0, 1, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 1, 1, 1, 0, 1},
            {1, 0, 1, 0, 1, 1, 1, 0, 0, 1},
            {1, 0, 1, 0, 0, 0, 1, 0, 1, 1},
            {1, 0, 1, 1, 1, 0, 0, 0, 1, 1},
            {1, 0, 0, 0, 0, 0, 1, 1, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1, 1}
        },
        { // Labirinto 3
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 1, 1, 1, 1, 1, 1, 1, 1},
            {1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
            {1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
            {1, 1, 1, 0, 0, 0, 0, 0, 1, 1},
            {1, 1, 1, 1, 1, 0, 1, 1, 1, 1},
            {1, 0, 0, 0, 1, 0, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 0, 1},
            {1, 1, 1, 0, 0, 0, 0, 0, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 1, 1}
        },
        { // Labirinto 4
            {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
            {1, 1, 1, 0, 1, 1, 0, 0, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
            {1, 1, 1, 0, 1, 1, 0, 1, 0, 1},
            {1, 0, 0, 0, 0, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 0, 0, 1, 0, 1},
            {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
            {1, 1, 1, 1, 1, 1, 1, 1, 1, 0}
        }
    };

void backTracking(int labirinto, int linha, int coluna, int profundidade);
void construirCandidatos(int labirinto, int linha, int coluna, int *numeroCandidatos, LC *vetorCandidatos);
void loopMenu(int *labirinto);
int setaBasica(int seta, int controlador);
int setaFinal(int seta, int controlador);
void imprimirLabirinto(int labirinto, int linhaInicio, int linhaFim, int colunaInicio, int colunaFim) ;
void construirMoldura(int Inicio_Linha, int Fim_Linha, int Inicio_Coluna, int Fim_Coluna);
void nomeMazeRunner();

int main() {
    system("chcp 65001"); // Configuração do console para permitir caracteres especiais
    int labirinto, seta=1, controlador;

    do{
        textbackground(BLUE);
        textcolor(WHITE);
        construirMoldura(0, 25, 0, 90);
        nomeMazeRunner();
        loopMenu(&labirinto);
        backTracking(labirinto, 0, colunasIniciais[labirinto], 0);
        labirintos[labirinto][0][colunasIniciais[labirinto]] = 0;

        textbackground(BLUE);
        textcolor(WHITE);
        gotoxy(15,19); printf("Testar novamente.");
        gotoxy(15,20); printf("Sair.");
        do{
            gotoxy(14,19); printf(" ");
            gotoxy(14,20); printf(" ");
            if (seta == 1) gotoxy(14,19);
            if (seta == 2) gotoxy(14,20);
            printf(">");
            controlador = getch();
            seta = setaFinal(seta, controlador);
            if(seta == 1 && controlador == KEY_ENTER) break;
            if(seta == 2 && controlador == KEY_ENTER) seta = 0;
        }while(seta != 0);
    }while(seta != 0);
    return 0;
}

void backTracking(int labirinto, int linha, int coluna, int profundidade) {
    int numeroCandidatos = 0;
    LC vetorCandidatos[MAXCANDIDATOS];

    labirintos[labirinto][0][colunasIniciais[labirinto]] = 2;

    if (linha == TAMANHO - 1) {
        textbackground(BLUE);
        textcolor(WHITE);
        construirMoldura(0, 25, 0, 90);
        nomeMazeRunner();
        gotoxy(40, 11); printf("PRESS ENTER");
        imprimirLabirinto(labirinto, 13, 23, 35, 45);
        getch();
        return;
    } else {
        construirCandidatos(labirinto, linha, coluna, &numeroCandidatos, vetorCandidatos);

        for (int i = 0; i < numeroCandidatos; i++) {
            int novaLinha = linha + vetorCandidatos[i].linha;
            int novaColuna = coluna + vetorCandidatos[i].coluna;

            if (novaLinha >= 0 && novaLinha < TAMANHO && novaColuna >= 0 && novaColuna < TAMANHO) {
                labirintos[labirinto][novaLinha][novaColuna] = 2;
                backTracking(labirinto, novaLinha, novaColuna, profundidade + 1);
                labirintos[labirinto][novaLinha][novaColuna] = 0;
            }
        }
    }
}

void construirCandidatos(int labirinto, int linha, int coluna, int *numeroCandidatos, LC *vetorCandidatos) {
    int contador = 0;

    if (linha > 0 && labirintos[labirinto][linha - 1][coluna] == 0) {
        vetorCandidatos[contador].linha = -1;
        vetorCandidatos[contador].coluna = 0;
        contador++;
    }
    if (linha < TAMANHO - 1 && labirintos[labirinto][linha + 1][coluna] == 0) {
        vetorCandidatos[contador].linha = 1;
        vetorCandidatos[contador].coluna = 0;
        contador++;
    }
    if (coluna < TAMANHO - 1 && labirintos[labirinto][linha][coluna + 1] == 0) {
        vetorCandidatos[contador].linha = 0;
        vetorCandidatos[contador].coluna = 1;
        contador++;
    }
    if (coluna > 0 && labirintos[labirinto][linha][coluna - 1] == 0) {
        vetorCandidatos[contador].linha = 0;
        vetorCandidatos[contador].coluna = -1;
        contador++;
    }
    *numeroCandidatos = contador;
}

void loopMenu(int *labirinto){
    int seta = 1, controlador = 0;
    gotoxy(15,15); printf("Escolha uma das opções de Labirinto:");
    gotoxy(15,16); printf("Labirinto 1.");
    gotoxy(15,17); printf("Labirinto 2.");
    gotoxy(15,18); printf("Labirinto 3.");
    gotoxy(15,19); printf("Labirinto 4.");
    gotoxy(15,20); printf("Labirinto 5.");
    do {
        // Apaga o cursor no submenu
        gotoxy(14,16); printf(" ");
        gotoxy(14,17); printf(" ");
        gotoxy(14,18); printf(" ");
        gotoxy(14,19); printf(" ");
        gotoxy(14,20); printf(" ");

        // Exibe o cursor no submenu
        if (seta == 1) gotoxy(14,16);
        if (seta == 2) gotoxy(14,17);
        if (seta == 3) gotoxy(14,18);
        if (seta == 4) gotoxy(14,19);
        if (seta == 5) gotoxy(14,20);
        printf(">");
        imprimirLabirinto(seta-1, 13, 23, 60, 70);

        textbackground(BLUE);
        textcolor(WHITE);

        // Captura a tecla no submenu
        controlador = getch();

        if (controlador == KEY_ENTER) {  // Confirma seleção de labirinto
            *labirinto = seta-1;
        }
        seta = setaBasica(seta, controlador);
    } while (seta != 0);  // Fica no submenu até selecionar ou apertar ESC
}

int setaBasica(int seta, int controlador){
    if(controlador==KEY_UP){
            if(seta==1)
                seta=5;
            else if(seta==2)
                seta=1;
            else if(seta==3)
                seta=2;
            else if(seta==4)
                seta=3;
            else if(seta==5)
                seta=4;
    }else if(controlador==KEY_DOWN){
            if(seta==1)
                seta=2;
            else if(seta==2)
                seta=3;
            else if(seta==3)
                seta=4;
            else if(seta==4)
                seta=5;
            else if(seta==5)
                seta=1;
    }else if(controlador==KEY_ENTER){
        seta=0;
    }else if(controlador==KEY_ESC){
        seta=-1;
    }
    return seta;
}

int setaFinal(int seta, int controlador){
    if(controlador==KEY_UP){
            if(seta==1)
                seta=2;
            else if(seta==2)
                seta=1;
    }else if(controlador==KEY_DOWN){
            if(seta==1)
                seta=2;
            else if(seta==2)
                seta=1;
    }
    return seta;
}

void imprimirLabirinto(int labirinto, int linhaInicio, int linhaFim, int colunaInicio, int colunaFim) {
    textbackground(WHITE);
    textcolor(BLACK);
    construirMoldura(linhaInicio-1, linhaFim+1, (colunaInicio-1),(colunaFim+11));
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            if (labirintos[labirinto][i][j] == 0){
                textbackground(GREEN);
                gotoxy(colunaInicio+j*2,linhaInicio+i); printf("  ");
            }else if (labirintos[labirinto][i][j] == 1){
                textbackground(BLACK);
                gotoxy(colunaInicio+j*2,linhaInicio+i); printf("  ");
            }else{
                textbackground(YELLOW);
                gotoxy(colunaInicio+j*2,linhaInicio+i); printf("  ");
            }
        }
    }
}

void construirMoldura(int Inicio_Linha, int Fim_Linha, int Inicio_Coluna, int Fim_Coluna){
    for(int linha=Inicio_Linha;linha<Fim_Linha;linha++){ // For responsável pintar o fundo
            gotoxy(Inicio_Coluna, linha);
            for(int coluna=Inicio_Coluna; coluna<Fim_Coluna;coluna++)
                printf(" ");
            printf("\n");
        }
        // Trecho responsável por construir a moldura
        gotoxy(Inicio_Coluna,Inicio_Linha);
        printf("╔");
        for(int coluna=Inicio_Coluna+1;coluna<Fim_Coluna-1;coluna++)
            printf("═");
        printf("╗\n");

        for(int linha=Inicio_Linha+1;linha<Fim_Linha-1;linha++){
            gotoxy(Inicio_Coluna,linha);printf("║");
            gotoxy(Fim_Coluna-1,linha);printf("║");
        }

        gotoxy(Inicio_Coluna, Fim_Linha-1);
        printf("╚");
        for(int coluna=Inicio_Coluna+1;coluna<Fim_Coluna-1;coluna++)
            printf("═");
        printf("╝");
}

void nomeMazeRunner(){
    gotoxy(8, 4); printf(" __  __           ____________   _____  _    _ _   _ _   _ ______ _____  ");
    gotoxy(8, 5); printf("|  \\/  |   /\\    |___  /  ____| |  __ \\| |  | | \\ | | \\ | |  ____|  __ \\ ");
    gotoxy(8, 6); printf("| \\  / |  /  \\      / /| |__    | |__) | |  | |  \\| |  \\| | |__  | |__) |");
    gotoxy(8, 7); printf("| |\\/| | / /\\ \\    / / |  __|   |  _  /| |  | | . ` | . ` |  __| |  _  / ");
    gotoxy(8, 8);printf("| |  | |/ ____ \\  / /__| |____  | | \\ \\| |__| | |\\  | |\\  | |____| | \\ \\ ");
    gotoxy(8, 9);printf("|_|  |_/_/    \\_\\/_____|______| |_|  \\_\\_____/|_| \\_|_| \\_|______|_|  \\_\\");
}
