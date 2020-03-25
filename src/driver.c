/**
 *******************************************************************************
 * @file       driver.c
 * @version    V0.7.2
 * @date       2020.03.01
 * @brief      Some system function for GUI engine's driver.	
 *******************************************************************************
 */ 

#include <cogui.h>

graphic_driver_t _driver;
graphic_driver_t *_current_driver = &_driver;

graphic_driver_t *gui_graphic_driver_get_default(void)
{   
    return _current_driver;
}

void gui_set_graphic_driver(graphic_driver_t *driver)
{
	_current_driver = driver;
}
