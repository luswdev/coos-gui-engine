/**
 *******************************************************************************
 * @file       cogui_config.h
 * @version    V0.0.3
 * @date       2020.01.20
 * @brief      This is a file for some configuration
 *******************************************************************************
 */ 

#ifndef __COGUI_CONFIG_H__
#define __COGUI_CONFIG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "user_config.h"

/* screen parameter */
#define COGUI_SCREEN_WIDTH      240
#define COGUI_SCREEN_HEIGHT     320

/* 0 for hardware engine, 1 for buffer engine */
#define COGUI_SCREEN_TYPE       0

/* debug output (serial) */
#define COGUI_DEBUG_PRINT

#ifdef COGUI_DEBUG_PRINT
#define cogui_putchar(c)    stm_print_char((c))
#define cogui_putstr(s)     stm_print_string((s))
#endif /* COGUI_DEBUG_PRINT*/

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_CONFIG_H__ */
