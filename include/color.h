/**
 *******************************************************************************
 * @file       color.h
 * @version    V0.0.1  
 * @date       2019.8.13
 * @brief      This is a color definition file for gui engine.
 *******************************************************************************
 */ 

#ifndef _COGUI_COLOR_H
#define _COGUI_COLOR_H

typedef co_int64_t cogui_color_t;

#define COGUI_USING_RGB565
//#define COGUI_USING_BGR565
//#define COGUI_USING_RGB888
//#define COGUI_USING_ARGB8888
//#define COGUI_USING_RGBA8888
//#define COGUI_USING_ABGR8888

#define COGUI_RGB565(r,g,b)     ((cogui_color_t)((((r)>>3)<<11)|(((g)>>2)<<5)|((b)>>3)))
#define COGUI_BGR565(b,g,r)     ((cogui_color_t)((((b)>>3)<<11)|(((g)>>2)<<5)|((r)>>3)))
#define COGUI_RGB888(r,g,b)     ((cogui_color_t)(((r)<<16)|((g)<<8)|(b)))
#define COGUI_ARGB8888(a,r,g,b) ((cogui_color_t)(((a)<<24)|((r)<<16)|((g)<<8)|(b)))
#define COGUI_RGBA8888(r,g,b,a) ((cogui_color_t)(((r)<<24)|((g)<<16)|((b)<<8)|(a)))
#define COGUI_ABGR8888(a,b,g,r) ((cogui_color_t)(((a)<<24)|((b)<<16)|((g)<<8)|(r)))

#ifdef COGUI_USING_RGB565
#define COGUI_RGB(r,g,b) COGUI_RGB565((r),(g),(b))
#endif

#ifdef COGUI_USING_BGR565
#define COGUI_RGB(r,g,b) COGUI_BGR565((b),(g),(r))
#endif

#ifdef COGUI_USING_RGB888
#define COGUI_RGB(r,g,b) COGUI_RGB565((r),(g),(b))
#endif

#ifdef COGUI_USING_ARGB8888
#define COGUI_RGB(r,g,b) COGUI_ARGB8888(255,(r),(g),(b))
#endif

#ifdef COGUI_USING_RGBA8888
#define COGUI_RGB(r,g,b) COGUI_RGB565((r),(g),(b), 255)
#endif

#ifdef COGUI_USING_ABGR8888
#define COGUI_RGB(r,g,b) COGUI_ABGR8888(255,(b),(g),(r))
#endif


#define COGUI_RED               COGUI_RGB(0xc6, 0x28, 0x28)
#define COGUI_GREEN             COGUI_RGB(0x38, 0x8e, 0x3c)
#define COGUI_BLUE              COGUI_RGB(0x02, 0x77, 0xbd)
#define COGUI_YELLOW            COGUI_RGB(0xfb, 0xc0, 0x2d)
#define COGUI_PURPLE            COGUI_RGB(0x51, 0x35, 0xb1)
#define COGUI_CYAN              COGUI_RGB(0x26, 0xc6, 0xda)
#define COGUI_HIGH_LIGHT        COGUI_RGB(0xf5, 0xf5, 0xf5)
#define COGUI_LIGHT_GRAY        COGUI_RGB(0x9e, 0x9e, 0x9e)
#define COGUI_DARK_GRAY         COGUI_RGB(0x42, 0x42, 0x42)
#define COGUI_WHITE             COGUI_RGB(0xff, 0xff, 0xff)
#define COGUI_BLACK             COGUI_RGB(0x00, 0x00, 0x00)

#endif /* _COGUI_COLOR_H */
