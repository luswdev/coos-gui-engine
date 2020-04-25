# GUI engine for CoOS
A GUI engine for CoOS, this project can help developer build a application on CoOS and render some frame on screen.

## Feature
- Application manager
- Window and widget tree system
- Mouse and keyboard support
- Event oriented server/client system

### Start Up
```c
gui_system_init(void);
```

### Application
- Creation
```c
app_t *app_ptr = gui_app_create("app_name");
```

- Running
```c
gui_app_run(app_ptr);
```

- Delete (app should delete itself when runloop is out)
```c
gui_app_delete(app_ptr);
```

### Window
- Creation
```c
window_t *window_ptr = gui_window_create_with_title();

/* or */

window_t *window_ptr = gui_window_create_without_title();
```

- Render
```c
gui_window_show(window_ptr);
```

- Hide
```c
gui_window_hide(window_ptr);
```

- Close (will destory window)
```c
gui_window_close(window_ptr);
```

### Widget
- Creation
```c
widget_t *widget_ptr = gui_widget_create();
```

- Render
```c
gui_widget_show(widget_ptr);
```

- Hide
```c
gui_widget_hide(widget_ptr);
```

- Delete
```c
gui_widget_delete(widget_ptr);
```

#### Moving
- moving to logic point (x, y) (by parent window)
```c
gui_widget_move_to_logic(widget_ptr, x, y);
```

- moving to device point (x, y)
```c
gui_widget_move_to_phy(widget_ptr, x, y);
```

#### Texting
- Set text
```c
gui_widget_set_text(widget_ptr, "text..");

```

- Append text to rear
```c
gui_widget_append_text(widget_ptr, "append text...");
```

- Clear text
```c
gui_widget_clear_text(widget_ptr);
```

- Alignment
```c
gui_widget_set_text_align(widget_ptr, alignment);
```

### Mouse / Keyboard
- Mouse should capture event like `EVENT_MOUSE_CLICK`.
    - Contain cursor position (x, y) and pressed button(s).
- Keyboard should capture event like `EVENT_KBD`.
    - Contain up/down key, modify keys and ascii code if possible.

### Change Log
- V0.7.4
    - Finish keyboard event
- V0.7.3
    - Add keyboard defines
    - Replace prefix "cogui" to "gui"
- V0.7.2
    - Add mouse button event
    - Add optional event - mouse click
    - Finish mouse develope
- V0.7.1
    - Add cursor moving
    - Add cursor icon
    - Fix color bug
- V0.7.0
    - First version of mouse
- V0.6.1
    - Add font display for dc
- V0.6.0
    - Add main page management
- V0.5.1
    - Add title for window
- V0.5.0
    - First version of window
- V0.4.1
    - Add widget function
    - focus, show\/hide and move
- V0.4.0
    - First version of DC engine
    - Work for default HW level
- V0.3.0
    - First version of widget
    - Add widget creation and deletion
- V0.2.0
    - First version of server
    - Add event handler for app create
- V0.1.0
    - First version of application
    - Work for app build, destory and run loop

## To-Do
- [ ] FrameBuffer support
- [ ] Image and video renderer
- [ ] File system support

## License
MIT