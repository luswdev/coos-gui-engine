/**
 *******************************************************************************
 * @file       system.h
 * @version    V0.7.3
 * @date       2020.03.25
 * @brief      GUI engine system header file.	
 *******************************************************************************
 */ 

#ifndef __GUI_SYSTEM_H__
#define __GUI_SYSTEM_H__

#ifdef __cplusplus
extern "C" {
#endif

/* define some type variables */
typedef signed   char           bool_t;           /**< Boolean type                */

/* GUI engine status type */
#define GUI_E_ERROR            (StatusType)22       /**< occurred error status       */
#define GUI_E_OK               (StatusType)23       /**< everythings OK status       */
#define GUI_E_APP_NULL         (StatusType)24       /**< run null application status */
#define GUI_E_APP_FULL         (StatusType)25       /**< run null application status */

/* some math inline function */
#define ABS(x)             ((x)>=0? (x): -(x))      /**< simple abs function         */

/** assert function */
#define ASSERT(EX) 								\
if(!(EX)){											    \
	assert_handler(#EX, __FUNCTION__, __LINE__);	\
}													    \

/** initial a rectangle to zero */
#define GUI_INIT_RECT(r)              \
{                                       \
    (r)->x1 = 0;                        \
    (r)->x2 = 0;                        \
    (r)->y1 = 0;                        \
    (r)->y2 = 0;                        \
}    

/** setting a rectangle */
#define GUI_SET_RECT(r, x, y, w, h)   \
{                                       \
    (r)->x1 = (x);                      \
    (r)->x2 = (x) + (w);                \
    (r)->y1 = (y);                      \
    (r)->y2 = (y) + (h);                \
}                                       \

/** expand a rectangle */
#define GUI_RECT_EXPAND(r, d)           \
{                                       \
    (r)->x1 -= (d);                     \
    (r)->x2 += (d);                     \
    (r)->y1 -= (d);                     \
    (r)->y2 += (d);                     \
}                                       \

/** resize a rectangle with padding value */
#define GUI_RECT_PADDING(r, p)    \
{                                   \
    (r)->x1 += (p)>>8  & 0x0FF;     \
    (r)->x2 -= (p)     & 0x0FF;     \
    (r)->y1 += (p)>>24 & 0x0FF;     \
    (r)->y2 -= (p)>>16 & 0x0FF;     \
}                                   \

/* rectangle width and height */
#define GUI_RECT_WIDTH(r)         ((r)->x2-(r)->x1)
#define GUI_RECT_HEIGHT(r)        ((r)->y2-(r)->y1)

/* list previous and next node */
#define COGUI_LIST_PREV(l) ((l)->prev)
#define COGUI_LIST_NEXT(l) ((l)->next)

#define GUI_TOGGLE_BOOL(b) (b=~b)

/** return a new result type */
#define GUI_RETURN_TYPE(r)    \
    if ((r) == E_OK)            \
        return GUI_E_OK;        \
    else                        \
        return GUI_E_ERROR;     \

/**
 * @struct   cogui_list_node
 * @brief    Double linked list struct
 * @details  This struct is double linked list.
 */
struct list_node
{
    struct list_node *prev;
    struct list_node *next;
};
typedef struct list_node list_t;

/**
 * @struct   cogui_slist_node	
 * @brief    Single linked list struct
 * @details  This struct is single linked list.
 */
struct slist_node
{
    struct slist_node *next;
};
typedef struct slist_node slist_t;

/**
 * @struct   cogui_point
 * @brief    2D point struct
 * @details  This struct is 2D point.
 */
struct point
{
    int16_t x, y;
};
typedef struct point point_t;

/**
 * @struct   cogui_rect	
 * @brief    Rectangle struct
 * @details  This struct is rectangle.
 */
struct rect
{
    int16_t x1, x2, y1, y2;
};
typedef struct rect rect_t;

struct event;
struct app;
typedef struct app app_t;

void gui_system_init(void);

/* memory manange from CoOS */
void *gui_malloc(uint32_t size);
void gui_free(void* ptr);

/* sync function from CoOS */
StatusType gui_ack(struct event *event, StatusType status);
StatusType gui_send(app_t *app, struct event *event);
StatusType gui_send_sync(app_t *app, struct event *event);
StatusType gui_recv(OS_EventID mq, struct event *event, int32_t timeout);

/* math function for cogui */
uint64_t gui_pow(int32_t base, int32_t exp);
void gui_itoa(int16_t n, char* ss);

/* mem function for cogui */
void *gui_memset(void *buf, int val, uint64_t size);
void *gui_memcpy(void *dest, const void *src, uint64_t size);
void *gui_memmove(void *dest, const void *src, uint64_t size);
int32_t gui_memcmp(const void *str1, const void *str2, uint64_t size);

/* string function for cogui */
char *gui_strdup(const char *str);
uint64_t gui_strlen(const char *str);
uint64_t gui_strnlen(const char *str, uint64_t maxlen);
int32_t gui_strncmp(const char *str1, const char *str2, uint64_t size);
int32_t gui_strcmp(const char *str1, const char *str2);

/* debug function */
int gui_printf(const char *fmt, ...);
void assert_handler(const char *ex_string, const char *func, uint32_t line);

#ifdef __cplusplus
}
#endif

#endif /* __GUI_SYSTEM_H__ */
