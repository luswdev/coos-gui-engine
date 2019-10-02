/**
 *******************************************************************************
 * @file       screen.h
 * @version    V0.1.0
 * @date       2019.9.29 
 * @brief      This is a file for refresh screen.	
 *******************************************************************************
 */ 

#ifndef _COGUI_SCREEN_H
#define _COGUI_SCREEN_H
      
#define COGUI_SCREEN_NODE_RECT(n)           ((n)->r)        
#define COGUI_SCREEN_NODE_CIRCLE(n)         ((n)->c)        
#define COGUI_SCREEN_NODE_TRIANGLE(n)       ((n)->t)      
#define COGUI_SCREEN_NODE_FLAG(n)           ((n)->flag)    
#define COGUI_SCREEN_NODE_ID(n)             ((n)->node_id)
#define COGUI_SCREEN_NODE_OWNER(n)          ((n)->owner)
#define COGUI_SCREEN_NODE_DC(n)             ((n)->owner->dc_engine)

/* screen node flag */
#define COGUI_SCREEN_NODE_FLAG_INIT         0x000
#define COGUI_SCREEN_NODE_FLAG_VAILD        0x001
#define COGUI_SCREEN_NODE_FLAG_FILLED       0x004
#define COGUI_SCREEN_NODE_FLAG_SHAPE_MASK   0x038    /* B0011 1000*/
#define COGUI_SCREEN_NODE_FLAG_RECT         0x008
#define COGUI_SCREEN_NODE_FLAG_CIRCLE       0x010
#define COGUI_SCREEN_NODE_FLAG_TRIANGLE     0x020
#define COGUI_SCREEN_NODE_FLAG_HEADER       0x040

#define COGUI_ENABLE_SCREEN_NODE(n)         COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_VAILD
#define COGUI_DISABLE_SCREEN_NODE(n)        COGUI_SCREEN_NODE_FLAG(n) &= ~COGUI_SCREEN_NODE_FLAG_VAILD
#define COGUI_SCREEN_NODE_IS_ENABLE(n)      (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_VAILD)

#define COGUI_FILLED_SCREEN_NODE(n)         COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_FILLED
#define COGUI_UNFILLED_SCREEN_NODE(n)       COGUI_SCREEN_NODE_FLAG(n) &= ~COGUI_SCREEN_NODE_FLAG_FILLED
#define COGUI_SCREEN_NODE_IS_FILLED(n)      (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_FILLED)

#define COGUI_SCREEN_NODE_TYPE_RESET(n)     COGUI_SCREEN_NODE_FLAG(n) &= ~COGUI_SCREEN_NODE_FLAG_SHAPE_MASK
#define COGUI_SCREEN_NODE_TYPE_RECT(n)      COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_RECT
#define COGUI_SCREEN_NODE_TYPE_CIRCLE(n)    COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_CIRCLE
#define COGUI_SCREEN_NODE_TYPE_TRIANGLE(n)  COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_TRIANGLE
#define COGUI_SCREEN_NODE_IS_RECT(n)        (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_RECT)
#define COGUI_SCREEN_NODE_IS_CIRCLE(n)      (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_CIRCLE)
#define COGUI_SCREEN_NODE_IS_TRIANGLE(n)    (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_TRIANGLE)

#define COGUI_SCREEN_NODE_HEADER(n)         COGUI_SCREEN_NODE_FLAG(n) |= COGUI_SCREEN_NODE_FLAG_HEADER
#define COGUI_SCREEN_NODE_IS_HEADER(n)      (COGUI_SCREEN_NODE_FLAG(n) & COGUI_SCREEN_NODE_FLAG_HEADER)


struct cogui_screen {
   cogui_rect_t     r;
   //struct circle   c;
   //struct triangle t;

    S32 flag;
    
    S32 node_id;
    cogui_widget_t *owner;

    cogui_list_t list;
};
typedef struct cogui_screen cogui_screen_t;

void cogui_screen_list_init(void);

cogui_screen_t *cogui_screen_node_create(cogui_widget_t *owner);
void cogui_screen_node_delete(cogui_screen_t *node);
void cogui_screen_list_insert(cogui_screen_t *node);
void cogui_screen_list_remove(S32 id);
void cogui_screen_list_pop(S32 id);

void cogui_screen_node_update(S32 id, cogui_screen_t *update_data);

void cogui_screen_node_set_rectangle(cogui_screen_t *node, S32 x, S32 y, S32 width, S32 height);
void cogui_screen_node_set_rect(cogui_screen_t *node, cogui_rect_t *rect);

cogui_screen_t *cogui_get_screen_node(S32 id);

void cogui_screen_refresh(void);

#endif /* _COGUI_SCREEN_H */
