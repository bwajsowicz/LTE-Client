#pragma once

#include "battery.h"
#include "common.h"

typedef struct CurrentlyAttached_eNodeB
{
	char ip[128];
	int port;
} CurrentlyAttached_eNodeB;

typedef struct UserEquipment
{
	char mmc[4];   // Mobile Country Code
	char mnc[3];   // Mobile Network Code
	char msin[10]; // Mobile Subscriber Identification Number
	char imsi[16]; // International Mobile Subscriber Identity
	char plmn[8];
	int signal_strength;
	bool is_sleeping;
	bool is_requesting_download;
	bool is_requesting_file_list;
	void (*power_off_on_trigger)();
	Battery battery;
	CurrentlyAttached_eNodeB eNodeB;
} UserEquipment;

void create_user_equipment_imsi();
void create_user_equipment_plmn();

UserEquipment create_user_equipment();
