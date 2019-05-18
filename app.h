/**
 *******************************************************************************
 * @file       app.h
 * @version    V0.0.1   
 * @date       2019.5.18
 * @brief      This is a file for GUI engine's app.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include <CoOS.h>
#include "cogui.h"

typedef struct coguiApp
{
    U8      id;
    U8      *name;

    U16     refCnt;

    /* Task id */
    P_OSTCB tid;
    /* Message queue */
    P_QCB   mq

    void    *userDate
}GuiApp,*P_GuiApp;

/*---------------------------- Function declare ------------------------------*/
P_GuiApp CreateApp(U8 *name);

void RunApp (P_GuiApp *app);
void ExitApp(P_GuiApp *app);