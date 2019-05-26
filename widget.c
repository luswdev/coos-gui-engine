/**
 *******************************************************************************
 * @file       widget.c
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

void _WidgetInit(P_GuiWidget widget)
{
    /* set parent and toplevel root */
    widget->parent        = Co_NULL;
    widget->topLevel      = Co_NULL;

    widget->minWidth = widget->minHeight = 0;

    /* some common event handler */
    widget->onFocusIn   = Co_NULL;
    widget->onFocusOut  = Co_NULL;

    /* set default event handler */
    widget->handler = WidgetEventHandler;

    /* init user data private to 0 */
    widget->user_data = 0;
}

P_GuiWidget WidgetCreate()
{
    P_GuiWidget widget;

    widget = GuiMalloc(sizeof(GuiWidget));
    if(widget==Co_NULL){
        return Co_NULL;
    }
    
    _WidgetInit(widget);

    return widget;
}


void WidgetDel();

StatusType WidgetEventHandler(struct GuiEvent *event);

void WidgetFoucs(P_GuiWidget widget);
void WidgetUnFoucs(P_GuiWidget widget);

void WidgetSetFoucs(P_GuiWidget widget, EventHandlerPtr handler)
{
    if(widget!=Co_NULL){
        widget->OnFocusIn = handler;
    }
}

void WidgetSetUnFoucs(P_GuiWidget widget, EventHandlerPtr handler)
{
    if(widget!=Co_NULL){
        widget->OnFocusOut = handler;
    }
}

void WidgetGetRect(P_GuiWidget widget, P_GuiRect rect)
{
    if(widget!=Co_NULL && rect!=Co_NULL){
        rect = widget->rect;
    }
}

void WidgetSetBorder(P_GuiWidget widget, U32 style);
void WidgetSetRect(P_GuiWidget widget, P_GuiRect rect);
void WidgetSetRectangle(P_GuiWidget widget, S32 x, S32 y, S32 width, S32 height);
void WidgetSetExtent(P_GuiWidget widget, P_GuiRect rect);

void WidgetSetMinsize(P_GuiWidget widget, S32 width, S32 height)
{
    if(widget!=Co_NULL){
        widget->minWidth = width;
        widget->minHeight = height;
    }
}

void WidgetSetMinwidth(P_GuiWidget widget, S32 width)
{
    if(widget!=Co_NULL){
        widget->minWidth = width;
    }
}

void WidgetSetMinheight(P_GuiWidget widget, S32 height)
{
    if(widget!=Co_NULL){
        widget->minHeight = height;
    }
}