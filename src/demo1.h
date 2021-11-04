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

static const int APP_LINES = 35;
static const int APP_COLUMNS = 128;

void initMpc(void);
void initApp(void);

void criaImagens(void);

void showBorders(void);
void screenReading();
void showMouse();
void animaImagens();

void displayApp(void);
void showBoxes(void);
void mostraTexto(int, int, char);

void displayApp(void);

void selectBox (void);
void textBox1(int write);
void textBox2(int write);
void preencheLinha(int keypress);
void moveBox();
void carregaVariaveis();

void cbMouse(int l, int c, int button, int state);

void cbKeyboard(int key, int modifier, bool special, bool up);

void cbUpdate(void);

void mostraTexto(int l, int c, char *msg);


void negativoImg(int id);
int  criaImg(int tamanho);

#endif // __APP_DEMO_H__
