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
/*char line->lineY[25];
char [113];*/

int pos_linha = 0, pos_coluna = 0;

int k = 0, j = 0, keyPRESS, keytemp, quebra = 0, quebra2 = 0, linha = 1;

int selectedBox = 0;

positionScreen *pS;

box *a; box *b; box *c; box *d; box *e; box *f; box *g; box *h; box *i;

mainWindow *line; mainWindow *col;

keySpecial *press;

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
    carregaVariaveis();
    showBoxes();        //Caixas relativas a matriz principal
    //showBorders();      //Deu errado, caixas dimensionadas por pixels, caracteres fora da janela
    screenReading();    //Habilita a leitura de ambas as caixas
    showMouse();
    selectBox();        //Habilita a escrita na caixa selecionada
    moveBox();
    //textBox1(1);
    //textBox2(1);

}

void carregaVariaveis(){
    pS->screenPositionX = APP_COLUMNS;
    pS->screenPositionY = APP_LINES;
}

//Movimenta a janela junto com todo o conteúdo
void moveBox(){
        if ((mouseY == 3) && ((mouseX > 6) && (mouseX < 122))){
            if(mouseOnPress == 1){
                pS->screenPositionX = mouseX;
                pS->screenPositionY = mouseY;
                printf("aq");
            }

        }
}

