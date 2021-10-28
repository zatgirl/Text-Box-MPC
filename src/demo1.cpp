//==================================================//
//    Multi-Platform Console (MPC) - v4.6.2 @ 2010  //
//     UFSM - Federal University of Santa Maria     //
//==================================================//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpc_c.h"
#include "demo1.h"
#include <vector>
#include <iostream>

//variaveis globais para controle do demo.
bool changed = true;
int ImgID[4], id = 0;
float alpha = 0;
int imgX = 0;
int direction = 1;
int horizontal_line = 50;

//posicoes mouse
int mouseX = 0;
int mouseY = 0;
int mouseOnPress = 0;

//posicoes relativas
int top = 50;
int bottom = 450;
int left = 50;
int right = 975;

//preenchimento
char janela_principal_linha[25];
char janela_principal_coluna[113];

char caixa1[103];
char box2a[103];
char box2b[103];
char box2c[103];
char box2d[103];
char box2e[103];
char box2f[103];
char box2g[103];
char box2h[103];
char box2i[103];

int enter, del = 0, home = 0, endi = 0, backspace = 0, press = 0;
int left_press = 0, up_press = 0, down_press = 0, right_press = 0;
int pos_linha = 0, pos_coluna = 0;

int k = 0, j = 0, keyPRESS, keytemp, quebra = 0, quebra2 = 0, linha = 1;

int box1 = 0, box2 = 0;

int selectedBox = 0;

void initMpc(void){

   mpcSetSize(APP_LINES, APP_COLUMNS);

   mpcSetMouseFunc(cbMouse);
   mpcSetUpdateFunc(cbUpdate);
   mpcSetKeyboardFunc(cbKeyboard);

   mpcSetCursorColor(RED_3);
   mpcSetCursorVisible(true);

   mpcAbout();

}

void displayApp(void){
    showBoxes();       //Caixas relativas a matriz principal
    //showBorders();     Deu errado, caixas dimensionadas por pixels
    preencheTela();    //Habilita a leitura de ambas as caixas
    showMouse();
    selectBox();       //Habilita a escrita na caixa selecionada
    //caixatexto1(1);
    //caixatexto2(1);

}

void showBorders(void){
    mpcHLine(top,left, right, RED_2, 1);
    mostraTexto(3,7, caixa1);

    mpcHLine(bottom,left,right, RED_2, 1);
    mpcVLine(left,top,bottom, RED_2, 1);
    mpcVLine(right,top,bottom, RED_2, 1);
    //caixa de texto 1 linha
    mpcHLine(top+50,left+50, right-50, RED_2, 1);
    mpcHLine(bottom-330,left+50,right-50, RED_2, 1);
    mpcVLine(left+50,top+50,bottom-330, RED_2, 1);
    mpcVLine(right-50,top+50,bottom-330, RED_2, 1);
    //caixa de texto multi linhas
    mpcHLine(top+100,left+50, right-50, RED_2, 1);
    mpcHLine(bottom-150,left+50,right-50, RED_2, 1);
    mpcVLine(left+50,top+100,bottom-150, RED_2, 1);
    mpcVLine(right-50,top+100,bottom-150, RED_2, 1);
    //botao 1
    mpcHLine(top+350,left+250, right-473, RED_2, 1);
    mpcHLine(bottom-10,left+250,right-473, RED_2, 1);
    mpcVLine(left+250,top+350,bottom-10, RED_2, 1);
    mpcVLine(right-473,top+350,bottom-10, RED_2, 1);
    //botao 2
    mpcHLine(top+350,left+472, right-251, RED_2, 1);
    mpcHLine(bottom-10,left+472,right-251, RED_2, 1);
    mpcVLine(left+472,top+350,bottom-10, RED_2, 1);
    mpcVLine(right-251,top+350,bottom-10, RED_2, 1);
}

//Indica onde está o cursor
void showMouse(){
   mpcSetCursorPos(pos_linha, pos_coluna);
}

