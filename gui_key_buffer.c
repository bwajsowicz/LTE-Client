#include "Headers/GUI/gui_key_buffer.h"

extern GUI_KeyBuffer gui_key_buffer;
extern char key_stack[50];
extern bool is_user_typing_filename;

GUI_KeyBuffer initialize_gui_key_buffer_bar()
{
    gui_key_buffer.is_enabled = false;
	gui_key_buffer.x_position = 3;
	gui_key_buffer.y_position = 0;
	gui_key_buffer.draw_on_screen = draw_key_buffer_on_screen;
}

void draw_key_buffer_on_screen(char screen[23][80])
{
    int x = gui_key_buffer.x_position;
    if(is_user_typing_filename)
    {
        place_string_on_screen(screen[19], x-1, ">", 1);
    }
    place_string_on_screen(screen[19], x, key_stack, 40);
}