/**
 *******************************************************************************
 * @file       container.c
 * @version    V0.0.1   
 * @date       2019.5.30
 * @brief      Some widget function for GUI engine's container.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"

void _InitContainer(P_GuiContainer container)
{
    container->handler = ContainerEventHandler;

    container->children.next = 0;
    container->layoutBox = Co_NULL;

    (P_GuiWidget)container->flag |= GUI_WIDGET_FLAG_FOCUSABLE;
}

P_GuiContainer ContainerCreate(void)
{
    P_GuiContainer container;

}

void ContainerDele(P_GuiContainer container)
{

}