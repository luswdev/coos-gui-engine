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

/*---------------------------- Function Define -------------------------------*/
P_GuiContainer ContainerVreate(void);
void ContainerDele(P_GuiContainer container);

StatusType ContainerEventHandler(P_GuiWidget widget, struct GuiEvent *event);

#endif /* _GUI_CONTAINER_H */
