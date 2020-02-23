/**
 *******************************************************************************
 * @file       driver.c
 * @version    V0.7.1
 * @date       2020.02.23
 * @brief      Some system function for GUI engine's driver.	
 *******************************************************************************
 */ 

#include <cogui.h>

static cogui_graphic_driver_t _driver;
static cogui_graphic_driver_t *_current_driver = &_driver;

cogui_graphic_driver_t *cogui_graphic_driver_get_default()
{   
    return _current_driver;
}

void cogui_set_graphic_driver(cogui_graphic_driver_t *driver)
{
	_current_driver = driver;
}
