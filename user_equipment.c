#include "Headers/user_equipment.h"
#include "Headers/connection.h"
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

extern UserEquipment user_equipment;
extern threadpool thread_pool;
extern int client_socket;

void INThandler(int sig)
{
    char shutdown[] = "UE_Shutdown";

    message_label shutdown_label = {
        message_type : msg_ue_shutdown,
        message_length : sizeof(shutdown)
    };

    signal(sig, SIG_IGN);
    send_data(client_socket, (void *)shutdown, shutdown_label);
    printf("Shutdown UE\n");
    close(client_socket);
    exit(0);
}

void create_user_equipment_imsi()
{
    strcat(user_equipment.imsi, user_equipment.mmc);
    strcat(user_equipment.imsi, user_equipment.mnc);
    strcat(user_equipment.imsi, user_equipment.msin);
}

void create_user_equipment_plmn()
{
    strncpy(user_equipment.plmn, user_equipment.mmc, 7);
    strcat(user_equipment.plmn, user_equipment.mnc);
}

void power_off_on_trigger()
{
    signal(SIGINT, INThandler);
}

UserEquipment create_user_equipment()
{
    strncpy(user_equipment.mmc, "260", 3);
    strncpy(user_equipment.mnc, "06", 2);
    strncpy(user_equipment.msin, "123456789", 9);
    user_equipment.power_off_on_trigger = power_off_on_trigger;
    create_user_equipment_plmn();
    create_user_equipment_imsi();

    create_battery();
}