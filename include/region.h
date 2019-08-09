/**
 *******************************************************************************
 * @file       region.h
 * @version    V0.0.1   
 * @date       2019.5.27
 * @brief      This is a file for GUI region.	
 *******************************************************************************
 */ 

#ifndef _COGUI_REGION_H
#define _COGUI_REGION_H

#include <coocox.h>
#include "cogui.h"

/* true iff Box r1 contains Box r2 */
#define SUBSUMES(r1,r2) \
      ( ((r1)->x1 <= (r2)->x1) && \
        ((r1)->x2 >= (r2)->x2) && \
        ((r1)->y1 <= (r2)->y1) && \
        ((r1)->y2 >= (r2)->y2) )

#define GUI_MIN(a,b) ((a) < (b) ? (a) : (b))
#define GUI_MAX(a,b) ((a) > (b) ? (a) : (b))

/*---------------------------- Function Define -------------------------------*/
static StatusType RegionBreak(cogui_region_t *region);
StatusType RegionCopy(cogui_region_t *dest, cogui_region_t *src);

void RegionInitWithExtents(cogui_region_t *region, cogui_rect_t *extents);

void RegionReset(cogui_region_t *region, cogui_rect_t *rect);

void RectIntersect(cogui_rect_t *src, cogui_rect_t *dest);
StatusType RegionIntersectRect(cogui_region_t *newReg,cogui_region_t *reg1, cogui_rect_t *rect);

StatusType RegionUnion(cogui_region_t *newReg, cogui_region_t *reg1, cogui_region_t *reg2);

StatusType RegionSubtract(cogui_region_t *regD, cogui_region_t *regM, cogui_region_t *regS);
StatusType RegionSubtractRect(cogui_region_t *regD, cogui_region_t *regM, cogui_rect_t *rect);

void RectMove(cogui_rect_t *rect, S32 x, S32 y);
void RectInflate(cogui_rect_t *rect, S32 d);

#endif /* _COGUI_REGION_H */
