/**
 *******************************************************************************
 * @file       color.h
 * @version    V0.7.4
 * @date       2020.04.18
 * @brief      Color define header file.
 *******************************************************************************
 */ 

#ifndef __GUI_COLOR_H__
#define __GUI_COLOR_H__

#ifdef __cplusplus
extern "C" {
#endif

typedef uint64_t color_t;   /**< color type belong to unsigned long integer */

/** determine which color style used */
#define USING_RGB565
//#define USING_BGR565
//#define USING_RGB888
//#define USING_ARGB8888
//#define USING_RGBA8888
//#define USING_ABGR8888

/* RGB into integer by different style */
#define GUI_RGB565(r,g,b)     ((color_t)((((r)>>3)<<11)|(((g)>>2)<<5)|((b)>>3)))
#define GUI_BGR565(b,g,r)     ((color_t)((((b)>>3)<<11)|(((g)>>2)<<5)|((r)>>3)))
#define GUI_RGB888(r,g,b)     ((color_t)(((r)<<16)|((g)<<8)|(b)))
#define GUI_ARGB8888(a,r,g,b) ((color_t)(((a)<<24)|((r)<<16)|((g)<<8)|(b)))
#define GUI_RGBA8888(r,g,b,a) ((color_t)(((r)<<24)|((g)<<16)|((b)<<8)|(a)))
#define GUI_ABGR8888(a,b,g,r) ((color_t)(((a)<<24)|((b)<<16)|((g)<<8)|(r)))

#ifdef USING_RGB565
#define GUI_RGB(r,g,b) GUI_RGB565((r),(g),(b))
#endif

#ifdef USING_BGR565
#define GUI_RGB(r,g,b) GUI_BGR565((b),(g),(r))
#endif

#ifdef USING_RGB888
#define GUI_RGB(r,g,b) GUI_RGB565((r),(g),(b))
#endif

#ifdef USING_ARGB8888
#define GUI_RGB(r,g,b) GUI_ARGB8888(255,(r),(g),(b))
#endif

#ifdef USING_RGBA8888
#define GUI_RGB(r,g,b) GUI_RGB565((r),(g),(b), 255)
#endif

#ifdef USING_ABGR8888
#define GUI_RGB(r,g,b) GUI_ABGR8888(255,(b),(g),(r))
#endif

/* extern from color.c */
extern const color_t red;
extern const color_t orange;
extern const color_t green;
extern const color_t blue;
extern const color_t yellow;
extern const color_t indigo;
extern const color_t purple;
extern const color_t cyan;
extern const color_t high_light;
extern const color_t light_grey;
extern const color_t dark_grey;
extern const color_t white;
extern const color_t black;

#ifdef __cplusplus
}
#endif

#endif /* __GUI_COLOR_H__ */
