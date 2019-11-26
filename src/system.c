/**
 *******************************************************************************
 * @file       system.c
 * @version    V0.1.3 
 * @date       2019.10.5
 * @brief      Some system function for GUI engine.	
 *******************************************************************************
 */ 

#include <cogui.h>
#include <stm32f4xx.h>      /* for UART setting */
#include <stdarg.h>         /* for va function  */

void cogui_system_init()
{
    cogui_printf("[%10s] Initial server...", "system");
    cogui_server_init();
    cogui_printf("[OK]\r\n");
}

void *cogui_malloc(U32 size)
{
    void *ptr;
    
    ptr = CoKmalloc(size);

#ifdef COGUI_DEBUG_PRINT
	if(ptr == Co_NULL){
		cogui_printf("[sys] out of memory\r\n");
	}
#endif
	
    return ptr;
}

void cogui_free(void* memBuf)
{
    CoKfree(memBuf);
}

StatusType cogui_ack(struct cogui_event *event, StatusType status)
{
    COGUI_ASSERT(event != Co_NULL);
    COGUI_ASSERT(event->ack);
		
    CoPostMail(event->ack, (void *)&status);

    return E_OK;
}

StatusType cogui_send(cogui_app_t *app, struct cogui_event *event)
{
    StatusType result;

    COGUI_ASSERT(event != Co_NULL);
    COGUI_ASSERT(app != Co_NULL);

    result = CoPostMail(app->mq, event);

    return result;
}

StatusType cogui_send_sync(cogui_app_t *app, struct cogui_event *event)
{
    StatusType result;

    COGUI_ASSERT(event != Co_NULL);
    COGUI_ASSERT(app != Co_NULL);

    OS_EventID mq = CoCreateMbox(EVENT_SORT_TYPE_FIFO);
	event->ack = mq;

    result = CoPostMail(app->mq, event);

    if (result != E_OK){
        CoDelMbox(mq, OPT_DEL_ANYWAY);
    }

    /* wait forever for server ack */
    event = CoPendMail(mq, 0, &result);

    CoDelMbox(mq, OPT_DEL_ANYWAY);
    return result;
}

static co_int32_t _cogui_get_event_size(struct cogui_event *event) {
    if (event->type <= COGUI_EVENT_APP_ACTIVATE) {
        return sizeof(struct cogui_event_app);
    }

    if (event->type <= COGUI_EVENT_MOUSE_BUTTON) {
        return sizeof(struct cogui_event_mouse);
    }

    if (event->type <= COGUI_EVENT_KBD) {
        return sizeof(struct cogui_event_kbd);
    }

    return sizeof(struct cogui_event);
}

StatusType cogui_recv(OS_EventID mq, struct cogui_event *event, co_int32_t timeout)
{
    StatusType result;
    cogui_app_t *app;
    struct cogui_event* buf;

    COGUI_ASSERT(event!=Co_NULL);

    app = cogui_app_self();
    if (app == Co_NULL) {
        return E_ERROR;
    }

    buf = (struct cogui_event *)CoPendMail(mq, timeout, &result);
    cogui_memcpy(event, buf, _cogui_get_event_size(buf));

    return result;
}



void *cogui_memset(void *s, int c, U64 cnt)
{
    char *ss = (char *)s;

    while (cnt--)
        *ss++ = c;

    return s;
}

void *cogui_memcpy(void *dest, const void *src, U64 cnt)
{
    char *tar = (char *)dest, *s = (char *)src;

    while (cnt--)
        *tar++ = *s++;

    return dest;    
}

void *cogui_memmove(void *dest, const void *src, U64 cnt)
{
    char *ds = (char *)dest, *ss = (char *)src;

    if (ss < ds && ds < ss + cnt) {
        ds += cnt;
        ss += cnt;

        while (cnt--)
            *(--ds) = *(--ss);
    }
    else {
        while (cnt--)
            *ds++ = *ss++;
    }

    return dest;
}

S32 cogui_memcmp(const void *str1, const void *str2, U64 cnt)
{
    const U8 *s1, *s2;
    int res = 0;

    for (s1 = str1, s2 = str2; cnt > 0; ++s1, ++s2, --cnt)
        if ((res = *s1 - *s2) != 0)
            break;
        
    return res;
}

char *cogui_strstr(const char *src, const char *tar)
{
    int ls, lt;

    lt = cogui_strlen(src);
    if (!lt)
        return (char *)src;

    ls = cogui_strlen(tar);
    while (ls >= lt) {
        ls--;
        if (!cogui_memcmp(src, tar, lt))
            return (char *)src;
        src++;
    }     

    return Co_NULL;
}

