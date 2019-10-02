/**
 *******************************************************************************
 * @file       system.c
 * @version    V0.1.1   
 * @date       2019.9.17
 * @brief      Some system function for GUI engine.	
 *******************************************************************************
 */ 

#include "../include/cogui.h"
#include "../include/screen.h"
#include <stm32f4xx.h>
#include <stdarg.h>

void cogui_system_init(void *par)
{
    cogui_printf("Initial screen list...");
    cogui_screen_list_init();
    cogui_printf("[OK]\r\n");

    cogui_printf("Initial server...\r\n");
    cogui_server_init();

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

struct cogui_event *cogui_recv(OS_EventID mq, StatusType *result)
{
    struct cogui_event * event;
    cogui_app_t *app;

    app = TCBTbl[CoGetCurTaskID()].userData;

    COGUI_ASSERT(app != Co_NULL);

    event = CoPendMail(mq, 50,result);

    return event;
}

void *cogui_memcpy(void *dest, const void *src, U64 size)
{
    
}


U16 cogui_strlen(const char *str)
{
    const char *s;
    U16 i;

    for (s = str, i = 0; *s != '\0'; s++, i++)
        ;
    
    return i;
}

char *cogui_strdup(const char *str)
{
    U64 len = cogui_strlen(str) + 1;
    char *tmp = cogui_malloc(len);

    if (tmp == Co_NULL)
        return Co_NULL;

    cogui_memcpy(tmp, str, len);

    return tmp;
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
    int val,r_val;
	char count, ch;
	char *s = Co_NULL;
    int res = 0;

    CoSchedLock();
    va_start(ap,str);
    while ('\0' != *str) { 
          switch (*str)
          {
            case '%':
                str++;

                switch (*str) {
                    /* handle integer var */
                    case 'd':
                        val = va_arg(ap, int); 
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
	CoSchedUnlock();

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
