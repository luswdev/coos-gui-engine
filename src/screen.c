/**
 *******************************************************************************
 * @file       screen.c
 * @version    V0.0.1
 * @date       2019.9.17
 * @brief      This is a file for refresh screen.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"
#include "../include/screen.h"

S32 current_widget_id   = 0;
cogui_screen_t *screen_list = NULL;

extern cogui_color_t default_background;

void cogui_screen_list_init()
{
	cogui_app_t *server_app = cogui_get_server();
	cogui_widget_t *screen_wgt = cogui_widget_create();
    cogui_dc_t *dc = cogui_dc_begin_drawing(screen_wgt);
	
	cogui_widget_set_rectangle(screen_wgt, 0, 0, 240, 320);
	

    /* create header node */
    cogui_screen_t *screen_node = cogui_screen_node_create(Co_NULL, Co_NULL); /* TODO: should create a widget for it */
    COGUI_ASSERT(screen_node != Co_NULL);

    screen_list = screen_node;
    COGUI_SCREEN_NODE_HEADER(screen_list);
    COGUI_GET_LIST_NEXT(screen_list) =  COGUI_GET_LIST_PREV(screen_list) = COGUI_LIST(screen_list);

    /* first object should be a fill screen */
    screen_node = cogui_screen_node_create(Co_NULL, dc);
    COGUI_ASSERT(screen_node != Co_NULL);

    COGUI_ENABLE_SCREEN_NODE(screen_node);

    /* set as rectangle */
    COGUI_SCREEN_NODE_TYPE_RECT(screen_node);

    COGUI_SCREEN_NODE_RECT(screen_node).x1 = 0;
    COGUI_SCREEN_NODE_RECT(screen_node).y1 = 0;
    COGUI_SCREEN_NODE_RECT(screen_node).x2 = COGUI_SCREEN_WIDTH - 1;
    COGUI_SCREEN_NODE_RECT(screen_node).y2 = COGUI_SCREEN_HEIGHT - 1;

    /* this is a full screen background */
    COGUI_SCREEN_NODE_SET_COLOR(screen_node, default_background);
    COGUI_FILLED_SCREEN_NODE(screen_node);

    /* insert this background into list */
    cogui_screen_list_insert(screen_node);
}

cogui_screen_t *cogui_screen_node_create(cogui_widget_t *owner, cogui_dc_t *dc)
{
    cogui_screen_t *screen_node;
	screen_node = cogui_malloc(sizeof(cogui_screen_t));

    if (screen_node == Co_NULL){
		printf("malloc failed!\r\n");
        return Co_NULL;
	}
    
	COGUI_SCREEN_NODE_FLAG(screen_node)&=0x0;
    COGUI_DISABLE_SCREEN_NODE(screen_node);
    screen_node->node_id = current_widget_id;
    screen_node->owner = owner;
    COGUI_SCREEN_NODE_DC(screen_node) = dc;
    COGUI_GET_LIST_NEXT(screen_node) = COGUI_GET_LIST_PREV(screen_node) = NULL;

    owner->screen_node_id = current_widget_id++;

    return screen_node;
}

void cogui_screen_list_insert(cogui_screen_t *node)
{   
    COGUI_ASSERT(node != Co_NULL);

    COGUI_GET_LIST_NEXT(node) = COGUI_LIST(screen_list);
    COGUI_GET_LIST_PREV(node) = COGUI_GET_LIST_PREV(screen_list);
    COGUI_GET_LIST_NEXT((cogui_screen_t *)COGUI_GET_LIST_PREV(screen_list)) = COGUI_LIST(node);
    COGUI_GET_LIST_PREV(screen_list) = COGUI_LIST(node);

    /* if this node is disabled, enable it */
    if (!COGUI_SCREEN_NODE_IS_ENABLE(node)){
         COGUI_ENABLE_SCREEN_NODE(node);
    }

    cogui_screen_refresh();
}

void cogui_screen_list_pop(S32 id)
{
    cogui_screen_t *screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_list);

    while (screen_node != screen_list) {
        if (COGUI_SCREEN_NODE_ID(screen_node) == id) {
            cogui_screen_t *prev_node = (cogui_screen_t *)COGUI_GET_LIST_PREV(screen_node);
            cogui_screen_t *next_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);

            COGUI_GET_LIST_NEXT(prev_node) = COGUI_LIST(next_node);
            COGUI_GET_LIST_PREV(next_node) = COGUI_LIST(prev_node);
            break;
        }

        screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);
    }

    cogui_screen_refresh();
}

