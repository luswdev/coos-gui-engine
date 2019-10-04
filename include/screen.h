/**
 *******************************************************************************
 * @file       screen.h
 * @version    V0.1.0
 * @date       2019.9.29 
 * @brief      Screen lists header file.	
 *******************************************************************************
 */ 

#ifndef _COGUI_SCREEN_H
#define _COGUI_SCREEN_H
      
#define COGUI_SCREEN_NODE_RECT(n)           ((n)->r)                 /**< Get node's rectangle      */
#define COGUI_SCREEN_NODE_CIRCLE(n)         ((n)->c)                 /**< Get node's circle         */
#define COGUI_SCREEN_NODE_TRIANGLE(n)       ((n)->t)                 /**< Get node's triangle       */
#define COGUI_SCREEN_NODE_FLAG(n)           ((n)->flag)              /**< Get node's flag           */
#define COGUI_SCREEN_NODE_ID(n)             ((n)->node_id)           /**< Get node's id             */
#define COGUI_SCREEN_NODE_OWNER(n)          ((n)->owner)             /**< Get node's owner widget   */
#define COGUI_SCREEN_NODE_DC(n)             ((n)->owner->dc_engine)  /**< Get node's dc engine      */

/* screen node flag */
#define COGUI_SCREEN_NODE_FLAG_INIT         0x000       /**< The initial state flag     */
#define COGUI_SCREEN_NODE_FLAG_VAILD        0x001       /**< Node is vaild              */
#define COGUI_SCREEN_NODE_FLAG_FILLED       0x004       /**< Node is needed to filled   */
#define COGUI_SCREEN_NODE_FLAG_SHAPE_MASK   0x038       /**< B(0011 1000)               */
#define COGUI_SCREEN_NODE_FLAG_RECT         0x008       /**< Node is rectangle          */
#define COGUI_SCREEN_NODE_FLAG_CIRCLE       0x010       /**< Node is circle             */
#define COGUI_SCREEN_NODE_FLAG_TRIANGLE     0x020       /**< Node is triangle           */
#define COGUI_SCREEN_NODE_FLAG_HEADER       0x040       /**< It is header node          */

/* enable flag block */
#define COGUI_ENABLE_SCREEN_NODE(n)         COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_VAILD
#define COGUI_DISABLE_SCREEN_NODE(n)        COGUI_SCREEN_NODE_FLAG(n) &= ~COGUI_SCREEN_NODE_FLAG_VAILD
#define COGUI_SCREEN_NODE_IS_ENABLE(n)      (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_VAILD)

/* filled flag block */
#define COGUI_FILLED_SCREEN_NODE(n)         COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_FILLED
#define COGUI_UNFILLED_SCREEN_NODE(n)       COGUI_SCREEN_NODE_FLAG(n) &= ~COGUI_SCREEN_NODE_FLAG_FILLED
#define COGUI_SCREEN_NODE_IS_FILLED(n)      (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_FILLED)

/* shape type flag block */
#define COGUI_SCREEN_NODE_TYPE_RESET(n)     COGUI_SCREEN_NODE_FLAG(n) &= ~COGUI_SCREEN_NODE_FLAG_SHAPE_MASK
#define COGUI_SCREEN_NODE_TYPE_RECT(n)      COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_RECT
#define COGUI_SCREEN_NODE_TYPE_CIRCLE(n)    COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_CIRCLE
#define COGUI_SCREEN_NODE_TYPE_TRIANGLE(n)  COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_TRIANGLE
#define COGUI_SCREEN_NODE_IS_RECT(n)        (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_RECT)
#define COGUI_SCREEN_NODE_IS_CIRCLE(n)      (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_CIRCLE)
#define COGUI_SCREEN_NODE_IS_TRIANGLE(n)    (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_TRIANGLE)

/* header flag block */
#define COGUI_SCREEN_NODE_HEADER(n)         COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_HEADER
#define COGUI_SCREEN_NODE_IS_HEADER(n)      (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_HEADER)

/**
 * @struct   cogui_screen screen.h	
 * @brief    screen list struct
 * @details  This struct use to refresh screen node.
 */
struct cogui_screen {
    /* screen shape */
    cogui_rect_t        r;                          /**< Screen node shape type: rectangle   */
    //struct circle     c;                          /**< Screen node shape type: circle      */
    //struct triangle   t;                          /**< Screen node shape type: triangle    */

    /* node information */
    co_uint32_t         flag;                       /**< Screen node flag                    */
    co_uint32_t         node_id;                    /**< Screen node id                      */
    cogui_widget_t      *owner;                     /**< Screen node owner                   */

    /* double linked list */
    cogui_list_t        list;                       /**< Screen node list                    */
};
typedef struct cogui_screen cogui_screen_t;

/* for screen list */
void cogui_screen_list_init(void);
void cogui_screen_refresh(void);

/* screen list operation function */
void cogui_screen_node_delete(cogui_screen_t *node);
void cogui_screen_list_insert(cogui_screen_t *node);
void cogui_screen_list_remove(co_uint32_t id);
void cogui_screen_list_pop(co_uint32_t id);

/* screen node operation function */
cogui_screen_t *cogui_screen_node_create(cogui_widget_t *owner);
void cogui_screen_node_update(co_uint32_t id, cogui_screen_t *update_data);
void cogui_screen_node_set_rect(cogui_screen_t *node, cogui_rect_t *rect);

cogui_screen_t *cogui_get_screen_node(co_uint32_t id);

#endif /* _COGUI_SCREEN_H */