void showBorders(void){
    mpcHLine(top,left, right, RED_2, 1);
    mostraTexto(3,7, a->box1);

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
   for (int x = 0; x < pS->screenPositionX; x++) {
      for (int y = 0; y < pS->screenPositionY; y++) {
         mpcSetChar(y,               x, 10, F_STD, GREY_5, GREY_4, 1.0); //fundo
      }
   }
   //final janela principal

   //caixa de texto
   for (int x = 6; x < pS->screenPositionX-5; x++) {
      mpcSetChar(            3,               x, 9, F_STD, WHITE, ORANGE_2, 1.0); //cima
      mpcSetChar(pS->screenPositionY - 5, pS->screenPositionX - x, 9, F_STD, WHITE, WHITE, 1.0); //baixo
          for (int y = 4; y < pS->screenPositionY-5; y++) {
             mpcSetChar(y,               x, 10, F_STD, WHITE,  WHITE, 1.0); //fundo
             mpcSetChar(y,               6, 10, F_STD, WHITE,  WHITE, 1.0); //esq
             mpcSetChar(y, pS->screenPositionX - 6, 10, F_STD, WHITE,  WHITE, 1.0); //dir
          }
   }
   mpcSetChar(          3,             6, 11, F_STD, WHITE, ORANGE_2, 1.0);
   mpcSetChar(          3, pS->screenPositionX-6, 12, F_STD, WHITE, ORANGE_2, 1.0);
   mpcSetChar(pS->screenPositionY-5,             6, 13, F_STD, WHITE, WHITE, 1.0);
   mpcSetChar(pS->screenPositionY-5, pS->screenPositionX-6, 14, F_STD, WHITE, WHITE, 1.0);
   char texto[] = "Caixa de Texto";
   for(int cont = 0; cont < (int)strlen(texto); cont++){
        mpcSetChar(3, 57+cont, texto[cont], F_IN, WHITE, ORANGE_2, 1 );
   }
   //final caixa de texto

   //início caixa de texto 1
   char texto2[] = "Caixa de Texto com 1 linha:";
   for(int cont = 0; cont < (int)strlen(texto2); cont++){
        mpcSetChar(5, 12+cont, texto2[cont], F_N, BLACK, WHITE, 1 );
   }
   for (int x = 12; x < pS->screenPositionX - 12; x++) {
      mpcSetChar(             6,               x, 9, F_STD, BLACK, BLUE_2, 1.0); //cima
      mpcSetChar(pS->screenPositionY - 27, pS->screenPositionX - x, 9, F_STD, BLACK, BLUE_2, 1.0); //baixo
          for (int y = 6; y < pS->screenPositionY-27; y++) {
             mpcSetChar(7,                x, 10, F_STD, BLUE_2,  BLUE_2, 1.0); //fundo
             mpcSetChar(y,               12, 10, F_STD,  BLACK, BLUE_2, 1.0); //esq
             mpcSetChar(y, pS->screenPositionX - 12, 10, F_STD,  BLACK, BLUE_2, 1.0); //dir
          }
   }
   mpcSetChar(           6,             12, 11, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(           6, pS->screenPositionX-12, 12, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(pS->screenPositionY-27,             12, 13, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(pS->screenPositionY-27, pS->screenPositionX-12, 14, F_STD, BLACK, BLUE_2, 1.0);
   //final caixa de texto 1

   //inicio caixa de texto 2
   char texto3[] = "Caixa de Texto com várias linhas:";
   for(int cont = 0; cont < (int)strlen(texto3); cont++){
        mpcSetChar(9, 12+cont, texto3[cont], F_N, BLACK, WHITE, 1 );
   }
   for (int x = 12; x < pS->screenPositionX - 12; x++) {
      mpcSetChar(            10,               x, 9, F_STD, BLACK, BLUE_2, 1.0); //cima
      //mpcSetChar(screenPositionY - 15, screenPositionX - x, 9, F_STD, GREY_2, GREY_2, 1.0); //baixo
          for (int y = 10; y < pS->screenPositionY-15; y++) {
             mpcSetChar(y+1,                x, 10, F_STD,  BLUE_2,  BLUE_2, 1.0); //fundo
             mpcSetChar(20, x, 9, F_STD, BLACK, BLUE_2, 1.0); //baixo
             mpcSetChar(y,               12, 10, F_STD, BLACK, BLUE_2, 1.0); //esq
             mpcSetChar(y, pS->screenPositionX - 12, 10, F_STD, BLACK, BLUE_2, 1.0); //dir
          }
   }
   mpcSetChar(          10,             12, 11, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(          10, pS->screenPositionX-12, 12, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(pS->screenPositionY-15,             12, 13, F_STD, BLACK, BLUE_2, 1.0);
   mpcSetChar(pS->screenPositionY-15, pS->screenPositionX-12, 14, F_STD, BLACK, BLUE_2, 1.0);
   //final caixa de texto 2

   //início primeiro botao
   for (int x = 37; x < pS->screenPositionX - 65; x++) {
      mpcSetChar(           25,                    x, 9, F_STD, BLACK, WHITE, 1.0); //cima
      mpcSetChar(pS->screenPositionY - 7, pS->screenPositionX - x - 29, 9, F_STD, BLACK, WHITE, 1.0); //baixo
          for (int y = 26; y < pS->screenPositionY-7; y++) {
             mpcSetChar(y,                x, 10, F_STD, WHITE, WHITE, 1.0); //fundo
             mpcSetChar(y,               37, 10, F_STD, BLACK, WHITE, 1.0); //esq
             mpcSetChar(y, pS->screenPositionX - 66, 10, F_STD, BLACK, WHITE, 1.0); //dir
          }
   }
   mpcSetChar(         25,             37, 11, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(         25, pS->screenPositionX-66, 12, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(pS->screenPositionY-7,             37, 13, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(pS->screenPositionY-7, pS->screenPositionX-66, 14, F_STD, BLACK, WHITE, 1.0);
   char texto4[] = ">       CANCELAR       <";
   for(int cont = 0; cont < (int)strlen(texto4); cont++){
        mpcSetChar(27, 38+cont, texto4[cont], F_N, BLACK, WHITE, 1 );
   }
   //final primeiro botao

   //segundo botao
   for (int x = 65; x < pS->screenPositionX - 37; x++) {
      mpcSetChar(           25, x, 9, F_STD, BLACK, WHITE, 1.0); //cima
      mpcSetChar(pS->screenPositionY - 7, x, 9, F_STD, BLACK, WHITE, 1.0); //baixo
          for (int y = 26; y < pS->screenPositionY-7; y++) {
             mpcSetChar(y,                x, 10, F_STD, WHITE, WHITE, 1.0); //fundo
             mpcSetChar(y,               65, 10, F_STD, BLACK, WHITE, 1.0); //esq
             mpcSetChar(y, pS->screenPositionX - 38, 10, F_STD, BLACK, WHITE, 1.0); //dir
          }
   }
   mpcSetChar(         25,             65, 11, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(         25, pS->screenPositionX-38, 12, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(pS->screenPositionY-7,             65, 13, F_STD, BLACK, WHITE, 1.0);
   mpcSetChar(pS->screenPositionY-7, pS->screenPositionX-38, 14, F_STD, BLACK, WHITE, 1.0);
   char texto5[] = ">        ENVIAR        <";
   for(int cont = 0; cont < (int)strlen(texto5); cont++){
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
        textBox1(1);
    }
    if(selectedBox == 2){
        textBox2(1);
    }
}

//Funções relativas a caixa de uma linha
void textBox1(int write){
    if(write == 1 && k < 103){
     switch (keyPRESS) {
         case 97:
            a->box1[k] = 'a';
            k++;
            break;
         case 98:
            a->box1[k] = 'b';
            k++;
            break;
         case 99:
            a->box1[k] = 'c';
            k++;
            break;
         case 100:
            a->box1[k] = 'd';
            k++;
            break;
         case 101:
            a->box1[k] = 'e';
            k++;
            break;
         case 102:
            a->box1[k] = 'f';
            k++;
            break;
         case 103:
            a->box1[k] = 'g';
            k++;
            break;
         case 104:
            a->box1[k] = 'h';
            k++;
            break;
         case 105:
            a->box1[k] = 'i';
            k++;
            break;
         case 106:
            a->box1[k] = 'j';
            k++;
            break;
         case 107:
            a->box1[k] = 'k';
            k++;
            break;
         case 108:
            a->box1[k] = 'l';
            k++;
            break;
         case 109:
            a->box1[k] = 'm';
            k++;
            break;
         case 110:
            a->box1[k] = 'n';
            k++;
            break;
         case 111:
            a->box1[k] = 'o';
            k++;
            break;
         case 112:
            a->box1[k] = 'p';
            k++;
            break;
         case 113:
            a->box1[k] = 'q';
            k++;
            break;
         case 114:
            a->box1[k] = 'r';
            k++;
            break;
         case 115:
            a->box1[k] = 's';
            k++;
            break;
         case 116:
            a->box1[k] = 't';
            k++;
            break;
         case 117:
            a->box1[k] = 'u';
            k++;
            break;
         case 118:
            a->box1[k] = 'v';
            k++;
            break;
         case 119:
            a->box1[k] = 'w';
            k++;
            break;
         case 120:
            a->box1[k] = 'x';
            k++;
            break;
         case 121:
            a->box1[k] = 'y';
            k++;
            break;
         case 122:
            a->box1[k] = 'z';
            k++;
            break;
         case 32:
            a->box1[k] = ' ';
            k++;
            break;
        }
      }keyPRESS = 0;
      //mostraTexto(7,13,caixa1);
}

//Funções relativas a caixa de várias linhas com teclas especiais
void textBox2(int write){

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
    if(press->home == 1) {
        mpcSetCursorPos(11, 13);
        preencheLinha(keyPRESS);
        keyPRESS = 0;
    }
    if(press->home == 0){
        preencheLinha(keyPRESS);
        keyPRESS = 0;
    }
    if(press->endi == 1){
        preencheLinha(keyPRESS);
        keyPRESS = 0;
    }
    if(press->left == 1){
        pos_coluna -= 1;
        press->left = 0;
        mpcSetCursorPos(pos_linha, pos_coluna);
        preencheLinha(keyPRESS);
        keyPRESS = 0;
    }
    if(press->up == 1){
        mpcSetCursorPos(pos_linha - 1, pos_coluna);
        pos_linha = pos_linha - 1;
        preencheLinha(keyPRESS);
        keyPRESS = 0;
        press->up = 0;
    }
    if(press->down == 1){
        mpcSetCursorPos(pos_linha + 1, pos_coluna);
        pos_linha = pos_linha + 1;
        preencheLinha(keyPRESS);
        keyPRESS = 0;
        press->down = 0;
    }
    if(press->right == 1){
        mpcSetCursorPos(pos_linha, pos_coluna + 1);
        pos_coluna = pos_coluna + 1;
        preencheLinha(keyPRESS);
        keyPRESS = 0;
        press->right = 0;
    }
}

//Função que escreve na caixa de várias linhas, selecionada o vetor a ser escrito em caso de quebra de linha ou ENTER
void preencheLinha(int keypress){
        if((quebra2 == 1) && (linha != 13)) {
        //enter++;
        if(linha == 1){
            mostraTexto(12, 13, b->box2);
            quebra2 = 0;
            linha++;
        }
        if(linha == 2){
            mostraTexto(13, 13, c->box2);
            quebra2 = 0;
            linha++;
        }
        if(linha == 3){
            mostraTexto(14, 13, d->box2);
            quebra2 = 0;
            linha++;
        }
        if(linha == 4){
            mostraTexto(15, 13, e->box2);
            quebra2 = 0;
            linha++;
        }
        if(linha == 5){
            mostraTexto(16, 13, f->box2);
            quebra2 = 0;
            linha++;
        }
        if(linha == 6){
            mostraTexto(17, 13, g->box2);
            quebra2 = 0;
            linha++;
        }
        if(linha == 7){
            mostraTexto(18, 13, h->box2);
            quebra2 = 0;
            linha++;
        }
        if(linha == 8){
            mostraTexto(19, 13, i->box2);
            quebra2 = 0;
            linha++;
        }
    }
    if(linha == 1){
        switch (keypress) {
             case 97:
                a->box2[j] = 'a';
                printf("\n %d", j);
                j++;
                break;
             case 98:
                a->box2[j] = 'b';
                j++;
                break;
             case 99:
                a->box2[j] = 'c';
                j++;
                break;
             case 100:
                a->box2[j] = 'd';
                j++;
                break;
             case 101:
                a->box2[j] = 'e';
                j++;
                break;
             case 102:
                a->box2[j] = 'f';
                j++;
                break;
             case 103:
                a->box2[j] = 'g';
                j++;
                break;
             case 104:
                a->box2[j] = 'h';
                j++;
                break;
             case 105:
                a->box2[j] = 'i';
                j++;
                break;
             case 106:
                a->box2[j] = 'j';
                j++;
                break;
             case 107:
                a->box2[j] = 'k';
                j++;
                break;
             case 108:
                a->box2[j] = 'l';
                j++;
                break;
             case 109:
                a->box2[j] = 'm';
                j++;
                break;
             case 110:
                a->box2[j] = 'n';
                j++;
                break;
             case 111:
                a->box2[j] = 'o';
                j++;
                break;
             case 112:
                a->box2[j] = 'p';
                j++;
                break;
             case 113:
                a->box2[j] = 'q';
                j++;
                break;
             case 114:
                a->box2[j] = 'r';
                j++;
                break;
             case 115:
                a->box2[j] = 's';
                j++;
                break;
             case 116:
                a->box2[j] = 't';
                j++;
                break;
             case 117:
                a->box2[j] = 'u';
                j++;
                break;
             case 118:
                a->box2[j] = 'v';
                j++;
                break;
             case 119:
                a->box2[j] = 'w';
                j++;
                break;
             case 120:
                a->box2[j] = 'x';
                j++;
                break;
             case 121:
                a->box2[j] = 'y';
                j++;
                break;
             case 122:
                a->box2[j] = 'z';
                j++;
                break;
             case 32:
                a->box2[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 2){
        switch (keypress) {
             case 97:
                b->box2[j] = 'a';
                j++;
                break;
             case 98:
                b->box2[j] = 'b';
                j++;
                break;
             case 99:
                b->box2[j] = 'c';
                j++;
                break;
             case 100:
                b->box2[j] = 'd';
                j++;
                break;
             case 101:
                b->box2[j] = 'e';
                j++;
                break;
             case 102:
                b->box2[j] = 'f';
                j++;
                break;
             case 103:
                b->box2[j] = 'g';
                j++;
                break;
             case 104:
                b->box2[j] = 'h';
                j++;
                break;
             case 105:
                b->box2[j] = 'i';
                j++;
                break;
             case 106:
                b->box2[j] = 'j';
                j++;
                break;
             case 107:
                b->box2[j] = 'k';
                j++;
                break;
             case 108:
                b->box2[j] = 'l';
                j++;
                break;
             case 109:
                b->box2[j] = 'm';
                j++;
                break;
             case 110:
                b->box2[j] = 'n';
                j++;
                break;
             case 111:
                b->box2[j] = 'o';
                j++;
                break;
             case 112:
                b->box2[j] = 'p';
                j++;
                break;
             case 113:
                b->box2[j] = 'q';
                j++;
                break;
             case 114:
                b->box2[j] = 'r';
                j++;
                break;
             case 115:
                b->box2[j] = 's';
                j++;
                break;
             case 116:
                b->box2[j] = 't';
                j++;
                break;
             case 117:
                b->box2[j] = 'u';
                j++;
                break;
             case 118:
                b->box2[j] = 'v';
                j++;
                break;
             case 119:
                b->box2[j] = 'w';
                j++;
                break;
             case 120:
                b->box2[j] = 'x';
                j++;
                break;
             case 121:
                b->box2[j] = 'y';
                j++;
                break;
             case 122:
                b->box2[j] = 'z';
                j++;
                break;
             case 32:
                b->box2[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 3){
        switch (keypress) {
            case 97:
                c->box2[j] = 'a';
                j++;
                break;
             case 98:
                c->box2[j] = 'b';
                j++;
                break;
             case 99:
                c->box2[j] = 'c';
                j++;
                break;
             case 100:
                c->box2[j] = 'd';
                j++;
                break;
             case 101:
                c->box2[j] = 'e';
                j++;
                break;
             case 102:
                c->box2[j] = 'f';
                j++;
                break;
             case 103:
                c->box2[j] = 'g';
                j++;
                break;
             case 104:
                c->box2[j] = 'h';
                j++;
                break;
             case 105:
                c->box2[j] = 'i';
                j++;
                break;
             case 106:
                c->box2[j] = 'j';
                j++;
                break;
             case 107:
                c->box2[j] = 'k';
                j++;
                break;
             case 108:
                c->box2[j] = 'l';
                j++;
                break;
             case 109:
                c->box2[j] = 'm';
                j++;
                break;
             case 110:
                c->box2[j] = 'n';
                j++;
                break;
             case 111:
                c->box2[j] = 'o';
                j++;
                break;
             case 112:
                c->box2[j] = 'p';
                j++;
                break;
             case 113:
                c->box2[j] = 'q';
                j++;
                break;
             case 114:
                c->box2[j] = 'r';
                j++;
                break;
             case 115:
                c->box2[j] = 's';
                j++;
                break;
             case 116:
                c->box2[j] = 't';
                j++;
                break;
             case 117:
                c->box2[j] = 'u';
                j++;
                break;
             case 118:
                c->box2[j] = 'v';
                j++;
                break;
             case 119:
                c->box2[j] = 'w';
                j++;
                break;
             case 120:
                c->box2[j] = 'x';
                j++;
                break;
             case 121:
                c->box2[j] = 'y';
                j++;
                break;
             case 122:
                c->box2[j] = 'z';
                j++;
                break;
             case 32:
                c->box2[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 4){
        switch (keypress) {
             case 97:
                //preencheLinha(linha, j, 'a');
                d->box2[j] = 'a';
                j++;
                break;
             case 98:
                d->box2[j] = 'b';
                j++;
                break;
             case 99:
                d->box2[j] = 'c';
                j++;
                break;
             case 100:
                d->box2[j] = 'd';
                j++;
                break;
             case 101:
                d->box2[j] = 'e';
                j++;
                break;
             case 102:
                d->box2[j] = 'f';
                j++;
                break;
             case 103:
                d->box2[j] = 'g';
                j++;
                break;
             case 104:
                d->box2[j] = 'h';
                j++;
                break;
             case 105:
                d->box2[j] = 'i';
                j++;
                break;
             case 106:
                d->box2[j] = 'j';
                j++;
                break;
             case 107:
                d->box2[j] = 'k';
                j++;
                break;
             case 108:
                d->box2[j] = 'l';
                j++;
                break;
             case 109:
                d->box2[j] = 'm';
                j++;
                break;
             case 110:
                d->box2[j] = 'n';
                j++;
                break;
             case 111:
                d->box2[j] = 'o';
                j++;
                break;
             case 112:
                d->box2[j] = 'p';
                j++;
                break;
             case 113:
                d->box2[j] = 'q';
                j++;
                break;
             case 114:
                d->box2[j] = 'r';
                j++;
                break;
             case 115:
                d->box2[j] = 's';
                j++;
                break;
             case 116:
                d->box2[j] = 't';
                j++;
                break;
             case 117:
                d->box2[j] = 'u';
                j++;
                break;
             case 118:
                d->box2[j] = 'v';
                j++;
                break;
             case 119:
                d->box2[j] = 'w';
                j++;
                break;
             case 120:
                d->box2[j] = 'x';
                j++;
                break;
             case 121:
                d->box2[j] = 'y';
                j++;
                break;
             case 122:
                d->box2[j] = 'z';
                j++;
                break;
             case 32:
                d->box2[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 5){
        switch (keypress) {
             case 97:
                e->box2[j] = 'a';
                j++;
                break;
             case 98:
                e->box2[j] = 'b';
                j++;
                break;
             case 99:
                e->box2[j] = 'c';
                j++;
                break;
             case 100:
                e->box2[j] = 'd';
                j++;
                break;
             case 101:
                e->box2[j] = 'e';
                j++;
                break;
             case 102:
                e->box2[j] = 'f';
                j++;
                break;
             case 103:
                e->box2[j] = 'g';
                j++;
                break;
             case 104:
                e->box2[j] = 'h';
                j++;
                break;
             case 105:
                e->box2[j] = 'i';
                j++;
                break;
             case 106:
                e->box2[j] = 'j';
                j++;
                break;
             case 107:
                e->box2[j] = 'k';
                j++;
                break;
             case 108:
                e->box2[j] = 'l';
                j++;
                break;
             case 109:
                e->box2[j] = 'm';
                j++;
                break;
             case 110:
                e->box2[j] = 'n';
                j++;
                break;
             case 111:
                e->box2[j] = 'o';
                j++;
                break;
             case 112:
                e->box2[j] = 'p';
                j++;
                break;
             case 113:
                e->box2[j] = 'q';
                j++;
                break;
             case 114:
                e->box2[j] = 'r';
                j++;
                break;
             case 115:
                e->box2[j] = 's';
                j++;
                break;
             case 116:
                e->box2[j] = 't';
                j++;
                break;
             case 117:
                e->box2[j] = 'u';
                j++;
                break;
             case 118:
                e->box2[j] = 'v';
                j++;
                break;
             case 119:
                e->box2[j] = 'w';
                j++;
                break;
             case 120:
                e->box2[j] = 'x';
                j++;
                break;
             case 121:
                e->box2[j] = 'y';
                j++;
                break;
             case 122:
                e->box2[j] = 'z';
                j++;
                break;
             case 32:
                e->box2[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 6){
        switch (keypress) {
             case 97:
                f->box2[j] = 'a';
                j++;
                break;
             case 98:
                f->box2[j] = 'b';
                j++;
                break;
             case 99:
                f->box2[j] = 'c';
                j++;
                break;
             case 100:
                f->box2[j] = 'd';
                j++;
                break;
             case 101:
                f->box2[j] = 'e';
                j++;
                break;
             case 102:
                f->box2[j] = 'f';
                j++;
                break;
             case 103:
                f->box2[j] = 'g';
                j++;
                break;
             case 104:
                f->box2[j] = 'h';
                j++;
                break;
             case 105:
                f->box2[j] = 'i';
                j++;
                break;
             case 106:
                f->box2[j] = 'j';
                j++;
                break;
             case 107:
                f->box2[j] = 'k';
                j++;
                break;
             case 108:
                f->box2[j] = 'l';
                j++;
                break;
             case 109:
                f->box2[j] = 'm';
                j++;
                break;
             case 110:
                f->box2[j] = 'n';
                j++;
                break;
             case 111:
                f->box2[j] = 'o';
                j++;
                break;
             case 112:
                f->box2[j] = 'p';
                j++;
                break;
             case 113:
                f->box2[j] = 'q';
                j++;
                break;
             case 114:
                f->box2[j] = 'r';
                j++;
                break;
             case 115:
                f->box2[j] = 's';
                j++;
                break;
             case 116:
                f->box2[j] = 't';
                j++;
                break;
             case 117:
                f->box2[j] = 'u';
                j++;
                break;
             case 118:
                f->box2[j] = 'v';
                j++;
                break;
             case 119:
                f->box2[j] = 'w';
                j++;
                break;
             case 120:
                f->box2[j] = 'x';
                j++;
                break;
             case 121:
                f->box2[j] = 'y';
                j++;
                break;
             case 122:
                f->box2[j] = 'z';
                j++;
                break;
             case 32:
                f->box2[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 7){
        switch (keypress) {
             case 97:
                g->box2[j] = 'a';
                j++;
                break;
             case 98:
                g->box2[j] = 'b';
                j++;
                break;
             case 99:
                g->box2[j] = 'c';
                j++;
                break;
             case 100:
                g->box2[j] = 'd';
                j++;
                break;
             case 101:
                g->box2[j] = 'e';
                j++;
                break;
             case 102:
                g->box2[j] = 'f';
                j++;
                break;
             case 103:
                g->box2[j] = 'g';
                j++;
                break;
             case 104:
                g->box2[j] = 'h';
                j++;
                break;
             case 105:
                g->box2[j] = 'i';
                j++;
                break;
             case 106:
                g->box2[j] = 'j';
                j++;
                break;
             case 107:
                g->box2[j] = 'k';
                j++;
                break;
             case 108:
                g->box2[j] = 'l';
                j++;
                break;
             case 109:
                g->box2[j] = 'm';
                j++;
                break;
             case 110:
                g->box2[j] = 'n';
                j++;
                break;
             case 111:
                g->box2[j] = 'o';
                j++;
                break;
             case 112:
                g->box2[j] = 'p';
                j++;
                break;
             case 113:
                g->box2[j] = 'q';
                j++;
                break;
             case 114:
                g->box2[j] = 'r';
                j++;
                break;
             case 115:
                g->box2[j] = 's';
                j++;
                break;
             case 116:
                g->box2[j] = 't';
                j++;
                break;
             case 117:
                g->box2[j] = 'u';
                j++;
                break;
             case 118:
                g->box2[j] = 'v';
                j++;
                break;
             case 119:
                g->box2[j] = 'w';
                j++;
                break;
             case 120:
                g->box2[j] = 'x';
                j++;
                break;
             case 121:
                g->box2[j] = 'y';
                j++;
                break;
             case 122:
                g->box2[j] = 'z';
                j++;
                break;
             case 32:
                g->box2[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 8){
        switch (keypress) {
             case 97:
                //preencheLinha(linha, j, 'a');
                h->box2[j] = 'a';
                j++;
                break;
             case 98:
                h->box2[j] = 'b';
                j++;
                break;
             case 99:
                h->box2[j] = 'c';
                j++;
                break;
             case 100:
                h->box2[j] = 'd';
                j++;
                break;
             case 101:
                h->box2[j] = 'e';
                j++;
                break;
             case 102:
                h->box2[j] = 'f';
                j++;
                break;
             case 103:
                h->box2[j] = 'g';
                j++;
                break;
             case 104:
                h->box2[j] = 'h';
                j++;
                break;
             case 105:
                h->box2[j] = 'i';
                j++;
                break;
             case 106:
                h->box2[j] = 'j';
                j++;
                break;
             case 107:
                h->box2[j] = 'k';
                j++;
                break;
             case 108:
                h->box2[j] = 'l';
                j++;
                break;
             case 109:
                h->box2[j] = 'm';
                j++;
                break;
             case 110:
                h->box2[j] = 'n';
                j++;
                break;
             case 111:
                h->box2[j] = 'o';
                j++;
                break;
             case 112:
                h->box2[j] = 'p';
                j++;
                break;
             case 113:
                h->box2[j] = 'q';
                j++;
                break;
             case 114:
                h->box2[j] = 'r';
                j++;
                break;
             case 115:
                h->box2[j] = 's';
                j++;
                break;
             case 116:
                h->box2[j] = 't';
                j++;
                break;
             case 117:
                h->box2[j] = 'u';
                j++;
                break;
             case 118:
                h->box2[j] = 'v';
                j++;
                break;
             case 119:
                h->box2[j] = 'w';
                j++;
                break;
             case 120:
                h->box2[j] = 'x';
                j++;
                break;
             case 121:
                h->box2[j] = 'y';
                j++;
                break;
             case 122:
                h->box2[j] = 'z';
                j++;
                break;
             case 32:
                h->box2[j] = ' ';
                j++;
                break;
        } keypress = 0;
    }
    if(linha == 9){
        switch (keypress) {
             case 97:
                //preencheLinha(linha, j, 'a');
                i->box1[j] = 'a';
                j++;
                break;
             case 98:
                i->box1[j] = 'b';
                j++;
                break;
             case 99:
                i->box1[j] = 'c';
                j++;
                break;
             case 100:
                i->box1[j] = 'd';
                j++;
                break;
             case 101:
                i->box1[j] = 'e';
                j++;
                break;
             case 102:
                i->box1[j] = 'f';
                j++;
                break;
             case 103:
                i->box1[j] = 'g';
                j++;
                break;
             case 104:
                i->box1[j] = 'h';
                j++;
                break;
             case 105:
                i->box1[j] = 'i';
                j++;
                break;
             case 106:
                i->box1[j] = 'j';
                j++;
                break;
             case 107:
                i->box1[j] = 'k';
                j++;
                break;
             case 108:
                i->box1[j] = 'l';
                j++;
                break;
             case 109:
                i->box1[j] = 'm';
                j++;
                break;
             case 110:
                i->box1[j] = 'n';
                j++;
                break;
             case 111:
                i->box1[j] = 'o';
                j++;
                break;
             case 112:
                i->box1[j] = 'p';
                j++;
                break;
             case 113:
                i->box1[j] = 'q';
                j++;
                break;
             case 114:
                i->box1[j] = 'r';
                j++;
                break;
             case 115:
                i->box1[j] = 's';
                j++;
                break;
             case 116:
                i->box1[j] = 't';
                j++;
                break;
             case 117:
                i->box1[j] = 'u';
                j++;
                break;
             case 118:
                i->box1[j] = 'v';
                j++;
                break;
             case 119:
                i->box1[j] = 'w';
                j++;
                break;
             case 120:
                i->box1[j] = 'x';
                j++;
                break;
             case 121:
                i->box1[j] = 'y';
                j++;
                break;
             case 122:
                i->box1[j] = 'z';
                j++;
                break;
             case 32:
                i->box1[j] = ' ';
                j++;
                break;
        } keypress = 0;

        if(mouseOnPress == 0){
            mpcSetCursorPos(mouseY, mouseX);
        }
}
}

//Função habilitando a leitura em ambas as caixas
void screenReading(){
    mostraTexto(7,13,a->box1);
    mostraTexto(11, 13, a->box2);
    mostraTexto(12, 13, b->box2);
    mostraTexto(13, 13, c->box2);
    mostraTexto(14, 13, d->box2);
    mostraTexto(15, 13, e->box2);
    mostraTexto(16, 13, f->box2);
    mostraTexto(17, 13, g->box2);
    mostraTexto(18, 13, h->box2);
    mostraTexto(19, 13, i->box2);
   //char texto[] = "Caixa de Texto";
   //mostraTexto(6, 30, texto);
   //mostraTexto(3, 57, "Caixa de Texto");
   /*for(int cont = 0; cont < strlen(texto); cont++){
        mpcSetChar(3, 57+cont, texto[cont], F_IN, WHITE, ORANGE_2, 1 );
   }*/
}


//funcao para exibir strings na tela.
void mostraTexto(int l, int c, char *text){
   for (int cont = 0; cont < (int)strlen(text); cont++){
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
        press->home++;
        //printf("\n %d", home);

     }
     if((key == 107) && (special == 1)){
        press->endi++;
     }
     if(key == 127){
        press->del++;
            //Se for pressionado End
            if(press->endi == 1) {
                mpcSetCursorPos(pos_linha, pos_coluna);
                if((pos_linha = 11)){
                    mostraTexto(pos_linha, pos_coluna, a->box2);
                }
                if((pos_linha = 12)){
                    mostraTexto(pos_linha, pos_coluna, b->box2);
                }
                if((pos_linha = 13)){
                    mostraTexto(pos_linha, pos_coluna, c->box2);
                }
                if((pos_linha = 14)){
                    mostraTexto(pos_linha, pos_coluna, d->box2);
                }
                if((pos_linha = 15)){
                    mostraTexto(pos_linha, pos_coluna, e->box2);
                }
                press->endi = 0;
            }
     }

     if(key == 8){
        press->backspace++;
     }
     //verifica se as setas direcionais foram digitadas
     if((key == 100) && (special == 1)){
        press->left++;
     }
     if((key == 101) && (special == 1)){
        press->up++;
     }
     if((key == 102) && (special == 1)){
        press->right++;
     }
     if((key == 103) && (special == 1)){
        press->down++;
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
