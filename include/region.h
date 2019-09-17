/**
 *******************************************************************************
 * @file       region.h
 * @version    V0.0.1   
 * @date       2019.8.10
 * @brief      This is a file for GUI region.	
 *******************************************************************************
 */ 

#ifndef _COGUI_REGION_H
#define _COGUI_REGION_H

#include <coocox.h>
#include "cogui.h"

#define free_region_data(reg)               \
    if((reg)->data && (reg)->data->size)    \
        cogui_free((reg)->data);            \

enum cogui_region_status
{
    COGUI_REGION_STATUS_SUCCESS,
    COGUI_REGION_STATUS_FAILURE
};

void cogui_region_init(cogui_region_t *region);
void cogui_region_init_rect(cogui_region_t *region, S32 x, S32 y, U32 width, U32 height);
void cogui_region_init_extent(cogui_region_t *region, const cogui_rect_t *extent);
void cogui_region_fini(cogui_region_t *region);

enum cogui_region_status cogui_region_copy(cogui_region_t *dest, cogui_region_t *src);

void cogui_rect_inflate(cogui_rect_t *rect, S32 d);


#endif /* _COGUI_REGION_H */
