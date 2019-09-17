/**
 *******************************************************************************
 * @file       region.c
 * @version    V0.0.1   
 * @date       2019.8.10
 * @brief      This is a file for GUI region.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"

static cogui_region_data_t cogui_region_empty_data = {0, 0};
static cogui_region_data_t cogui_broken_data = {0, 0};

cogui_rect_t cogui_empty_rect = {0, 0, 0, 0};
cogui_point_t cogui_empty_point = {0, 0};

void cogui_region_init(cogui_region_t *region)
{
    region->extent = cogui_empty_rect;
    region->data   = &cogui_region_empty_data;
}

void cogui_region_init_rect(cogui_region_t *region, S32 x, S32 y, U32 width, U32 height)
{
    region->extent.x1 = x;
    region->extent.y1 = y;
    region->extent.x2 = x + width;
    region->extent.y2 = y + height;
    region->data      = Co_NULL;
}

void cogui_region_init_extent(cogui_region_t *region, const cogui_rect_t *extent)
{
    region->extent = *extent;
    region->data   = Co_NULL;
}

void cogui_region_fini(cogui_region_t *region)
{
    COGUI_ASSERT(region != Co_NULL);

    free_region_data(region);
}

static enum cogui_region_status cogui_region_break(cogui_region_t *region)
{
    free_region_data(region);
    
    region->extent = cogui_empty_rect;
    region->data   = &cogui_broken_data;

    return COGUI_REGION_STATUS_FAILURE;
}

enum cogui_region_status cogui_region_copy(cogui_region_t *dest, cogui_region_t *src)
{
    COGUI_ASSERT(src);
    COGUI_ASSERT(dest);

    if (dest == src)
        return COGUI_REGION_STATUS_SUCCESS;

    dest->extent = src->extent;
    if (!src->data || !src->data->size) {
        free_region_data(dest);
        dest->data = src->data;
        return COGUI_REGION_STATUS_SUCCESS;
    }

    if (!dest->data || (dest->data->size < src->data->num_rects)) {
        free_region_data(dest);

        dest->data = cogui_malloc(sizeof(cogui_region_t) + (src->data->num_rects)*sizeof(cogui_rect_t));
        if (!dest->data)
            return cogui_region_break(dest);

        dest->data->size = src->data->num_rects;
    }
    
    dest->data->num_rects = src->data->num_rects;
    //memmove

    return COGUI_REGION_STATUS_SUCCESS;
}

void cogui_rect_inflate(cogui_rect_t *rect, S32 d)
{
    rect->x1 -= d;
    rect->x2 += d;
    rect->y1 -= d;
    rect->y2 += d;
}
