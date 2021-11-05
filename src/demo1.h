//==================================================//
//    Multi-Platform Console (MPC) - v4.6.1 @ 2010  //
//     UFSM - Federal University of Santa Maria     //
//==================================================//

#ifndef __APP_DEMO_H__
#define __APP_DEMO_H__

#include <string>

class positionScreen{
public:
    int screenPositionX;
    int screenPositionY;
};
extern positionScreen *pS;

class box{
public:
    char box1[103] = {0};
    char box2[103] = {0};
};
extern box *a, *b, *c, *d, *e, *f, *g, *h, *i;

class mainWindow{
public:
    char lineY[25] = {0};
    char colX[113] = {0};
};
extern mainWindow *line, *col;

class keySpecial{
public:
    int enter = 0;
    int del = 0;
    int home = 0;
    int endi = 0;
    int backspace = 0;
    int press = 0;
    int left = 0;
    int up = 0;
    int down = 0;
    int right = 0;
};
extern keySpecial *press;

static const int APP_LINES = 35;
static const int APP_COLUMNS = 128;

void initMpc(void);
void initApp(void);

void criaImagens(void);

void showMouse();
void animaImagens();

void displayApp(void);
void showBorders(void);
void showBoxes(void);
void carregaVariaveis();
void moveBox();
void selectBox (void);
void textBox1(int write);
void textBox2(int write);
void preencheLinha(int keypress);
void screenReading();
void mostraTexto(int, int, char);

void cbMouse(int l, int c, int button, int state);
void cbKeyboard(int key, int modifier, bool special, bool up);
void cbUpdate(void);
void mostraTexto(int l, int c, char *msg);

void negativoImg(int id);
int  criaImg(int tamanho);

#endif // __APP_DEMO_H__
