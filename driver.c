/**
 *******************************************************************************
 * @file       driver.c
 * @version    V0.0.1   
 * @date       2019.5.19
 * @brief      Some system function for GUI engine's driver.	
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "cogui.h"

static struct GuiGD _driver;
static struct P_GuiGD _currentDriver = &_driver;

P_GuiGD GraphiDriverGetDefault()
{   
    return _currentDriver;
}
