/**
 *******************************************************************************
 * @file       GuiWidget.h
 * @version    V0.0.1   
 * @date       2019.5.26
 * @brief      Some widget function for GUI engine's widget.	
 *******************************************************************************
 */ 

#ifndef _GUI_WIDGET_H
#define _GUI_WIDGET_H

/*---------------------------- structure -------------------------------------*/
typedef struct GuiWidget
{
    /* the widget that contains this widget */
    struct GuiWidget *parent;
    /* the window that contains this widget */
    GuiWin *topLevel;
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
    U16 borderStyle;

    /* call back */
    StatusType  (*onFocusIn)(struct GuiWidget *widget, struct GuiEvent *event);
    StatusType (*onFocusOut)(struct GuiWidget *widget, struct GuiEvent *event);

    /* the event handler */
    StatusType (*handler)(P_GuiWidget widget ,struct GuiEvent *event);

    /* user private data */
    U32 userData;

}GuiWidget,*P_GuiWidget;

/* widget flag */
#define GUI_WIDGET_FLAG_DEFAULT       0x0000
#define GUI_WIDGET_FLAG_SHOWN         0x0001
#define GUI_WIDGET_FLAG_DISABLE       0x0002
#define GUI_WIDGET_FLAG_FOCUS         0x0004
#define GUI_WIDGET_FLAG_TRANSPARENT   0x0008
#define GUI_WIDGET_FLAG_FOCUSABLE     0x0010
#define GUI_WIDGET_FLAG_DC_VISIBLE    0x0100
#define GUI_WIDGET_FLAG_IN_ANIM       0x0200

/*---------------------------- Function Define -------------------------------*/
P_GuiWidget WidgetCreate();
void WidgetDel(P_GuiWidget widget);

StatusType WidgetEventHandler(P_GuiWidget widget, struct GuiEvent *event);

void WidgetFocus(P_GuiWidget widget);
void WidgetUnFocus(P_GuiWidget widget);

void WidgetSetFocus(P_GuiWidget widget, EventHandlerPtr handler);
void WidgetSetUnFocus(P_GuiWidget widget, EventHandlerPtr handler);

void WidgetGetRect(P_GuiWidget widget, P_GuiRect rect);
void WidgetSetBorder(P_GuiWidget widget, U32 style);
void WidgetSetRect(P_GuiWidget widget, P_GuiRect rect);
void WidgetSetRectangle(P_GuiWidget widget, S32 x, S32 y, S32 width, S32 height);
void WidgetGetExtent(P_GuiWidget widget, P_GuiRect rect);

void WidgetSetMinsize(P_GuiWidget widget, S32 width, S32 height);
void WidgetSetMinwidth(P_GuiWidget widget, S32 width);
void WidgetSetMinheight(P_GuiWidget widget, S32 height);

void WidgetShow(P_GuiWidget widget);
StatusType WidgetOnshow(P_GuiWidget widget, struct GuiEvent *event);
void WidgetHide(P_GuiWidget widget);
StatusType WidgetOnhide(P_GuiWidget widget, struct GuiEvent *event);
void WidgetUpdate(P_GuiWidget widget);

/* get the physical position of a logic point on widget */
void WidgetPointToDevice(P_GuiWidget widget, P_GuiPoint point);
/* get the physical position of a logic rect on widget */
void WidgetRectToDevice(P_GuiWidget widget, P_GuiRect rect);

/* get the logic position of a physical point on widget */
void WidgetPointToLogic(P_GuiWidget widget, P_GuiPoint point);
/* get the logic position of a physical rect on widget */
void widgetRectToLogic(P_GuiWidget widget, P_GuiRect rect);

/* move widget and its children to a logic point */
void WidgetMoveToLogic(P_GuiWidget widget, S32 dx, S32 dy);

/* update the clip info of widget */
void WidgetUpdateClip(rtgui_widget_t *widget);

#endif /* _GUI_WIDGET_H */