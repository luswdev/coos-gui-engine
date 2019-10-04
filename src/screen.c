/**
 *******************************************************************************
 * @file       screen.c
 * @version    V0.1.1
 * @date       2019.10.4
 * @brief      This is a file to refresh screen.	
 *******************************************************************************
 */ 

#include <cogui.h>

S32 current_node_id   = 0;                      /*!< Record how much node have right now            */
cogui_screen_t *screen_list = Co_NULL;          /*!< The REAL screen list                           */

extern cogui_color_t default_background;        /*!< Default background uses to initial first node  */

/**
 *******************************************************************************
 * @brief      Initial screen list   
 * @param[in]  None
 * @param[out] None
 * @retval     None		 
 *
 * @par Description
 * @details    This function is used to initial a screen list to a header node
 *             and a full screen widget, and refresh screen currently.    
 *******************************************************************************
 */
void cogui_screen_list_init()
{
	cogui_app_t *server_app = cogui_get_server();
	cogui_widget_t *screen_wgt = cogui_widget_create();
    cogui_dc_t *dc = cogui_dc_begin_drawing(screen_wgt);
	
	cogui_widget_set_rectangle(screen_wgt, 0, 0, 240, 320);
	
    /* create header node */
    cogui_screen_t *screen_node = cogui_screen_node_create(Co_NULL); /* TODO: should create a widget for it */
    COGUI_ASSERT(screen_node != Co_NULL);

    /* let screen list be the header node */
    screen_list = screen_node;
    COGUI_SCREEN_NODE_HEADER(screen_list);
    COGUI_GET_LIST_NEXT(screen_list) =  COGUI_GET_LIST_PREV(screen_list) = COGUI_LIST(screen_list);

    /* first object should be a fill screen */
    screen_node = cogui_screen_node_create(screen_wgt);
    COGUI_ASSERT(screen_node != Co_NULL);

    /* enabled it */
    COGUI_ENABLE_SCREEN_NODE(screen_node);

    /* set as a full screen rectangle */
    COGUI_SCREEN_NODE_TYPE_RECT(screen_node);
    COGUI_SCREEN_NODE_RECT(screen_node).x1 = 0;
    COGUI_SCREEN_NODE_RECT(screen_node).y1 = 0;
    COGUI_SCREEN_NODE_RECT(screen_node).x2 = COGUI_SCREEN_WIDTH - 1;
    COGUI_SCREEN_NODE_RECT(screen_node).y2 = COGUI_SCREEN_HEIGHT - 1;

    /* this node should be filled by background */
    COGUI_DC_FC(dc) = default_background;
    COGUI_FILLED_SCREEN_NODE(screen_node);

    /* insert this background into list */
    cogui_screen_list_insert(screen_node);
}

/**
 *******************************************************************************
 * @brief      create a screen node
 * @param[in]  *owner      the node's parent widget
 * @param[out] None
 * @retval     screen_node the node which we just create 
 *
 * @par Description
 * @details    This function is used to create a screen node which is belone
 *             by specific widget. 
 *******************************************************************************
 */
cogui_screen_t *cogui_screen_node_create(cogui_widget_t *owner)
{
    cogui_screen_t *screen_node;
	screen_node = cogui_malloc(sizeof(cogui_screen_t));

    if (screen_node == Co_NULL)
        return Co_NULL;
    
    /* give initial state to this node */
	COGUI_SCREEN_NODE_FLAG(screen_node) &= COGUI_SCREEN_NODE_FLAG_INIT;
    /* first hide this node */
    COGUI_DISABLE_SCREEN_NODE(screen_node);
    /* filled information into node */
    screen_node->node_id = current_node_id;
    screen_node->owner = owner;
    /* initial linked list */
    COGUI_GET_LIST_NEXT(screen_node) = COGUI_GET_LIST_PREV(screen_node) = Co_NULL;

    /* put this node into owner widget */
    owner->screen_node_id = current_node_id++;

    return screen_node;
}

/**
 *******************************************************************************
 * @brief      insert a screen node into screen list
 * @param[in]  *node    which node we should insert
 * @param[out] None
 * @retval     None 
 *
 * @par Description
 * @details    This function is used to insert a screen node into screen list
 *             and refresh screen currently.
 *******************************************************************************
 */
void cogui_screen_list_insert(cogui_screen_t *node)
{   
    COGUI_ASSERT(node != Co_NULL);

    /* double linked list operating */
    COGUI_GET_LIST_NEXT(node) = COGUI_LIST(screen_list);
    COGUI_GET_LIST_PREV(node) = COGUI_GET_LIST_PREV(screen_list);
    COGUI_GET_LIST_NEXT((cogui_screen_t *)COGUI_GET_LIST_PREV(screen_list)) = COGUI_LIST(node);
    COGUI_GET_LIST_PREV(screen_list) = COGUI_LIST(node);

    /* after inserted, refresh screen */
    cogui_screen_refresh();
}

/**
 *******************************************************************************
 * @brief      pop out a screen node from screen list
 * @param[in]  id       which node we should pop
 * @param[out] None
 * @retval     None 
 *
 * @par Description
 * @details    This function is used to pop out a screen node from screen list
 *             and not delete it right now. 
 *******************************************************************************
 */
