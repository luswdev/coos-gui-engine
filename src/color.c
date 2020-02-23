/**
 *******************************************************************************
 * @file       color.c
 * @version    V0.7.0
 * @date       2020.02.22
 * @brief      This is a file for GUI engine's color.
 *******************************************************************************
 */ 

#include <cogui.h>

const cogui_color_t COGUI_RED          = COGUI_RGB(0xff, 0x00, 0x00);         /**< Default red color               */ 
const cogui_color_t COGUI_GREEN        = COGUI_RGB(0x00, 0xff, 0x00);         /**< Default green color             */ 
const cogui_color_t COGUI_BLUE         = COGUI_RGB(0x00, 0x00, 0xff);         /**< Default blue color              */ 
const cogui_color_t COGUI_YELLOW       = COGUI_RGB(0xff, 0xff, 0x00);         /**< Default yellow color            */ 
const cogui_color_t COGUI_PURPLE       = COGUI_RGB(0xff, 0x00, 0xff);         /**< Default purple color            */
const cogui_color_t COGUI_CYAN         = COGUI_RGB(0x00, 0xff, 0xff);         /**< Default cyan color              */ 
const cogui_color_t COGUI_HIGH_LIGHT   = COGUI_RGB(0xf5, 0xf5, 0xf5);         /**< Default high light color        */ 
const cogui_color_t COGUI_LIGHT_GRAY   = COGUI_RGB(0x9e, 0x9e, 0x9e);         /**< Default light gray color        */ 
const cogui_color_t COGUI_DARK_GRAY    = COGUI_RGB(0x42, 0x42, 0x42);         /**< Default dark gray color         */ 
const cogui_color_t COGUI_WHITE        = COGUI_RGB(0xff, 0xff, 0xff);         /**< Default white color             */ 
const cogui_color_t COGUI_BLACK        = COGUI_RGB(0x00, 0x00, 0x00);         /**< Default black color             */ 

const cogui_color_t default_foreground = COGUI_RGB(0xff, 0xff, 0xff);;        /**< Set default foreground to white */
const cogui_color_t default_background = COGUI_RGB(0x00, 0x00, 0x00);;        /**< Set default background to black */