void cogui_screen_list_remove(S32 id)
{
    cogui_screen_t *screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_list);

    while (screen_node != screen_list) {
        if (COGUI_SCREEN_NODE_ID(screen_node) == id) {
            cogui_screen_t *prev_node = (cogui_screen_t *)COGUI_GET_LIST_PREV(screen_node);
            cogui_screen_t *next_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);

            COGUI_GET_LIST_NEXT(prev_node) = COGUI_LIST(next_node);
            COGUI_GET_LIST_PREV(next_node) = COGUI_LIST(prev_node);

            cogui_free(screen_node);
            break;
        }

        screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);
    }

    cogui_screen_refresh();
}

cogui_screen_t *cogui_get_screen_node(S32 id)
{
    cogui_screen_t *screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_list);

    while (screen_node != screen_list) {
        if (COGUI_SCREEN_NODE_ID(screen_node) == id) {
            return screen_node;
        }

        screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);
    }

    return Co_NULL;
}

void cogui_screen_node_update(S32 id, cogui_screen_t *update_data)
{
    cogui_screen_t *screen_node = cogui_get_screen_node(id);

    /* update color if need */
    if (screen_node->color != update_data->color) {
        COGUI_SCREEN_NODE_COLOR(screen_node) = COGUI_SCREEN_NODE_COLOR(update_data);
    }
    
    /* update shape if need */
    if (COGUI_SCREEN_NODE_IS_RECT(screen_node)) {
        COGUI_SCREEN_NODE_RECT(screen_node) = COGUI_SCREEN_NODE_RECT(update_data);
    }
    else if (COGUI_SCREEN_NODE_IS_CIRCLE(screen_node)) {
        //COGUI_SCREEN_NODE_CIRCLE(screen_node) = COGUI_SCREEN_NODE_CIRCLE(update_data);
    }
    else if (COGUI_SCREEN_NODE_IS_TRIANGLE(screen_node)) {
        //COGUI_SCREEN_NODE_TRIANGLE(screen_node)  = COGUI_SCREEN_NODE_TRIANGLE(update_data);
    }

    /* if this node is disabled, enable it */
    if (!COGUI_SCREEN_NODE_IS_ENABLE(screen_node)){
         COGUI_ENABLE_SCREEN_NODE(screen_node);
    }

    /* pop the node and insert to rear */
    cogui_screen_list_remove(id);
    cogui_screen_list_insert(screen_node);

    cogui_screen_refresh();
}

void cogui_screen_node_set_rect(cogui_screen_t *node, cogui_rect_t *rect)
{
    COGUI_ASSERT(node != Co_NULL);
    COGUI_ASSERT(rect != Co_NULL);

    node->r = *rect;
}

void cogui_screen_node_set_rectangle(cogui_screen_t *node, S32 x, S32 y, S32 width, S32 height)
{
    cogui_rect_t rect;

    rect.x1 = x;
    rect.y1 = y;

    rect.x2 = x + width;
    rect.y2 = y + height;

    cogui_screen_node_set_rect(node, &rect);
}

void cogui_screen_refresh()
{
    cogui_screen_t *screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_list);

    while (screen_node != screen_list) {
        /* if this node is disabled, skip it */
        if (!COGUI_SCREEN_NODE_IS_ENABLE(screen_node)){
            screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);
            continue;
        }
        
        /* first, change foreground color */
        cogui_color_t save_color = COGUI_DC_FC(COGUI_SCREEN_NODE_DC(screen_node));
        COGUI_DC_FC(COGUI_SCREEN_NODE_DC(screen_node)) = COGUI_SCREEN_NODE_COLOR(screen_node);

        /* draw by different shape */
        if (COGUI_SCREEN_NODE_IS_RECT(screen_node)) {
            if (COGUI_SCREEN_NODE_IS_FILLED(screen_node)) {
                cogui_dc_fill_rect_forecolor(COGUI_SCREEN_NODE_DC(screen_node), &COGUI_SCREEN_NODE_RECT(screen_node));
			}
            else {
                cogui_dc_draw_rect(COGUI_SCREEN_NODE_DC(screen_node), &COGUI_SCREEN_NODE_RECT(screen_node));
            }
        }
        else if (COGUI_SCREEN_NODE_IS_CIRCLE(screen_node)) {

        }
        else if (COGUI_SCREEN_NODE_IS_TRIANGLE(screen_node)) {

        }

        /* restore foreground color */
        COGUI_DC_FC(COGUI_SCREEN_NODE_DC(screen_node)) = save_color;
        screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);
    }
}
