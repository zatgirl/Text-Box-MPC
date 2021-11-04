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
   initMpc();

   mpcRun(29); //frames por segundo
   return 0;
}
