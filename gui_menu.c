#include "Headers/GUI/gui_menu.h"
#include "Headers/GUI/gui_helper.h"
#include "Headers/user_equipment.h"

extern GUI_Menu gui_menu;

extern UserEquipment user_equipment;

void draw_menu_on_screen(char screen[23][80])
{
	int x = gui_menu.x_position;
	int y = gui_menu.y_position;
    char enodeb_ip[64] = "IP: ";
    char enodeb_port[64] = "Port: ";
    char download[] = "1 : Download";
    char handover[] = "2 : Handover";
    char filelist[] = "3 : File list";
    char shutdown[] = "Ctrl + C : Shutdown";

    strcat(enodeb_ip, user_equipment.eNodeB.ip);
    sprintf(enodeb_port + strlen(enodeb_port), "%d", user_equipment.eNodeB.port);

    place_string_on_screen(screen[y], x, enodeb_ip, (sizeof(enodeb_ip)/sizeof(char)));
    place_string_on_screen(screen[++y], x, enodeb_port, (sizeof(enodeb_port)/sizeof(char)));
	place_string_on_screen(screen[++y], x, download, (sizeof(download)/sizeof(char)) );
    place_string_on_screen(screen[++y], x, handover, (sizeof(handover)/sizeof(char)) );
    place_string_on_screen(screen[++y], x, filelist, (sizeof(filelist)/sizeof(char)) );
    place_string_on_screen(screen[++y], x, shutdown, (sizeof(shutdown)/sizeof(char)) );

}

GUI_Menu initialize_gui_menu()
{
	gui_menu.is_enabled = true;
	gui_menu.x_position = 59;
	gui_menu.y_position = 4;
	gui_menu.draw_on_screen = draw_menu_on_screen;
}