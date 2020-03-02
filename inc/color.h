/**
 *******************************************************************************
 * @file       color.h
 * @version    V0.7.1
 * @date       2020.02.23
 * @brief      Color define header file.
 *******************************************************************************
 */ 

#ifndef __COGUI_COLOR_H__
#define __COGUI_COLOR_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t cogui_color_t;   /**< Color type belong to long integer */

/** Determine which color style used */
#define COGUI_USING_RGB565
//#define COGUI_USING_BGR565
//#define COGUI_USING_RGB888
//#define COGUI_USING_ARGB8888
//#define COGUI_USING_RGBA8888
//#define COGUI_USING_ABGR8888

/* RGB into integer by different style */
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

extern const cogui_color_t red;
extern const cogui_color_t orange;
extern const cogui_color_t green;
extern const cogui_color_t blue;
extern const cogui_color_t yellow;
extern const cogui_color_t indigo;
extern const cogui_color_t purple;
extern const cogui_color_t cyan;
extern const cogui_color_t high_light;
extern const cogui_color_t light_grey;
extern const cogui_color_t dark_grey;
extern const cogui_color_t white;
extern const cogui_color_t black;

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_COLOR_H__ */
