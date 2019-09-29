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

void cogui_system_init(void *par)
{
    printf("initial screen list...\r\n");
    cogui_screen_list_init();

    printf("starting server...\r\n");
    cogui_server_init();

    printf("end of initial.\r\n");
}

void *cogui_malloc(U32 size)
{
    void *ptr;
    
    ptr = CoKmalloc(size);
	if(ptr == Co_NULL){
		printf("out of memory\r\n");
	}
	
    return ptr;
}

void cogui_free(void* memBuf)
{
    CoKfree(memBuf);
}

void *cogui_memmove(void *dest, const void *src, U64 n)
{
    char *tmp = (char *)dest, *s = (char *)src;

    if(s < tmp && tmp < s + n){
        tmp += n;
        s += n;

        while(n--){
            *(--tmp) = *(--s);
        }
    }
    else{
        while(n--){
            *tmp++ = *s++;
        }
    }

    return dest;
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

void cogui_assert_handler(const char *ex_string, const char *func, U32 line)
{
	volatile char dummy = 0;
	
	printf("(%s) assertion failed at function: %s, line number: %d.\r\n", ex_string, func, line);

	while(dummy ==0)
	{
	}
}