void cogui_screen_list_pop(co_uint32_t id)
{
    cogui_screen_t *screen_node;
    /* recursive from first node */
    screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_list);

    while (screen_node != screen_list) {
        /* find the corrent one, pop it */
        if (COGUI_SCREEN_NODE_ID(screen_node) == id) {
            cogui_screen_t *prev_node = (cogui_screen_t *)COGUI_GET_LIST_PREV(screen_node);
            cogui_screen_t *next_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);

            COGUI_GET_LIST_NEXT(prev_node) = COGUI_LIST(next_node);
            COGUI_GET_LIST_PREV(next_node) = COGUI_LIST(prev_node);
            break;
        }

        /* or move to next one */
        screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);
    }

    /* after pop function, refresh screen */
    cogui_screen_refresh();
}

/**
 *******************************************************************************
 * @brief      remove a screen node from screen list
 * @param[in]  id which node we should remove
 * @param[out] None
 * @retval     None 
 *
 * @par Description
 * @details    This function is used to remove a screen node from screen list
 *             and DELETE it right now. 
 *******************************************************************************
 */
void cogui_screen_list_remove(co_uint32_t id)
{
    cogui_screen_t *screen_node;
    /* recursive from first node */
    screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_list);

    while (screen_node != screen_list) {
        /* find the corrent one, pop it */
        if (COGUI_SCREEN_NODE_ID(screen_node) == id) {
            cogui_screen_t *prev_node = (cogui_screen_t *)COGUI_GET_LIST_PREV(screen_node);
            cogui_screen_t *next_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);

            COGUI_GET_LIST_NEXT(prev_node) = COGUI_LIST(next_node);
            COGUI_GET_LIST_PREV(next_node) = COGUI_LIST(prev_node);

            /* now we can totally remove it */
            cogui_free(screen_node);
            break;
        }

        /* or move to next one */
        screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);
    }

    /* after remove function, refresh screen */
    cogui_screen_refresh();
}

/**
 *******************************************************************************
 * @brief      find a node from id
 * @param[in]  id    which node we want to find
 * @param[out] None
 * @retval     screen_node the result we found
 * @retval     Co_NULL     or we did not find it
 *
 * @par Description
 * @details    This function is used to find a screen node from id
 *******************************************************************************
 */
cogui_screen_t *cogui_get_screen_node(co_uint32_t id)
{
    cogui_screen_t *screen_node;
    /* recursive from first node */
    screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_list);

    while (screen_node != screen_list) {
        /* find the corrent one, return it */
        if (COGUI_SCREEN_NODE_ID(screen_node) == id) {
            return screen_node;
        }

        /* or move to next one */
        screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);
    }

    return Co_NULL;
}

/**
 *******************************************************************************
 * @brief      update node information
 * @param[in]  id               which node we should update
 * @param[in]  *update_data     all we need to update's data
 * @param[out] None
 * @retval     None
 *
 * @par Description
 * @details    This function is used to update node information by giving a node
 *             contain updated data.
 *******************************************************************************
 */
void cogui_screen_node_update(co_uint32_t id, cogui_screen_t *update_data)
{
    cogui_screen_t *screen_node = cogui_get_screen_node(id);
    
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

    /* pop the node and insert to rear */
    cogui_screen_list_remove(id);
    cogui_screen_list_insert(screen_node);

    /* refresh screen */    
    cogui_screen_refresh();
}

/**
 *******************************************************************************
 * @brief      set node's rectangle 
 * @param[in]  *node     which node we should set
 * @param[in]  *rect     the rectangle to set
 * @param[out] None
 * @retval     None
 *
 * @par Description
 * @details    This function is used to set node's retangle  by giving a real
 *             rectangle.
 *******************************************************************************
 */
static void cogui_screen_node_set_rect(cogui_screen_t *node, cogui_rect_t *rect)
{
    COGUI_ASSERT(node != Co_NULL);
    COGUI_ASSERT(rect != Co_NULL);

    node->r = *rect;
}

/**
 *******************************************************************************
 * @brief      set node's rectangle 
 * @param[in]  *node     which node we should set
 * @param[in]  x         the coordinate x
 * @param[in]  y         the coordinate y
 * @param[in]  width     how width the rectangle is
 * @param[in]  height    how height the rectangle is
 * @param[out] None
 * @retval     None
 *
 * @par Description
 * @details    This function is used to set node's retangle by giving a pair
 *             of coordinate, width and height. 
 *******************************************************************************
 */
void cogui_screen_node_set_rectangle(cogui_screen_t *node, co_int32_t x, co_int32_t y, co_int32_t width, co_int32_t height)
{
    cogui_rect_t rect;

    rect.x1 = x;
    rect.y1 = y;

    rect.x2 = x + width;
    rect.y2 = y + height;
    
    /* call function above */
    cogui_screen_node_set_rect(node, &rect);
}

/**
 *******************************************************************************
 * @brief      refresh screen by list
 * @param[in]  None
 * @param[out] None
 * @retval     None
 *
 * @par Description
 * @details    This function is called to refresh screen by list.
 *******************************************************************************
 */
void cogui_screen_refresh()
{
    cogui_screen_t *screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_list);

    while (screen_node != screen_list) {
        /* if this node is disabled, skip it */
        if (!COGUI_SCREEN_NODE_IS_ENABLE(screen_node)){
            screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);
            continue;
        }

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

        /* go forward to next node */
        screen_node = (cogui_screen_t *)COGUI_GET_LIST_NEXT(screen_node);
    }
}
