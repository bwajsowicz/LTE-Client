#include "Headers/GUI/gui_battery.h"
#include "Headers/GUI/gui_helper.h"

extern GUI_Battery gui_battery;
extern UserEquipment user_equipment;

void draw_battery_on_screen(char screen[23][80])
{
	int x = gui_battery.x_position;
	int y = gui_battery.y_position;
	char battery_text[80];
	sprintf(battery_text, "Battery: %d%%", user_equipment.battery.charge);

	place_string_on_screen(screen[y], x, battery_text, 13);
}

GUI_Battery initialize_gui_battery()
{
	gui_battery.is_enabled = true;
	gui_battery.x_position = 66;
	gui_battery.y_position = 1;
	gui_battery.draw_on_screen = draw_battery_on_screen;
}