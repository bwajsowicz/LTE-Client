#include "Headers/ping.h"
#include "Headers/user_equipment.h"
#include "Headers/connection.h"
#include <pthread.h>

extern int client_socket;
extern UserEquipment user_equipment;
extern threadpool thread_pool;

void resolve_ping(bool ping_already_sent)
{
    char ping_response[64];
    char ping_request[64];

    message_label ping_response_label = {
        message_type : msg_ping_response,
        message_length : sizeof(ping_response)
    };

    read(client_socket, (void *)ping_request, sizeof(ping_request));
    printf("------------------------------------------\n");
    printf("RECEIVED MESSAGE\n");
    printf("Type: msg_ping_request\n");
    printf("------------------------------------------\n");
    if (!ping_already_sent)
        send_data(client_socket, (void *)&ping_response, ping_response_label);
}

void ping_server()
{
    message_label label;

    while (user_equipment.battery.is_battery_drained() == false)
    {
        if (user_equipment.battery.is_battery_critical() == true)
            printf("Battery is low!\n");

        bool ping_sent = false;
        while (true)
        {
            int response =
                read(client_socket, (void *)&label, sizeof(message_label));
            if (response < 0)
                break;

            usleep(50000);
            if (response == sizeof(message_label))
            {
                switch (label.message_type)
                {
                case msg_ping_request:
                    resolve_ping(ping_sent);
                    ping_sent = true;
                    break;
                default:
                    printf("Unknown message type.\n");
                    continue;
                }
            }
        }

        user_equipment.is_sleeping = true;
        printf("---Device goes to sleep.---\n");
        sleep(4);
        printf("\n---Device wakes up!---\n");
        usleep(100000);
        user_equipment.is_sleeping = false;
        sleep(1);
    }

    printf("Listening stopped.\n");
}