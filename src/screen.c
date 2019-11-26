/**
 *******************************************************************************
 * @file       screen.c
 * @version    V0.1.1
 * @date       2019.10.4
 * @brief      This is a file to refresh screen.	
 *******************************************************************************
 */ 

#include <cogui.h>

co_uint32_t current_node_id = 0;                   /*!< The REAL screen list                           */

extern cogui_color_t default_background;                /*!< Default background uses to initial first node  */