U64 cogui_strlen(const char *str)
{
    const char *s;

    for (s = str; *s != '\0'; ++s)
        ;
    
    return s - str;
}

char *cogui_strdup(const char *str)
{
    U64 len = cogui_strlen(str) + 1;
    char *tmp =  (char *)cogui_malloc(len);

    if (tmp == Co_NULL)
        return Co_NULL;

    cogui_memmove(tmp, str, len);

    return tmp;
}

S32 cogui_strncmp(const char *str1, const char *str2, U64 cnt)
{
    for (; *str1 && *str1 == *str2 && cnt; str1++, str2++, cnt--)
        ;

    return (*str1 - *str2);
}

S32 cogui_strcmp(const char *str1, const char *str2)
{
    for (; *str1 && *str1 == *str2; str1++, str2++)
        ;

    return (*str1 - *str2);
}


U64 cogui_pow(S32 x, S32 y)
{
    U64 sum = 1;

    while (y--)
        sum *= x;

    return sum;
}

void cogui_putchar(const char ch)
{
    USART1->DR = (uint8_t) ch;

	/* loop until the end of transmission */
    while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
}


void cogui_putstr(const char *str)
{   
    /* output character one by one */
    while (*str)
        cogui_putchar(*str++);
}


int cogui_printf(const char *str,...)
{
	va_list ap;
    int val,r_val,space=0;
	char count, ch;
	char *s = Co_NULL;
    int res = 0;

    //CoSchedLock();
    va_start(ap,str);
    while ('\0' != *str) { 
          switch (*str)
          {
            case '%':
                str++;
                while (*str >= '0' && *str <= '9') {
                    space *= 10;
                    space += *str - '0';
                    str++;
                }

                switch (*str) {

                    /* handle integer var */
                    case 'd':
                        val = va_arg(ap, int); 
 			            
                        /* if val is negative or zero */
                        if (val < 0) {
                            cogui_putchar('-');
                            val = 0 - val;
                        }
                        else if (val == 0) {
                            cogui_putchar('0');
                        }
                        
                        r_val = val; 
                        count = 0; 
						while (r_val) {
                            count++;
                            r_val /= 10;
                        }
						res += count;
                        r_val = val; 
                        while (count) { 
                            ch = r_val / cogui_pow(10,count - 1);
							r_val %= cogui_pow(10, count - 1);
							cogui_putchar(ch + '0');
							count--;
						}
                        break;

                    /* handle integer var with hex output */
                    case 'x':
                        val = va_arg(ap, int);

                        /* if val is negative or zero */
                        if (val<0) {
                            cogui_putchar('-');
                            val = 0 - val;
                        }
                        else if (val == 0) {
                            cogui_putchar('0');
                        }
                        
                        r_val = val; 
                        count = 0;
						while (r_val) {
                            count++;
                            r_val /= 16; 
                        }
                        res += count;
                        r_val = val; 
                        while(count) { 
                            ch = r_val / cogui_pow(16, count - 1);
							r_val %= cogui_pow(16, count - 1);
							if (ch <= 9)
                                cogui_putchar(ch + '0');
                            else
								cogui_putchar(ch - 10 + 'a');
							count--;
						}
						break;

                    /* handle string var */
                    case 's':
						s = va_arg(ap, char *);
                        
                        if (space) {
                            int len = cogui_strlen(s);
                            while (len < space) {
                                cogui_putchar(' ');
                                space --;
                            }
                        }

						cogui_putstr(s);
                        res += cogui_strlen(s);
						break;
					
                    /* handle character var */
                    case 'c':
                        cogui_putchar( (char)va_arg(ap, int ));
						res += 1;
                        break;

                    default:
						break;
				}
				break;
            
            /* handle escape character: newline */
            case '\n':
				cogui_putchar('\n');
				res += 1;
				break;
			
            /* handle escape character: return */
			case '\r':
				cogui_putchar('\r');
				res += 1;
				break;
			
            /* just output character */
			default:
				cogui_putchar(*str);
				res += 1;
		}
		str++;
     }
    va_end(ap);
	//CoSchedUnlock();

	return res;
}

void cogui_assert_handler(const char *ex_string, const char *func, U32 line)
{
	volatile char dummy = 0;

	cogui_printf("(%s) assertion failed at function: %s, line number: %d.\r\n", ex_string, func, line);

    /* loop forever */
	while(dummy == 0)
	{
	}
}
