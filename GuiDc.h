/**
 *******************************************************************************
 * @file       GuiDc.h
 * @version    V0.0.1   
 * @date       2019.5.29
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#ifndef _GUI_DC_H
#define _GUI_DC_H

#define _intSwap(x, y) {x ^= y; y ^= x; x ^= y;}

/*---------------------------- Function declare ------------------------------*/

/* create a hardware dc */
P_GuiDc DcHwCreate(P_GuiWidget owner);

void DcDrawLine(P_GuiDc dc, S32 x1, S32 y1, S32 x2, S32 y2);
void DcDrawRect(P_GuiDc dc, P_GuiRect rect);
void DcFillRectForecolor(P_GuiDc dc, P_GuiRect rect);
//void DcDrawRoundRect(P_GuiDc dc, P_GuiRect rect, S32 r);
//void DcFillRoundRect(P_GuiDc dc, P_GuiRect rect, S32 r);

void DcDrawHorizontalLine(P_GuiDc dc, S32 x1, S32 x2, S32 y);
void DcDrawVerticalLine(P_GuiDc dc, S32 x, S32 y1, S32 y2);


#endif /* _GUI_DC_H */
