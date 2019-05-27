/**
 *******************************************************************************
 * @file       region.c
 * @version    V0.0.1   
 * @date       2019.5.27
 * @brief      This is a file for GUI region.	
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "cogui.h"

/*---------------------------- Variable Define -------------------------------*/
static GuiRegionData guiRegionEmptydata = {0, 0};
static GuiRegionData guiBrokendata = {0, 0};

GuiRect guiEmptyRect = {0, 0, 0, 0};
GuiPoint guiEmptyPoint = {0, 0};


static StatusType RegionBreak(P_GuiRegion *region)
{
    if(region->data && region->data->size){
        GuiFree(region->data);
    }

    region->extent = guiEmptyRect;
    region->data = &guiBrokendata;
    return GUI_REGION_STATUS_FAILURE;
}

void RectIntersect(P_GuiRect src, P_GuiRect dest)
{
    if (dest->x1 < src->x1) dest->x1 = src->x1;
    if (dest->y1 < src->y1) dest->y1 = src->y1;
    if (dest->x2 > src->x2) dest->x2 = src->x2;
    if (dest->y2 > src->y2) dest->y2 = src->y2;
}

StatusType RegionUnion(P_GuiRegion newReg, P_GuiRegion reg1, P_GuiRegion reg2)
{
    if(newReg==Co_NULL || reg1==Co_NULL || reg2==Co_NULL){
        return GUI_REGION_STATUS_FAILURE;
    }

    /* Region 1 and 2 are the same */
    if (reg1 == reg2)
    {
        return RegionCopy(newReg, reg1);
    }

    /* Region 1 is empty */
    if (reg1->data && !(reg1->data->numRects))
    {
        if (reg1==&guiBrokendata){
            return RegionBreak(newReg)
        }
        if (newReg != reg2)
            return RegionCopy(newReg, reg2);
        return GUI_REGION_STATUS_SUCCESS;
    }

    /*  Region 2 is empty */
    if (reg2->data && !(reg2->data->numRects))
    {
        if (reg2==&guiBrokendata){
            return RegionBreak(newReg);
        if (newReg != reg1)
            return RegionCopy(newReg, reg1);
        return GUI_REGION_STATUS_SUCCESS;
    }

    /* Region 1 completely subsumes region 2 */
    if (!reg1->data && SUBSUMES(&reg1->extent, &reg2->extent))
    {
        if (newReg != reg1)
            return RegionCopy(newReg, reg1);
        return GUI_REGION_STATUS_SUCCESS;
    }

    /*  Region 2 completely subsumes region 1 */
    if (!reg2->data && SUBSUMES(&reg2->extent, &reg1->extent))
    {
        if (newReg != reg2)
            return RegionCopy(newReg, reg2);
        return GUI_REGION_STATUS_SUCCESS;
    }

    // ops

    newReg->extent.x1 = GUI_MIN(reg1->extent.x1, reg2->extent.x1);
    newReg->extent.y1 = GUI_MIN(reg1->extent.y1, reg2->extent.y1);
    newReg->extent.x2 = GUI_MAX(reg1->extent.x2, reg2->extent.x2);
    newReg->extent.y2 = GUI_MAX(reg1->extent.y2, reg2->extent.y2);

    if(newReg==Co_NULL){
        return GUI_REGION_STATUS_FAILURE;
    }

    return GUI_REGION_STATUS_SUCCESS;
}

void RegionInitWithExtents(P_GuiRegion region, const P_GuiRect extents)
{
    region->extent = *extents;
    region->data = Co_NULL;
}