/**
 *******************************************************************************
 * @file       dc.c
 * @version    V0.0.1   
 * @date       2019.5.29
 * @brief      This is a file for GUI dc engine.	
 *******************************************************************************
 */ 

#include "cogui.h"

#define guiSgn(x) ((x<0)?-1:((x>0)?1:0)) /* macro to return the sign of a number */

void DcDrawLine(P_GuiDc dc, S32 x1, S32 y1, S32 x2, S32 y2)
{
    if(dc==Co_NULL){
        return;
    }

    if(y1==y2){
        dc->engine->drawHline(dc, x1, x2, y1);
    }
    else if (x1==x2){
        dc->engine->drawVline(dc, x1, y1, y2);
    }
    else
    {
        S32 dx, dy, sdx, sdy, dxabs, dyabs, x, y, px, py;
        register U64 i;
        /* rtgui_rect_t rect; */

        dx = x2 - x1;       /* the horizontal distance of the line */
        dy = y2 - y1;       /* the vertical distance of the line */

        dxabs = _UI_ABS(dx);
        dyabs = _UI_ABS(dy);
        sdx = guiSgn(dx);
        sdy = guiSgn(dy);
        x = dyabs >> 1;
        y = dxabs >> 1;
        px = x1;
        py = y1;

        /* the line is more horizontal than vertical */
        if(dxabs >= dyabs) {
            for(i = 0; i < dxabs; i++){
                y += dyabs;
                if(y >= dxabs){
                    y -= dxabs;
                    py += sdy;
                }
                px += sdx;

                /* draw this point */
                dc->engine->drawPoint(dc, px, py);
            }
        }
        else{               /* the line is more vertical than horizontal */
            for(i = 0; i < dyabs; i++){
                x += dxabs;
                if(x >= dyabs){
                    x -= dyabs;
                    px += sdx;
                }
                py += sdy;

                /* draw this point */
                dc->engine->drawPoint(dc, px, py);
            }
        }
    }
}

void DcDrawHorizontalLine(P_GuiDc dc, S32 x1, S32 x2, S32 y)
{
    GUI_COLOR color;

    if(dc==Co_NULL){
        return;
    }

    /* save old color */
    color = (struct dcHw *)dc->owner->gc->foreground;

    (struct dcHw *)dc->owner->gc->foreground = darkGrey;
    dc->engine->drawHline(dc, x1, x2, y);

    y++;

    (struct dcHw *)dc->owner->gc->foreground = highLight;
    dc->engine->drawHline(dc, x1, x2, y);

    /* restore color */
    (struct dcHw *)dc->owner->gc->foreground = color;
}

void DcDrawVerticalLine(P_GuiDc dc, S32 x, S32 y1, S32 y2)
{
    GUI_COLOR color;

    if(dc==Co_NULL){
        return;
    }

    /* save old color */
    color = (struct dcHw *)dc->owner->gc->foreground;

    (struct dcHw *)dc->owner->gc->foreground = darkGrey;
    dc->engine->drawVline(dc, x1, x2, y);

    y++;

    (struct dcHw *)dc->owner->gc->foreground = highLight;
    dc->engine->drawVline(dc, x1, x2, y);

    /* restore color */
    (struct dcHw *)dc->owner->gc->foreground = color;
}

void DcDrawRect(P_GuiDc dc, P_GuiRect rect)
{
    dc->engine->drawHline(dc, rect->x1, rect->x2, rect->y1);
    dc->engine->drawHline(dc, rect->x1, rect->x2, rect->y2 - 1);

    dc->engine->drawVline(dc, rect->x1, rect->y1, rect->y2);
    dc->engine->drawVline(dc, rect->x2 - 1, rect->y1, rect->y2);
}

void DcFillRectForecolor(P_GuiDc dc, P_GuiRect rect)
{
    GUI_COLOR saveColor;
    /*save the background color of dc*/
    saveColor = (struct dcHw *)dc->owner->gc->-background;
    /*set the background color to fore color*/
    (struct dcHw *)dc->owner->gc->background = (struct dcHw *)dc->owner->gc->foreground;
    dc->engine->fillRect(dc, rect);
    /*restore the background color of dc*/
    (struct dcHw *)dc->owner->gc->background = save_color;
}