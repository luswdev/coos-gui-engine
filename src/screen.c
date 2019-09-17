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

void init_screen_list()
{
    cogui_app_t *server_app = cogui_get_server();

    /* create header node */
    cogui_screen_t *screen_node = init_screen_node(server_app);

    screen = screen_node;
    COGUI_SCREEN_NODE_HEADER(screen);

    /* first object should be a fill screen */
    screen_node = init_screen_node(server_app);

    COGUI_ENABLE_SCREEN_NODE(screen_node);

    /* set as rectangle */
    COGUI_SCREEN_NODE_TYPE_RECT(screen_node);

    screen_node->shape.r.x1 = 0;
    screen_node->shape.r.y1 = 0;
    screen_node->shape.r.x2 = COGUI_SCREEN_WIDTH - 1;
    screen_node->shape.r.y2 = COGUI_SCREEN_HEIGHT - 1;

    /* this is a full screen background */
    COGUI_SCREEN_NODE_SET_COLOR(screen_node, default_bg_color);
    COGUI_FILLED_SCREEN_NODE(screen_node);

    /* let header node point to first node */
    COGUI_GET_LIST_NEXT(screen) =  COGUI_GET_LIST_PREV(screen) = screen_node;
    /* let first node point to header */
    COGUI_GET_LIST_NEXT(screen_node) =  COGUI_GET_LIST_PREV(screen_node) = screen_node;

    dc_refresh();
}

cogui_screen_t *init_screen_node(cogui_app_t *owner)
{
    cogui_screen_t *screen_node
    screen_node = cogui_malloc(sizeof(struct cogui_screen));

    COGUI_DISABLE_SCREEN_NODE(screen_node);
    screen_node->node_id = current_widget_id++;
    screen_node->owner = owner;
    COGUI_GET_LIST_NEXT(screen_node) =  COGUI_GET_LIST_PREV(screen_node) = NULL;

    return screen_node;
}

void insert_screen_list(cogui_screen_t *node)
{
    struct cogui_screen *screen_node = screen->screen_list.next;

    
    while (screen_node != screen)
        screen_node->level++;
    
    node->screen_list.next = screen;
    node->screen_list.prev = screen->screen_list.prev;
    screen->screen_list.prev->screen_list.next = node;
    screen->screen_list.prev = node;

    dc_refresh();
}

void dc_refresh()
{
    struct cogui_screen *screen_node = screen->screen_list.next;

    while (screen_node != screen){
        if !(screen_node->vaild):
            continue;
        
        switch (screen_node->type){
            case screen_shape_rect:
                //draw_rect();

            case screen_shape_circle:
                //draw_circle();

            case screen_shape_triangle:
                //draw_triangle();
        }
        
        screen_node = screen_node->next;
    }
}