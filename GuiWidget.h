/**
 *******************************************************************************
 * @file       GuiWidget.h
 * @version    V0.0.1   
 * @date       2019.5.26
 * @brief      Some widget function for GUI engine's event.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 
/*---------------------------- Include ---------------------------------------*/
#include "GuiSystem.h"

/*---------------------------- structure -------------------------------------*/
typedef struct GuiWidget
{
    /* the widget that contains this widget */
    struct GuiWidget *parent;
    /* the window that contains this widget */
    GuiWin *topLevel
    /* the widget children and sibling */
    CoList sibling;

    S32 flag;

    /* the widget extent */
    GuiRect extent;
    /* the visiable extent */
    GuiRect extentVisiable;
    /* the rect clip information */
    GuiRegion clip;

    /* minimal width and height of widget */
    S16 minWidth, minHeight;
    /* widget align */
    S32 align;
    U16 border;
    U16 border_style;

    /* call back */
    StatusType  (*onFocusIn)(struct GuiWidget *widget, struct GuiEvent *event);
    StatusType (*onFocusOut)(struct GuiWidget *widget, struct GuiEvent *event);

    /* the event handler */
    StatusType (*handler)(struct GuiEvent *event);

    /* user private data */
    U32 userData;

}GuiWidget,*P_GuiWidget;

/*---------------------------- Function Define -------------------------------*/
P_GuiWidget WidgetCreate();
void WidgetDel();

StatusType WidgetEventHandler(struct GuiEvent *event);

void WidgetFoucs(P_GuiWidget widget);
void WidgetUnFoucs(P_GuiWidget widget);

void WidgetSetFoucs(P_GuiWidget widget, EventHandlerPtr handler);
void WidgetSetUnFoucs(P_GuiWidget widget, EventHandlerPtr handler);

void WidgetGetRect(P_GuiWidget widget, P_GuiRect rect);
void WidgetSetBorder(P_GuiWidget widget, U32 style);
void WidgetSetRect(P_GuiWidget widget, P_GuiRect rect);
void WidgetSetRectangle(P_GuiWidget widget, S32 x, S32 y, S32 width, S32 height);
void WidgetSetExtent(P_GuiWidget widget, P_GuiRect rect);

void WidgetSetMinsize(P_GuiWidget widget, S32 width, S32 height);
void WidgetSetMinwidth(P_GuiWidget widget, S32 width);
void WidgetSetMinheight(P_GuiWidget widget, S32 height);


