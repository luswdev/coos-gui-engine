/**
 *******************************************************************************
 * @file       GuiRegion.h
 * @version    V0.0.1   
 * @date       2019.5.27
 * @brief      This is a file for GUI region.	
 *******************************************************************************
 */ 

#ifndef _GUI_REGION_H
#define _GUI_REGION_H

/*---------------------------- structure -------------------------------------*/
typedef struct regionData
{
    U32 size;
    U32 nubRects;

}GuiRegionData,*P_GuiRegionData;

typedef struct region
{
    GuiRect extent;

    P_GuiRegionData data;

}GuiRegion,*P_GuiRegion;

/* true iff Box r1 contains Box r2 */
#define SUBSUMES(r1,r2) \
      ( ((r1)->x1 <= (r2)->x1) && \
        ((r1)->x2 >= (r2)->x2) && \
        ((r1)->y1 <= (r2)->y1) && \
        ((r1)->y2 >= (r2)->y2) )

#define GUI_MIN(a,b) ((a) < (b) ? (a) : (b))
#define GUI_MAX(a,b) ((a) > (b) ? (a) : (b))

/*---------------------------- Error Codes   ---------------------------------*/
#define GUI_REGION_STATUS_FAILURE (StatusType)24
#define GUI_REGION_STATUS_SUCCESS (StatusType)25

/*---------------------------- Function Define -------------------------------*/
StatusType RegionCopy(P_GuiRegion dest, P_GuiRegion source);

void RectIntersect(P_GuiRect src, P_GuiRect dest);

StatusType RegionUnion(P_GuiRegion newReg, P_GuiRegion reg1, P_GuiRegion reg2);

void RegionInitWithExtents(P_GuiRegion region, const P_GuiRect extents);

#endif /* _GUI_REGION_H */