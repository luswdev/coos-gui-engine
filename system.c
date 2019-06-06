/**
 *******************************************************************************
 * @file       system.c
 * @version    V0.0.1   
 * @date       2019.5.15
 * @brief      Some system function for GUI engine.	
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "cogui.h"

void GuiSystemInit(void *par)
{
    ServerInit();

    return;
}

/**
 *******************************************************************************
 * @brief      allocate memory	 
 * @param[in]  size     How many memory	should allocate?
 * @param[out] None
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to allocate memory.
 *******************************************************************************
 */
void *GuiMalloc(U32 size)
{
    void *ptr;
    
    ptr = CoKmalloc(size);

    return ptr;
}

/**
 *******************************************************************************
 * @brief      free memory	 
 * @param[in]  memBuf     Where should free?
 * @param[out] None
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to free memory.
 *******************************************************************************
 */
void GuiFree(void* memBuf)
{
    CoKfree(memBuf);
}

void *MemMove(void *dest, const void *src, U64 n)
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

/**
 *******************************************************************************
 * @brief      Ack a request	 
 * @param[in]  app      ack which event
 * @param[in]  event    which status to ack
 * @param[out] None
 * @retval     E_OK     Good.
 * @retval     E_ERROR  No such event	 
 * @retval     E_ERROR  No such ack place 
 *
 * @par Description
 * @details    This function is called to ack a request.
 *******************************************************************************
 */
StatusType GuiAck(struct GuiEvent *event, StatusType status)
{
    if(event == Co_NULL){
				return E_ERROR;
		}
    if(event->ack == 0){
				return E_INVALID_ID;
		}
		

    CoPostMail(event->ack, (void *)&status);

    return E_OK;
}

/**
 *******************************************************************************
 * @brief      send a event to app	 
 * @param[in]  app      Where to send.
 * @param[in]  event    Which to send.
 * @param[out] None
 * @retval     E_OK     Good.
 * @retval     E_ERROR  Bad.		 
 *
 * @par Description
 * @details    This function is called to send a event to app.
 *******************************************************************************
 */
StatusType GuiSend(P_GuiApp app, struct GuiEvent *event)
{
    StatusType result;

    if(app==Co_NULL || event==Co_NULL){
        return E_ERROR;
    }
		
		printf("[sys]Send a event no.%d, ptr=0x%p, sender=0x%p\n", event->type, event, event->sender);
    result = CoPostMail(app->mq, event);
		//CoTickDelay(50);
    return result;
}

/**
 *******************************************************************************
 * @brief      recive a event	 
 * @param[in]  mq       Where to recive.
 * @param[in]  result   to put the result
 * @param[out] None
 * @retval     event    The recive event			 
 *
 * @par Description
 * @details    This function is called to recive a event.
 *******************************************************************************
 */
struct GuiEvent * GuiRecv(OS_EventID mq, StatusType *result)
{
    struct GuiEvent * event;
    P_GuiApp app;

    app = TCBTbl[CoGetCurTaskID()].userData;

    if(app==Co_NULL){
        return Co_NULL;
    }
		
    event = CoPendMail(mq, 50,result);
		if(event!=Co_NULL)
			printf("[sys]Recv a event no.%d, ptr=0x%p, sender=0x%p\n", event->type, event, event->sender);

    return event;
}
