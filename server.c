/**
 *******************************************************************************
 * @file       server.c
 * @version    V0.0.1   
 * @date       2019.5.19
 * @brief      The server for gui engine.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "app.h"

/*---------------------------- Variable declare ------------------------------*/
P_GuiApp serverApp = Co_NULL;


void SHandlerMonitorAdd();
void SHandlerMonitorRemove();
void SHandlerMouseBtn();
void SHandlerMouseMotion();
void SHandlerMouseKbd();
