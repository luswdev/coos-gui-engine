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

struct cogui_window;

/* for screen list */
cogui_widget_t *cogui_screen_list_init(struct cogui_window *top);
void cogui_screen_refresh(struct cogui_window *top);

/* screen list operation function */
void cogui_screen_list_insert(cogui_widget_t *node, struct cogui_window *top);
void cogui_screen_list_remove(co_uint32_t id, struct cogui_window *top);
cogui_widget_t *cogui_screen_list_pop(co_uint32_t id, struct cogui_window *top);

/* screen node operation function */

cogui_widget_t *cogui_get_screen_node(co_uint32_t id, struct cogui_window *top);

#endif /* _COGUI_SCREEN_H */
