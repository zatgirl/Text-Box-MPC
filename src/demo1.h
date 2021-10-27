//==================================================//
//    Multi-Platform Console (MPC) - v4.6.1 @ 2010  //
//     UFSM - Federal University of Santa Maria     //
//==================================================//

#ifndef __APP_DEMO_H__
#define __APP_DEMO_H__

#include <string>

static const int APP_LINES = 35;
static const int APP_COLUMNS = 128;

void initMpc(void);
void initApp(void);

void criaImagens(void);

void showBorders(void);
void preencheTela();
void showMouse();
void animaImagens();

void displayApp(void);
void showBoxes(void);
void mostraTexto(int, int, char);

void displayApp(void);

void selectBox (void);
void caixatexto1(int keypress);
void caixatexto2(void);
void preencheLinha(int keypress);

void cbMouse(int l, int c, int button, int state);

void cbKeyboard(int key, int modifier, bool special, bool up);

void cbUpdate(void);

void mostraTexto(int l, int c, char *msg);


void negativoImg(int id);
int  criaImg(int tamanho);

#endif // __APP_DEMO_H__
