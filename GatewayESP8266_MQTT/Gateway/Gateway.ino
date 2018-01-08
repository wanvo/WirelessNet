/**
 * The MySensors Arduino library handles the wireless radio link and protocol
 * between your home built sensors/actuators and HA controller of choice.
 * The sensors forms a self healing radio network with optional repeaters. Each
 * repeater and gateway builds a routing tables in EEPROM which keeps track of the
 * network topology allowing messages to be routed to nodes.
 *
 * Created by Henrik Ekblad <henrik.ekblad@mysensors.org>
 * Copyright (C) 2013-2015 Sensnology AB
 * Full contributor list: https://github.com/mysensors/Arduino/graphs/contributors
 *
 * Documentation: http://www.mysensors.org
 * Support Forum: http://forum.mysensors.org
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 *******************************
  * Not all ESP8266 modules have all pins available on their external interface.
 * This code has been tested on an ESP-12 module.
 * The ESP8266 requires a certain pin configuration to download code, and another one to run code:
 * - Connect REST (reset) via 10K pullup resistor to VCC, and via switch to GND ('reset switch')
 * - Connect GPIO15 via 10K pulldown resistor to GND
 * - Connect CH_PD via 10K resistor to VCC
 * - Connect GPIO2 via 10K resistor to VCC
 * - Connect GPIO0 via 10K resistor to VCC, and via switch to GND ('bootload switch')
 *
  * Inclusion mode button:
 * - Connect GPIO5 via switch to GND ('inclusion switch')
 *
 */
#define SKETCH_NAME "RFM69"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"

// Enable debug prints to serial monitor
#define MY_DEBUG

// Use a bit lower baudrate for serial prints on ESP8266 than default in MyConfig.h
#define MY_BAUD_RATE 9600

// Enables and select radio type (if attached)
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RF69_IRQ_PIN D1
#define MY_RF69_IRQ_NUM MY_RF69_IRQ_PIN
#define MY_RF69_SPI_CS D8 // NSS. Use MY_RFM69_CS_PIN for the development branch.
#define MY_RFM69_FREQUENCY   RFM69_868MHZ
#define MY_RFM69_NEW_DRIVER
//#define MY_RFM69_ENABLE_ENCRYPTION
//#define MY_RFM69_NETWORKID 100
//#define MY_DEBUG_VERBOSE_RFM69
//#define MY_RFM69_ATC_MODE_DISABLED

// Message signing settings
//#define MY_SIGNING_SOFT
//#define MY_SIGNING_SOFT_RANDOMSEED_PIN 7
//#define MY_SIGNING_REQUEST_SIGNATURES
//#define MY_SIGNING_ATSHA204

#define MY_GATEWAY_MQTT_CLIENT
#define MY_GATEWAY_ESP8266

// Set this node's subscribe and publish topic prefix
#define MY_MQTT_PUBLISH_TOPIC_PREFIX "out_rfm69"
#define MY_MQTT_SUBSCRIBE_TOPIC_PREFIX "in_rfm69"

//#define MY_MQTT_PUBLISH_TOPIC_PREFIX "domoticz/in/MyMQTT"
//#define MY_MQTT_SUBSCRIBE_TOPIC_PREFIX "domoticz/out/MyMQTT"

// Set MQTT client id
#define MY_MQTT_CLIENT_ID "rfm69"

// Enable these if your MQTT broker requires usenrame/password
//#define MY_MQTT_USER "username"
//#define MY_MQTT_PASSWORD "password"

// Set WIFI SSID and password
#define MY_ESP8266_SSID "OrPiZero"
#define MY_ESP8266_PASSWORD "orangepi"
//#define MY_ESP8266_SSID "wanvo"
//#define MY_ESP8266_PASSWORD "merkulovanastya"

// Set the hostname for the WiFi Client. This is the hostname
// it will pass to the DHCP server if not static.
// #define MY_ESP8266_HOSTNAME "mqtt-sensor-gateway"

// Enable MY_IP_ADDRESS here if you want a static ip address (no DHCP)
//#define MY_IP_ADDRESS 192,168,178,87

// If using static ip you can define Gateway and Subnet address as well
//#define MY_IP_GATEWAY_ADDRESS 192,168,178,1
//#define MY_IP_SUBNET_ADDRESS 255,255,255,0

// MQTT broker ip address.
#define MY_CONTROLLER_IP_ADDRESS 172, 24, 1, 1
//#define MY_CONTROLLER_IP_ADDRESS 192, 168, 0, 199

// The MQTT broker port to to open
#define MY_PORT 1883

// Enable inclusion mode
//#define MY_INCLUSION_MODE_FEATURE
// Enable Inclusion mode button on gateway
//#define MY_INCLUSION_BUTTON_FEATURE
// Set inclusion mode duration (in seconds)
//#define MY_INCLUSION_MODE_DURATION 60
// Digital pin used for inclusion mode button
//#define MY_INCLUSION_MODE_BUTTON_PIN  3

// Set blinking period
//#define MY_DEFAULT_LED_BLINK_PERIOD 300

// Flash leds on rx/tx/err
//#define MY_DEFAULT_ERR_LED_PIN 16  // Error led pin
//#define MY_DEFAULT_RX_LED_PIN  16  // Receive led pin
//#define MY_DEFAULT_TX_LED_PIN  16  // the PCB, on board LED

#include <ESP8266WiFi.h>
#include <MySensors.h>

void setup()
{
    Serial.setDebugOutput(true);
	// Setup locally attached sensors
}

void presentation()
{
	// Present locally attached sensors here
    //Send node name and version information
  //sendSketchInfo("rfm69hw Gate", "1.0.0");
}

void loop()
{
	// Send locally attech sensors data here
}

