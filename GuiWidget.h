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

/* widget flag */
#define COGUI_WIDGET_FLAG_DEFAULT       0x0000
#define COGUI_WIDGET_FLAG_SHOWN         0x0001
#define COGUI_WIDGET_FLAG_DISABLE       0x0002
#define COGUI_WIDGET_FLAG_FOCUS         0x0004
#define COGUI_WIDGET_FLAG_TRANSPARENT   0x0008
#define COGUI_WIDGET_FLAG_FOCUSABLE     0x0010
#define COGUI_WIDGET_FLAG_DC_VISIBLE    0x0100
#define COGUI_WIDGET_FLAG_IN_ANIM       0x0200
#define COGUI_WIDGET_FLAG_IS_CONTAINER  0x0400

/*---------------------------- Function Define -------------------------------*/
cogui_widget_t * WidgetCreate(void);
void WidgetDel(cogui_widget_t * widget);

StatusType WidgetEventHandler(cogui_widget_t * widget, struct GuiEvent *event);

void WidgetFocus(cogui_widget_t * widget);
void WidgetUnFocus(cogui_widget_t * widget);

void WidgetSetFocus(cogui_widget_t * widget, EventHandlerPtr handler);
void WidgetSetUnFocus(cogui_widget_t * widget, EventHandlerPtr handler);

void WidgetGetRect(cogui_widget_t * widget, P_GuiRect rect);
void WidgetSetBorder(cogui_widget_t * widget, U32 style);
void WidgetSetRect(cogui_widget_t * widget, P_GuiRect rect);
void WidgetSetRectangle(cogui_widget_t * widget, S32 x, S32 y, S32 width, S32 height);
void WidgetGetExtent(cogui_widget_t * widget, P_GuiRect rect);

void WidgetSetMinsize(cogui_widget_t * widget, S32 width, S32 height);
void WidgetSetMinwidth(cogui_widget_t * widget, S32 width);
void WidgetSetMinheight(cogui_widget_t * widget, S32 height);

void WidgetShow(cogui_widget_t * widget);
StatusType WidgetOnshow(cogui_widget_t * widget, struct GuiEvent *event);
void WidgetHide(cogui_widget_t * widget);
StatusType WidgetOnhide(cogui_widget_t * widget, struct GuiEvent *event);
void WidgetUpdate(cogui_widget_t * widget);

/* get the physical position of a logic point on widget */
void WidgetPointToDevice(cogui_widget_t * widget, P_GuiPoint point);
/* get the physical position of a logic rect on widget */
void WidgetRectToDevice(cogui_widget_t * widget, P_GuiRect rect);

/* get the logic position of a physical point on widget */
void WidgetPointToLogic(cogui_widget_t * widget, P_GuiPoint point);
/* get the logic position of a physical rect on widget */
void widgetRectToLogic(cogui_widget_t * widget, P_GuiRect rect);

/* move widget and its children to a logic point */
void WidgetMoveToLogic(cogui_widget_t * widget, S32 dx, S32 dy);

void WidgetClipParent(cogui_widget_t * widget);
void WidgetClipReturn(cogui_widget_t * widget);

/* update the clip info of widget */
void WidgetUpdateClip(cogui_widget_t * widget);

/* get the next sibling of widget */
cogui_widget_t * WidgetGetNextSibling(cogui_widget_t * widget);
/* get the prev sibling of widget */
cogui_widget_t * WidgetGetPrevSibling(cogui_widget_t * widget);

#endif /* _GUI_WIDGET_H */
