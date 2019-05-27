/**
 *******************************************************************************
 * @file       GuiContainer.h
 * @version    V0.0.1   
 * @date       2019.5.27
 * @brief      Some widget function for GUI engine's container.	
 *******************************************************************************
 */ 

#ifndef _GUI_CONTAINER_H
#define _GUI_CONTAINER_H

/*---------------------------- structure -------------------------------------*/
typedef struct container
{
    GuiWidget parent;

    CoSList children;

}GuiContainer,*P_GuiContainer;

#endif /* _GUI_CONTAINER_H */