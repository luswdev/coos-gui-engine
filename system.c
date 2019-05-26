/**
 *******************************************************************************
 * @file       system.c
 * @version    V0.0.1   
 * @date       2019.5.15
 * @brief      Some system function for GUI engine.	
 *******************************************************************************
 * @copy
 *
 * 
 *******************************************************************************
 */ 

/*---------------------------- Include ---------------------------------------*/
#include "GuiSystem.h"
#include "GuiApp.h"


/*---------------------------- Function Declare ------------------------------*/
void *GuiMalloc(U32 size)
{
    void *ptr;
    
    ptr = CoKmalloc(size);

    return ptr;
}


void GuiFree(void* memBuf)
{

    CoKfree(memBuf);
}

StatusType GuiSend(P_GuiApp app, struct GuiEvent event)
{
    StatusType result;

    if(app==Co_NULL || event==Co_NULL || size == 0){
        return;
    }

    result = CoPostMail(app->mq, event);

    return result;
}

StatusType GuiSendSync(P_GuiApp app, struct GuiEvent event)
{
    StatusType result;

    

    return result;
}

struct GuiEvent * GuiRecv(OS_EventID mq, StatusType *result)
{
    struct GuiEvent * event;
    P_GuiApp app;

    app = TCBTbl[CoGetCurTaskID()].userData;

    if(app==Co_NULL){
        return E_ERROR;
    }

    event = CoAcceptMail(mq, result);

    return result
}