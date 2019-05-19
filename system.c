/**
 *******************************************************************************
 * @file       system.c
 * @version    V0.0.1   
 * @date       2019.5.15
 * @brief      Some system function for GUI engine.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "GuiSystem.h"


/*---------------------------- Function Declare ------------------------------*/
void *GuiMalloc(U32 size)
{
    void *ptr;
    
    ptr = CoKmalloc(size);

    return ptr;
}


void GuiFree(void* memBuf)
{

    CoKfree(memBuf);
}