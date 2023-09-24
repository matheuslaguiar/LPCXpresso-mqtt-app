/*
 * mqtt.c
 *
 *  Created on: 7 de set de 2023
 *      Author: matheus
 */

#include "../usr_mqtt/usr_mqtt.h"
#include "mqtt.h"
#include "board.h"
mqtt_client_t *client;

static void client_callback(mqtt_client_t *client, void *arg, mqtt_connection_status_t status) {
	/*
	  MQTT_CONNECT_ACCEPTED                 = 0,
	  MQTT_CONNECT_REFUSED_PROTOCOL_VERSION = 1,
	  MQTT_CONNECT_REFUSED_IDENTIFIER       = 2,
	  MQTT_CONNECT_REFUSED_SERVER           = 3,
	  MQTT_CONNECT_REFUSED_USERNAME_PASS    = 4,
	  MQTT_CONNECT_REFUSED_NOT_AUTHORIZED_  = 5,
	  MQTT_CONNECT_DISCONNECTED             = 256,
	  MQTT_CONNECT_TIMEOUT                  = 257
	 */
	if(status == MQTT_CONNECT_ACCEPTED) {
		LED1_ON();
		LED2_OFF();
	}
	else {
		LED1_OFF();
		LED2_ON();
	}
}

int8_t usr_mqtt_init()
{
	client = mqtt_client_new();

	ip4_addr_t addr;
	const struct mqtt_connect_client_info_t client_info = {
	  .client_id = "lpcxpresso_240923",
	  .client_user = "",
	  .client_pass = "",
	  .keep_alive = 60,  // Set the keep-alive time to 60 seconds
	  .will_topic = "",
	  .will_msg = "",
	  .will_qos = 0,     // Set the will QoS level
	  .will_retain = 0  // Set will_retain to 0 (false)
	};

	if(ip4addr_aton("54.146.113.169", &addr) != 1)
		return 0;

	return mqtt_client_connect(client, &addr, 1883, &client_callback, ((void *)0), &client_info) == ERR_OK;
}

uint8_t usr_mqtt_is_connected() {
	return mqtt_client_is_connected(client);
}
