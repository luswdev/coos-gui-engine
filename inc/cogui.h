/**
 *******************************************************************************
 * @file       cogui.h
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      This is a file for GUI engine.	
 *******************************************************************************
 */ 

#ifndef __GUI_H__
#define __GUI_H__

#ifdef __cplusplus
extern "C" {
#endif

/* system library */
#include "stdint.h"

/* CooCox CoOS library */
#include "coocox.h"

/* configuation */
#include "cogui_config.h"

/* GUI component library */
#include "system.h"
#include "color.h"
#include "driver.h"
#include "dc.h"
#include "font.h"
#include "widget.h"
#include "title.h"
#include "window.h"
#include "event.h"
#include "app.h"
#include "server.h"
#include "mouse.h"
#include "kbddef.h"

#ifdef __cplusplus
}
#endif

#endif /* __COGUI_H__ */
