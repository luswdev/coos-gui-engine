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


/*---------------------------- Function Declare ------------------------------*/
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

/**
 *******************************************************************************
 * @brief      send a event to app	 
 * @param[in]  app      Where to send.
 * @param[in]  event    Which to send.
 * @param[out] E_ERROR  Bad.
 * @param[out] E_OK     Good.
 * @retval     None			 
 *
 * @par Description
 * @details    This function is called to send a event to app.
 *******************************************************************************
 */
StatusType GuiSend(P_GuiApp app, struct GuiEvent *event)
{
    StatusType result;

    if(app==Co_NULL || event==Co_NULL || size == 0){
        return E_ERROR;
    }

    result = CoPostMail(app->mq, event);

    return result;
}

/**
 *******************************************************************************
 * @brief      recive a event	 
 * @param[in]  app      Where to recive.
 * @param[in]  result   to put the result
 * @param[out] event    The recive event
 * @retval     None			 
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
        return E_ERROR;
    }

    event = CoAcceptMail(mq, result);

    return event
}