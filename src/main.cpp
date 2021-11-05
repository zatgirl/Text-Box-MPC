//=======================================================//
//    Multi-Platform Console (MPC) - v4.6 @ 2010         //
//     UFSM - Federal University of Santa Maria          //
//     Author: Cesar Tadeu Pozzer (pozzer at inf.ufsm.br)//
//     Colaborators: Cicero Pahins, Eduardo Ceretta      //
//=======================================================//
#include "mpc_c.h"
#include "demo1.h"

int main(void)
{
   pS = new positionScreen;
   a = new box;
   b = new box;
   c = new box;
   d = new box;
   e = new box;
   f = new box;
   g = new box;
   h = new box;
   i = new box;
   line = new mainWindow;
   col = new mainWindow;
   press = new keySpecial;

   initMpc();

   mpcRun(29); //frames por segundo
   return 0;
}