//Criação gráfica das janelas/caixas de texto
void showBoxes(void){

   //janela principal fundo
   for (int x = 0; x < APP_COLUMNS; x++) {
      for (int y = 0; y < APP_LINES; y++) {
         mpcSetChar(y,               x, 10, F_STD, GREY_5, GREY_4, 1.0); //fundo
      }
   }
   //final janela principal

   //caixa de texto
   for (int x = 6; x < APP_COLUMNS-5; x++) {
      mpcSetChar(            3,               x, 9, F_STD, WHITE, ORANGE_2, 1.0); //cima
      mpcSetChar(APP_LINES - 5, APP_COLUMNS - x, 9, F_STD, WHITE, WHITE, 1.0); //baixo
          for (int y = 4; y < APP_LINES-5; y++) {
             mpcSetChar(y,               x, 10, F_STD, WHITE,  WHITE, 1.0); //fundo
             mpcSetChar(y,               6, 10, F_STD, WHITE,  WHITE, 1.0); //esq
             mpcSetChar(y, APP_COLUMNS - 6, 10, F_STD, WHITE,  WHITE, 1.0); //dir
          }
   }
   mpcSetChar(          3,             6, 11, F_STD, WHITE, ORANGE_2, 1.0);
   mpcSetChar(          3, APP_COLUMNS-6, 12, F_STD, WHITE, ORANGE_2, 1.0);
   mpcSetChar(APP_LINES-5,             6, 13, F_STD, WHITE, WHITE, 1.0);
   mpcSetChar(APP_LINES-5, APP_COLUMNS-6, 14, F_STD, WHITE, WHITE, 1.0);
   char texto[] = "Caixa de Texto";
   for(int cont = 0; cont < strlen(texto); cont++){
        mpcSetChar(3, 57+cont, texto[cont], F_IN, WHITE, ORANGE_2, 1 );
   }
   //final caixa de texto

   //início caixa de texto 1
   char texto2[] = "Caixa de Texto com 1 linha:";
   for(int cont = 0; cont < strlen(texto2); cont++){
        mpcSetChar(5, 12+cont, texto2[cont], F_N, BLACK, WHITE, 1 );
   }
   for (int x = 12; x < APP_COLUMNS - 12; x++) {
      mpcSetChar(             6,               x, 9, F_STD, BLACK, BLUE_2, 1.0); //cima
      mpcSetChar(APP_LINES - 27, APP_COLUMNS - x, 9, F_STD, BLACK, BLUE_2, 1.0); //baixo
          for (int y = 6; y < APP_LINES-27; y++) {
             mpcSetChar(7,                x, 10, F_STD, BLUE_2,  BLUE_2, 1.0); //fundo
             mpcSetChar(y,               12, 10, F_STD,  BLACK, BLUE_2, 1.0); //esq
             mpcSetChar(y, APP_COLUMNS - 12, 10, F_STD,  BLACK, BLUE_2, 1.0); //dir
          }
   }
   mpcSetChar(           6,             12, 11, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(           6, APP_COLUMNS-12, 12, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(APP_LINES-27,             12, 13, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(APP_LINES-27, APP_COLUMNS-12, 14, F_STD, BLACK, BLUE_2, 1.0);
   //final caixa de texto 1

   //inicio caixa de texto 2
   char texto3[] = "Caixa de Texto com várias linhas:";
   for(int cont = 0; cont < strlen(texto3); cont++){
        mpcSetChar(9, 12+cont, texto3[cont], F_N, BLACK, WHITE, 1 );
   }
   for (int x = 12; x < APP_COLUMNS - 12; x++) {
      mpcSetChar(            10,               x, 9, F_STD, BLACK, BLUE_2, 1.0); //cima
      //mpcSetChar(APP_LINES - 15, APP_COLUMNS - x, 9, F_STD, GREY_2, GREY_2, 1.0); //baixo
          for (int y = 10; y < APP_LINES-15; y++) {
             mpcSetChar(y+1,                x, 10, F_STD,  BLUE_2,  BLUE_2, 1.0); //fundo
             mpcSetChar(20, x, 9, F_STD, BLACK, BLUE_2, 1.0); //baixo
             mpcSetChar(y,               12, 10, F_STD, BLACK, BLUE_2, 1.0); //esq
             mpcSetChar(y, APP_COLUMNS - 12, 10, F_STD, BLACK, BLUE_2, 1.0); //dir
          }
   }
   mpcSetChar(          10,             12, 11, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(          10, APP_COLUMNS-12, 12, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(APP_LINES-15,             12, 13, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(APP_LINES-15, APP_COLUMNS-12, 14, F_STD, BLACK, BLUE_2, 1.0);
   //final caixa de texto 2

   //início primeiro botao
   for (int x = 37; x < APP_COLUMNS - 65; x++) {
      mpcSetChar(           25,                    x, 9, F_STD, BLACK, WHITE, 1.0); //cima
      mpcSetChar(APP_LINES - 7, APP_COLUMNS - x - 29, 9, F_STD, BLACK, WHITE, 1.0); //baixo
          for (int y = 26; y < APP_LINES-7; y++) {
             mpcSetChar(y,                x, 10, F_STD, WHITE, WHITE, 1.0); //fundo
             mpcSetChar(y,               37, 10, F_STD, BLACK, WHITE, 1.0); //esq
             mpcSetChar(y, APP_COLUMNS - 66, 10, F_STD, BLACK, WHITE, 1.0); //dir
          }
   }
   mpcSetChar(         25,             37, 11, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(         25, APP_COLUMNS-66, 12, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(APP_LINES-7,             37, 13, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(APP_LINES-7, APP_COLUMNS-66, 14, F_STD, BLACK, WHITE, 1.0);
   char texto4[] = ">       CANCELAR       <";
   for(int cont = 0; cont < strlen(texto4); cont++){
        mpcSetChar(27, 38+cont, texto4[cont], F_N, BLACK, WHITE, 1 );
   }
   //final primeiro botao

   //segundo botao
   for (int x = 65; x < APP_COLUMNS - 37; x++) {
      mpcSetChar(           25, x, 9, F_STD, BLACK, WHITE, 1.0); //cima
      mpcSetChar(APP_LINES - 7, x, 9, F_STD, BLACK, WHITE, 1.0); //baixo
          for (int y = 26; y < APP_LINES-7; y++) {
             mpcSetChar(y,                x, 10, F_STD, WHITE, WHITE, 1.0); //fundo
             mpcSetChar(y,               65, 10, F_STD, BLACK, WHITE, 1.0); //esq
             mpcSetChar(y, APP_COLUMNS - 38, 10, F_STD, BLACK, WHITE, 1.0); //dir
          }
   }
   mpcSetChar(         25,             65, 11, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(         25, APP_COLUMNS-38, 12, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(APP_LINES-7,             65, 13, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(APP_LINES-7, APP_COLUMNS-38, 14, F_STD, BLACK, WHITE, 1.0);
   char texto5[] = ">        ENVIAR        <";
   for(int cont = 0; cont < strlen(texto5); cont++){
        mpcSetChar(27, 66+cont, texto5[cont], F_N, BLACK, WHITE, 1 );
   }
   //final segundo botao
}

//Função habilitando a escrita na caixa selecionada
void selectBox (void){
    // se o mouse passar encima da caixa 1 e for clicado, a caixa 1 eh ativada
    if ((mouseY == 7) && ((mouseX > 12) && (mouseX < 115))){
        if(mouseOnPress == 1){
            selectedBox = 1;
        }
    }
    // se o mouse passar encima da caixa 2 e for clicado, a caixa 2 eh ativada
    if ((mouseY > 10) && (mouseY < 21) && ((mouseX > 12) && (mouseX < 115))){
        if(mouseOnPress == 1){
            selectedBox = 2;
        }
    }
    if(selectedBox == 1){
        caixatexto1(1);
    }
    if(selectedBox == 2){
        caixatexto2(1);
    }
}

//Funções relativas a caixa de uma linha
void caixatexto1(int write){
    if(write == 1 && k < 103){
     switch (keyPRESS) {
         case 97:
            caixa1[k] = 'a';
            k++;
            break;
         case 98:
            caixa1[k] = 'b';
            k++;
            break;
         case 99:
            caixa1[k] = 'c';
            k++;
            break;
         case 100:
            caixa1[k] = 'd';
            k++;
            break;
         case 101:
            caixa1[k] = 'e';
            k++;
            break;
         case 102:
            caixa1[k] = 'f';
            k++;
            break;
         case 103:
            caixa1[k] = 'g';
            k++;
            break;
         case 104:
            caixa1[k] = 'h';
            k++;
            break;
         case 105:
            caixa1[k] = 'i';
            k++;
            break;
         case 106:
            caixa1[k] = 'j';
            k++;
            break;
         case 107:
            caixa1[k] = 'k';
            k++;
            break;
         case 108:
            caixa1[k] = 'l';
            k++;
            break;
         case 109:
            caixa1[k] = 'm';
            k++;
            break;
         case 110:
            caixa1[k] = 'n';
            k++;
            break;
         case 111:
            caixa1[k] = 'o';
            k++;
            break;
         case 112:
            caixa1[k] = 'p';
            k++;
            break;
         case 113:
            caixa1[k] = 'q';
            k++;
            break;
         case 114:
            caixa1[k] = 'r';
            k++;
            break;
         case 115:
            caixa1[k] = 's';
            k++;
            break;
         case 116:
            caixa1[k] = 't';
            k++;
            break;
         case 117:
            caixa1[k] = 'u';
            k++;
            break;
         case 118:
            caixa1[k] = 'v';
            k++;
            break;
         case 119:
            caixa1[k] = 'w';
            k++;
            break;
         case 120:
            caixa1[k] = 'x';
            k++;
            break;
         case 121:
            caixa1[k] = 'y';
            k++;
            break;
         case 122:
            caixa1[k] = 'z';
            k++;
            break;
         case 32:
            caixa1[k] = ' ';
            k++;
            break;
        }
      }keyPRESS = 0;
      //mostraTexto(7,13,caixa1);
}

//Funções relativas a caixa de várias linhas com teclas especiais
void caixatexto2(int write){

    //Se a linha chegar ao final
    if(j == 103){
        quebra++;
        j = 0;
        linha++;
        printf("\nFinal da linha %d", quebra);
    }
    //Se for pressionado enter
    if(keyPRESS == 13){
        quebra2 += 1;
    }
    //Se for pressionado Home
    if(home == 1) {
        mpcSetCursorPos(11, 13);
        preencheLinha(keyPRESS);
        keyPRESS = 0;
    }
    if(home == 0){
        preencheLinha(keyPRESS);
        keyPRESS = 0;
    }
    if(endi == 1){
        preencheLinha(keyPRESS);
        keyPRESS = 0;
    }
    if(left_press == 1){
        pos_coluna -= 1;
        left_press = 0;
        mpcSetCursorPos(pos_linha, pos_coluna);
        preencheLinha(keyPRESS);
        keyPRESS = 0;
    }
    if(up_press == 1){
        mpcSetCursorPos(pos_linha - 1, pos_coluna);
        pos_linha = pos_linha - 1;
        preencheLinha(keyPRESS);
        keyPRESS = 0;
        up_press = 0;
    }
    if(down_press == 1){
        mpcSetCursorPos(pos_linha + 1, pos_coluna);
        pos_linha = pos_linha + 1;
        preencheLinha(keyPRESS);
        keyPRESS = 0;
        down_press = 0;
    }
    if(right_press == 1){
        mpcSetCursorPos(pos_linha, pos_coluna + 1);
        pos_coluna = pos_coluna + 1;
        preencheLinha(keyPRESS);
        keyPRESS = 0;
        right_press = 0;
    }
    //mostra os vetores
    /*mostraTexto(11, 13, box2a);
    mostraTexto(12, 13, box2b);
    mostraTexto(13, 13, box2c);
    mostraTexto(14, 13, box2d);
    mostraTexto(15, 13, box2e);
    mostraTexto(16, 13, box2f);
    mostraTexto(17, 13, box2g);
    mostraTexto(18, 13, box2h);
    mostraTexto(19, 13, box2i);*/

}

//Função que escreve na caixa de várias linhas, selecionada o vetor a ser escrito em caso de quebra de linha ou ENTER
void preencheLinha(int keypress){
        if((quebra2 == 1) && (linha != 13)) {
        //enter++;
        if(linha == 1){
            mostraTexto(12, 13, box2b);
            quebra2 = 0;
            linha++;
        }
        if(linha == 2){
            mostraTexto(13, 13, box2c);
            quebra2 = 0;
            linha++;
        }
        if(linha == 3){
            mostraTexto(14, 13, box2d);
            quebra2 = 0;
            linha++;
        }
        if(linha == 4){
            mostraTexto(15, 13, box2e);
            quebra2 = 0;
            linha++;
        }
        if(linha == 5){
            mostraTexto(16, 13, box2f);
            quebra2 = 0;
            linha++;
        }
        if(linha == 6){
            mostraTexto(17, 13, box2g);
            quebra2 = 0;
            linha++;
        }
        if(linha == 7){
            mostraTexto(18, 13, box2h);
            quebra2 = 0;
            linha++;
        }
        if(linha == 8){
            mostraTexto(19, 13, box2i);
            quebra2 = 0;
            linha++;
        }
    }
    if(linha == 1){
        switch (keypress) {
             case 97:
                box2a[j] = 'a';
                printf("\n %d", j);
                j++;
                break;
             case 98:
                box2a[j] = 'b';
                j++;
                break;
             case 99:
                box2a[j] = 'c';
                j++;
                break;
             case 100:
                box2a[j] = 'd';
                j++;
                break;
             case 101:
                box2a[j] = 'e';
                j++;
                break;
             case 102:
                box2a[j] = 'f';
                j++;
                break;
             case 103:
                box2a[j] = 'g';
                j++;
                break;
             case 104:
                box2a[j] = 'h';
                j++;
                break;
             case 105:
                box2a[j] = 'i';
                j++;
                break;
             case 106:
                box2a[j] = 'j';
                j++;
                break;
             case 107:
                box2a[j] = 'k';
                j++;
                break;
             case 108:
                box2a[j] = 'l';
                j++;
                break;
             case 109:
                box2a[j] = 'm';
                j++;
                break;
             case 110:
                box2a[j] = 'n';
                j++;
                break;
             case 111:
                box2a[j] = 'o';
                j++;
                break;
             case 112:
                box2a[j] = 'p';
                j++;
                break;
             case 113:
                box2a[j] = 'q';
                j++;
                break;
             case 114:
                box2a[j] = 'r';
                j++;
                break;
             case 115:
                box2a[j] = 's';
                j++;
                break;
             case 116:
                box2a[j] = 't';
                j++;
                break;
             case 117:
                box2a[j] = 'u';
                j++;
                break;
             case 118:
                box2a[j] = 'v';
                j++;
                break;
             case 119:
                box2a[j] = 'w';
                j++;
                break;
             case 120:
                box2a[j] = 'x';
                j++;
                break;
             case 121:
                box2a[j] = 'y';
                j++;
                break;
             case 122:
                box2a[j] = 'z';
                j++;
                break;
             case 32:
                box2a[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 2){
        switch (keypress) {
             case 97:
                box2b[j] = 'a';
                j++;
                break;
             case 98:
                box2b[j] = 'b';
                j++;
                break;
             case 99:
                box2b[j] = 'c';
                j++;
                break;
             case 100:
                box2b[j] = 'd';
                j++;
                break;
             case 101:
                box2b[j] = 'e';
                j++;
                break;
             case 102:
                box2b[j] = 'f';
                j++;
                break;
             case 103:
                box2b[j] = 'g';
                j++;
                break;
             case 104:
                box2b[j] = 'h';
                j++;
                break;
             case 105:
                box2b[j] = 'i';
                j++;
                break;
             case 106:
                box2b[j] = 'j';
                j++;
                break;
             case 107:
                box2b[j] = 'k';
                j++;
                break;
             case 108:
                box2b[j] = 'l';
                j++;
                break;
             case 109:
                box2b[j] = 'm';
                j++;
                break;
             case 110:
                box2b[j] = 'n';
                j++;
                break;
             case 111:
                box2b[j] = 'o';
                j++;
                break;
             case 112:
                box2b[j] = 'p';
                j++;
                break;
             case 113:
                box2b[j] = 'q';
                j++;
                break;
             case 114:
                box2b[j] = 'r';
                j++;
                break;
             case 115:
                box2b[j] = 's';
                j++;
                break;
             case 116:
                box2b[j] = 't';
                j++;
                break;
             case 117:
                box2b[j] = 'u';
                j++;
                break;
             case 118:
                box2b[j] = 'v';
                j++;
                break;
             case 119:
                box2b[j] = 'w';
                j++;
                break;
             case 120:
                box2b[j] = 'x';
                j++;
                break;
             case 121:
                box2b[j] = 'y';
                j++;
                break;
             case 122:
                box2b[j] = 'z';
                j++;
                break;
             case 32:
                box2b[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 3){
        switch (keypress) {
            case 97:
                box2c[j] = 'a';
                j++;
                break;
             case 98:
                box2c[j] = 'b';
                j++;
                break;
             case 99:
                box2c[j] = 'c';
                j++;
                break;
             case 100:
                box2c[j] = 'd';
                j++;
                break;
             case 101:
                box2c[j] = 'e';
                j++;
                break;
             case 102:
                box2c[j] = 'f';
                j++;
                break;
             case 103:
                box2c[j] = 'g';
                j++;
                break;
             case 104:
                box2c[j] = 'h';
                j++;
                break;
             case 105:
                box2c[j] = 'i';
                j++;
                break;
             case 106:
                box2c[j] = 'j';
                j++;
                break;
             case 107:
                box2c[j] = 'k';
                j++;
                break;
             case 108:
                box2c[j] = 'l';
                j++;
                break;
             case 109:
                box2c[j] = 'm';
                j++;
                break;
             case 110:
                box2c[j] = 'n';
                j++;
                break;
             case 111:
                box2c[j] = 'o';
                j++;
                break;
             case 112:
                box2c[j] = 'p';
                j++;
                break;
             case 113:
                box2c[j] = 'q';
                j++;
                break;
             case 114:
                box2c[j] = 'r';
                j++;
                break;
             case 115:
                box2c[j] = 's';
                j++;
                break;
             case 116:
                box2c[j] = 't';
                j++;
                break;
             case 117:
                box2c[j] = 'u';
                j++;
                break;
             case 118:
                box2c[j] = 'v';
                j++;
                break;
             case 119:
                box2c[j] = 'w';
                j++;
                break;
             case 120:
                box2c[j] = 'x';
                j++;
                break;
             case 121:
                box2c[j] = 'y';
                j++;
                break;
             case 122:
                box2c[j] = 'z';
                j++;
                break;
             case 32:
                box2c[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 4){
        switch (keypress) {
             case 97:
                //preencheLinha(linha, j, 'a');
                box2d[j] = 'a';
                j++;
                break;
             case 98:
                box2d[j] = 'b';
                j++;
                break;
             case 99:
                box2d[j] = 'c';
                j++;
                break;
             case 100:
                box2d[j] = 'd';
                j++;
                break;
             case 101:
                box2d[j] = 'e';
                j++;
                break;
             case 102:
                box2d[j] = 'f';
                j++;
                break;
             case 103:
                box2d[j] = 'g';
                j++;
                break;
             case 104:
                box2d[j] = 'h';
                j++;
                break;
             case 105:
                box2d[j] = 'i';
                j++;
                break;
             case 106:
                box2d[j] = 'j';
                j++;
                break;
             case 107:
                box2d[j] = 'k';
                j++;
                break;
             case 108:
                box2d[j] = 'l';
                j++;
                break;
             case 109:
                box2d[j] = 'm';
                j++;
                break;
             case 110:
                box2d[j] = 'n';
                j++;
                break;
             case 111:
                box2d[j] = 'o';
                j++;
                break;
             case 112:
                box2d[j] = 'p';
                j++;
                break;
             case 113:
                box2d[j] = 'q';
                j++;
                break;
             case 114:
                box2d[j] = 'r';
                j++;
                break;
             case 115:
                box2d[j] = 's';
                j++;
                break;
             case 116:
                box2d[j] = 't';
                j++;
                break;
             case 117:
                box2d[j] = 'u';
                j++;
                break;
             case 118:
                box2d[j] = 'v';
                j++;
                break;
             case 119:
                box2d[j] = 'w';
                j++;
                break;
             case 120:
                box2d[j] = 'x';
                j++;
                break;
             case 121:
                box2d[j] = 'y';
                j++;
                break;
             case 122:
                box2d[j] = 'z';
                j++;
                break;
             case 32:
                box2d[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 5){
        switch (keypress) {
             case 97:
                box2e[j] = 'a';
                j++;
                break;
             case 98:
                box2e[j] = 'b';
                j++;
                break;
             case 99:
                box2e[j] = 'c';
                j++;
                break;
             case 100:
                box2e[j] = 'd';
                j++;
                break;
             case 101:
                box2e[j] = 'e';
                j++;
                break;
             case 102:
                box2e[j] = 'f';
                j++;
                break;
             case 103:
                box2e[j] = 'g';
                j++;
                break;
             case 104:
                box2e[j] = 'h';
                j++;
                break;
             case 105:
                box2e[j] = 'i';
                j++;
                break;
             case 106:
                box2e[j] = 'j';
                j++;
                break;
             case 107:
                box2e[j] = 'k';
                j++;
                break;
             case 108:
                box2e[j] = 'l';
                j++;
                break;
             case 109:
                box2e[j] = 'm';
                j++;
                break;
             case 110:
                box2e[j] = 'n';
                j++;
                break;
             case 111:
                box2e[j] = 'o';
                j++;
                break;
             case 112:
                box2e[j] = 'p';
                j++;
                break;
             case 113:
                box2e[j] = 'q';
                j++;
                break;
             case 114:
                box2e[j] = 'r';
                j++;
                break;
             case 115:
                box2e[j] = 's';
                j++;
                break;
             case 116:
                box2e[j] = 't';
                j++;
                break;
             case 117:
                box2e[j] = 'u';
                j++;
                break;
             case 118:
                box2e[j] = 'v';
                j++;
                break;
             case 119:
                box2e[j] = 'w';
                j++;
                break;
             case 120:
                box2e[j] = 'x';
                j++;
                break;
             case 121:
                box2e[j] = 'y';
                j++;
                break;
             case 122:
                box2e[j] = 'z';
                j++;
                break;
             case 32:
                box2e[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 6){
        switch (keypress) {
             case 97:
                box2f[j] = 'a';
                j++;
                break;
             case 98:
                box2f[j] = 'b';
                j++;
                break;
             case 99:
                box2f[j] = 'c';
                j++;
                break;
             case 100:
                box2f[j] = 'd';
                j++;
                break;
             case 101:
                box2f[j] = 'e';
                j++;
                break;
             case 102:
                box2f[j] = 'f';
                j++;
                break;
             case 103:
                box2f[j] = 'g';
                j++;
                break;
             case 104:
                box2f[j] = 'h';
                j++;
                break;
             case 105:
                box2f[j] = 'i';
                j++;
                break;
             case 106:
                box2f[j] = 'j';
                j++;
                break;
             case 107:
                box2f[j] = 'k';
                j++;
                break;
             case 108:
                box2f[j] = 'l';
                j++;
                break;
             case 109:
                box2f[j] = 'm';
                j++;
                break;
             case 110:
                box2f[j] = 'n';
                j++;
                break;
             case 111:
                box2f[j] = 'o';
                j++;
                break;
             case 112:
                box2f[j] = 'p';
                j++;
                break;
             case 113:
                box2a[j] = 'q';
                j++;
                break;
             case 114:
                box2a[j] = 'r';
                j++;
                break;
             case 115:
                box2f[j] = 's';
                j++;
                break;
             case 116:
                box2f[j] = 't';
                j++;
                break;
             case 117:
                box2f[j] = 'u';
                j++;
                break;
             case 118:
                box2f[j] = 'v';
                j++;
                break;
             case 119:
                box2f[j] = 'w';
                j++;
                break;
             case 120:
                box2f[j] = 'x';
                j++;
                break;
             case 121:
                box2f[j] = 'y';
                j++;
                break;
             case 122:
                box2f[j] = 'z';
                j++;
                break;
             case 32:
                box2f[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 7){
        switch (keypress) {
             case 97:
                box2g[j] = 'a';
                j++;
                break;
             case 98:
                box2g[j] = 'b';
                j++;
                break;
             case 99:
                box2g[j] = 'c';
                j++;
                break;
             case 100:
                box2g[j] = 'd';
                j++;
                break;
             case 101:
                box2g[j] = 'e';
                j++;
                break;
             case 102:
                box2g[j] = 'f';
                j++;
                break;
             case 103:
                box2g[j] = 'g';
                j++;
                break;
             case 104:
                box2g[j] = 'h';
                j++;
                break;
             case 105:
                box2g[j] = 'i';
                j++;
                break;
             case 106:
                box2g[j] = 'j';
                j++;
                break;
             case 107:
                box2g[j] = 'k';
                j++;
                break;
             case 108:
                box2g[j] = 'l';
                j++;
                break;
             case 109:
                box2g[j] = 'm';
                j++;
                break;
             case 110:
                box2g[j] = 'n';
                j++;
                break;
             case 111:
                box2g[j] = 'o';
                j++;
                break;
             case 112:
                box2g[j] = 'p';
                j++;
                break;
             case 113:
                box2g[j] = 'q';
                j++;
                break;
             case 114:
                box2g[j] = 'r';
                j++;
                break;
             case 115:
                box2g[j] = 's';
                j++;
                break;
             case 116:
                box2g[j] = 't';
                j++;
                break;
             case 117:
                box2g[j] = 'u';
                j++;
                break;
             case 118:
                box2g[j] = 'v';
                j++;
                break;
             case 119:
                box2g[j] = 'w';
                j++;
                break;
             case 120:
                box2g[j] = 'x';
                j++;
                break;
             case 121:
                box2g[j] = 'y';
                j++;
                break;
             case 122:
                box2g[j] = 'z';
                j++;
                break;
             case 32:
                box2g[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 8){
        switch (keypress) {
             case 97:
                //preencheLinha(linha, j, 'a');
                box2h[j] = 'a';
                j++;
                break;
             case 98:
                box2h[j] = 'b';
                j++;
                break;
             case 99:
                box2h[j] = 'c';
                j++;
                break;
             case 100:
                box2h[j] = 'd';
                j++;
                break;
             case 101:
                box2h[j] = 'e';
                j++;
                break;
             case 102:
                box2h[j] = 'f';
                j++;
                break;
             case 103:
                box2h[j] = 'g';
                j++;
                break;
             case 104:
                box2h[j] = 'h';
                j++;
                break;
             case 105:
                box2h[j] = 'i';
                j++;
                break;
             case 106:
                box2h[j] = 'j';
                j++;
                break;
             case 107:
                box2h[j] = 'k';
                j++;
                break;
             case 108:
                box2h[j] = 'l';
                j++;
                break;
             case 109:
                box2h[j] = 'm';
                j++;
                break;
             case 110:
                box2h[j] = 'n';
                j++;
                break;
             case 111:
                box2h[j] = 'o';
                j++;
                break;
             case 112:
                box2h[j] = 'p';
                j++;
                break;
             case 113:
                box2h[j] = 'q';
                j++;
                break;
             case 114:
                box2h[j] = 'r';
                j++;
                break;
             case 115:
                box2h[j] = 's';
                j++;
                break;
             case 116:
                box2h[j] = 't';
                j++;
                break;
             case 117:
                box2h[j] = 'u';
                j++;
                break;
             case 118:
                box2h[j] = 'v';
                j++;
                break;
             case 119:
                box2h[j] = 'w';
                j++;
                break;
             case 120:
                box2h[j] = 'x';
                j++;
                break;
             case 121:
                box2h[j] = 'y';
                j++;
                break;
             case 122:
                box2h[j] = 'z';
                j++;
                break;
             case 32:
                box2h[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 9){
        switch (keypress) {
             case 97:
                //preencheLinha(linha, j, 'a');
                box2i[j] = 'a';
                j++;
                break;
             case 98:
                box2i[j] = 'b';
                j++;
                break;
             case 99:
                box2i[j] = 'c';
                j++;
                break;
             case 100:
                box2i[j] = 'd';
                j++;
                break;
             case 101:
                box2i[j] = 'e';
                j++;
                break;
             case 102:
                box2i[j] = 'f';
                j++;
                break;
             case 103:
                box2i[j] = 'g';
                j++;
                break;
             case 104:
                box2i[j] = 'h';
                j++;
                break;
             case 105:
                box2i[j] = 'i';
                j++;
                break;
             case 106:
                box2i[j] = 'j';
                j++;
                break;
             case 107:
                box2i[j] = 'k';
                j++;
                break;
             case 108:
                box2i[j] = 'l';
                j++;
                break;
             case 109:
                box2i[j] = 'm';
                j++;
                break;
             case 110:
                box2i[j] = 'n';
                j++;
                break;
             case 111:
                box2i[j] = 'o';
                j++;
                break;
             case 112:
                box2i[j] = 'p';
                j++;
                break;
             case 113:
                box2i[j] = 'q';
                j++;
                break;
             case 114:
                box2i[j] = 'r';
                j++;
                break;
             case 115:
                box2i[j] = 's';
                j++;
                break;
             case 116:
                box2i[j] = 't';
                j++;
                break;
             case 117:
                box2i[j] = 'u';
                j++;
                break;
             case 118:
                box2i[j] = 'v';
                j++;
                break;
             case 119:
                box2i[j] = 'w';
                j++;
                break;
             case 120:
                box2i[j] = 'x';
                j++;
                break;
             case 121:
                box2i[j] = 'y';
                j++;
                break;
             case 122:
                box2i[j] = 'z';
                j++;
                break;
             case 32:
                box2i[j] = ' ';
                j++;
                break;
        } keypress = 0;

        if(mouseOnPress == 0){
            mpcSetCursorPos(mouseY, mouseX);
        }
}
}

//Função habilitando a leitura em ambas as caixas
void preencheTela(){
    mostraTexto(7,13,caixa1);
    mostraTexto(11, 13, box2a);
    mostraTexto(12, 13, box2b);
    mostraTexto(13, 13, box2c);
    mostraTexto(14, 13, box2d);
    mostraTexto(15, 13, box2e);
    mostraTexto(16, 13, box2f);
    mostraTexto(17, 13, box2g);
    mostraTexto(18, 13, box2h);
    mostraTexto(19, 13, box2i);
   //char texto[] = "Caixa de Texto";
   //mostraTexto(6, 30, texto);
   //mostraTexto(3, 57, "Caixa de Texto");
   /*for(int cont = 0; cont < strlen(texto); cont++){
        mpcSetChar(3, 57+cont, texto[cont], F_IN, WHITE, ORANGE_2, 1 );
   }*/
}

//funcao para exibir strings na tela.
void mostraTexto(int l, int c, char *text){
   for (int cont = 0; cont < strlen(text); cont++){
      mpcSetChar(l, c+cont, text[cont], F_N, BLACK, BLUE_2, 1 );
      pos_linha = l;
      pos_coluna = c + j;
      //printf("\n [%d,%d]", pos_linha, pos_coluna);
      mpcSetCursorPos(l, c+cont+1);
   }
}

//*************************************************************
//callbacks implementation
//*************************************************************
void cbMouse(int lin, int col, int button, int state) {
   //printf("\n linha: %d coluna: %d button: %d state: %d",lin, col, button, state);
   mouseX = col;
   mouseY = lin;
   mouseOnPress = state;
   /*if(state == 0){
    mouseOnPress = 1;
   }*/
   changed = true;
}

void cbKeyboard(int key, int modifier, bool special, bool up) {
     //salva o valor de key apenas enquanto a tecla eh pressionada, e nao for especial
     if((up == 0) && special != 1){
        keyPRESS = key;
     }else keyPRESS = 0;
     //verifica se as teclas Home, End, Del e Backspace foram digitadas
     if((key == 106) && (special == 1) && (up == 0)){
        home++;
        //printf("\n %d", home);

     }
     if((key == 107) && (special == 1)){
        endi++;
     }
     if(key == 127){
        del++;
            //Se for pressionado End
            if(endi == 1) {
                mpcSetCursorPos(pos_linha, pos_coluna);
                if(pos_linha = 11){
                    mostraTexto(pos_linha, pos_coluna, box2a);
                }
                if(pos_linha = 12){
                    mostraTexto(pos_linha, pos_coluna, box2b);
                }
                if(pos_linha = 13){
                    mostraTexto(pos_linha, pos_coluna, box2c);
                }
                if(pos_linha = 14){
                    mostraTexto(pos_linha, pos_coluna, box2d);
                }
                if(pos_linha = 15){
                    mostraTexto(pos_linha, pos_coluna, box2e);
                }
                endi = 0;
            }
     }

     if(key == 8){
        backspace++;
     }
     //verifica se as setas direcionais foram digitadas
     if((key == 100) && (special == 1)){
        left_press++;
     }
     if((key == 101) && (special == 1)){
        up_press++;
     }
     if((key == 102) && (special == 1)){
        right_press++;
     }
     if((key == 103) && (special == 1)){
        down_press++;
     }
   /*if (special) {
      if (up) {
         //printf("SpecialKeyUp: %d    modifier: %d\n",key,modifier);
      } else {
         //printf("SpecialKey    %d    modifier: %d\n",key,modifier);
      }

   } else {
      if (up) {
         //printf("KeyUp: %d    modifier: %d\n",key,modifier);
      } else {
         //printf("Key    %d    modifier: %d\n",key,modifier);
      }

   }*/
   //changed = true;
   //printf("\n%d, %d, %d, %d", key, modifier, special, up);
}

void cbUpdate(void) {
   displayApp();
   /*if (changed) {
      displayApp();
      changed = false;
   }*/
}
