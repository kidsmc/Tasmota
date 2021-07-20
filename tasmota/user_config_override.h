/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2021  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/

/*
Examples :

// -- Master parameter control --------------------
#undef  CFG_HOLDER
#define CFG_HOLDER        4617                   // [Reset 1] Change this value to load SECTION1 configuration parameters to flash

// -- Setup your own Wifi settings  ---------------
#undef  STA_SSID1
#define STA_SSID1         "YourSSID"             // [Ssid1] Wifi SSID

#undef  STA_PASS1
#define STA_PASS1         "YourWifiPassword"     // [Password1] Wifi password

// -- Setup your own MQTT settings  ---------------
#undef  MQTT_HOST
#define MQTT_HOST         "your-mqtt-server.com" // [MqttHost]

#undef  MQTT_PORT
#define MQTT_PORT         1883                   // [MqttPort] MQTT port (10123 on CloudMQTT)

#undef  MQTT_USER
#define MQTT_USER         "YourMqttUser"         // [MqttUser] Optional user

#undef  MQTT_PASS
#define MQTT_PASS         "YourMqttPass"         // [MqttPassword] Optional password

// You might even pass some parameters from the command line ----------------------------
// Ie:  export PLATFORMIO_BUILD_FLAGS='-DUSE_CONFIG_OVERRIDE -DMY_IP="192.168.1.99" -DMY_GW="192.168.1.1" -DMY_DNS="192.168.1.1"'

#ifdef MY_IP
#undef  WIFI_IP_ADDRESS
#define WIFI_IP_ADDRESS     MY_IP                // Set to 0.0.0.0 for using DHCP or enter a static IP address
#endif

#ifdef MY_GW
#undef  WIFI_GATEWAY
#define WIFI_GATEWAY        MY_GW                // if not using DHCP set Gateway IP address
#endif

#ifdef MY_DNS
#undef  WIFI_DNS
#define WIFI_DNS            MY_DNS               // If not using DHCP set DNS IP address (might be equal to WIFI_GATEWAY)
#endif

// !!! Remember that your changes GOES AT THE BOTTOM OF THIS FILE right before the last #endif !!! 
*/

// -- Setup your own Wifi settings  ---------------
#undef  STA_SSID2
#define STA_SSID2         "BIMAT"             // [Ssid1] Wifi SSID

#undef  STA_PASS2
#define STA_PASS2         "12121234"     // [Password1] Wifi password

#ifndef USE_MQTT_TLS 
  #define USE_MQTT_TLS                             // Use TLS for MQTT connection (+34.5k code, +7.0k mem and +4.8k additional during connection handshake)
  //  #define USE_MQTT_TLS_CA_CERT                   // Force full CA validation instead of fingerprints, slower, but simpler to use.  (+2.2k code, +1.9k mem during connection handshake)
                                                   // This includes the LetsEncrypt CA in tasmota_ca.ino for verifying server certificates
  //  #define USE_MQTT_TLS_FORCE_EC_CIPHER   
  #undef  MQTT_PORT
  #define MQTT_PORT              8883              // [MqttPort] MQTT port (10123 on CloudMQTT)        
  
  #undef MQTT_TLS_ENABLED  
  #define MQTT_TLS_ENABLED       true              // [SetOption103] Enable TLS mode (requires TLS version)												// Force Elliptic Curve cipher (higher security) required by some servers (automatically enabled with USE_MQTT_AWS_IOT) (+11.4k code, +0.4k mem)
#endif

#undef MQTT_RESULT_COMMAND     
#define MQTT_RESULT_COMMAND    true 

// -- MQTT - Telemetry ----------------------------
#undef TELE_PERIOD
#define TELE_PERIOD            30               // [TelePeriod] Telemetry (0 = disable, 10 - 3600 seconds)
//#define TELE_ON_POWER
//#define TELE_ON_POWER        true
#undef MQTT_STATE_RETAIN         
#define MQTT_STATE_RETAIN      true

#undef MQTT_SENSOR_RETAIN     
#define MQTT_SENSOR_RETAIN     true

#undef MQTT_FULLTOPIC         
#define MQTT_FULLTOPIC         "%topic%/%prefix%/" 

#undef GUI_SHOW_HOSTNAME
#define GUI_SHOW_HOSTNAME      true             // [SetOption53] Show hostname and IP address in GUI main menu

#undef APP_TIMEZONE 
#define APP_TIMEZONE           7

// -- Location ------------------------------------
#undef LATITUDE 
#define LATITUDE               16.047079         // [Latitude] Your location to be used with sunrise and sunset

#undef LONGITUDE 
#define LONGITUDE              108.206230          // [Longitude] Your location to be used with sunrise and sunset

#undef USE_DOMOTICZ 

#undef USE_HOME_ASSISTANT 

#ifdef USE_RULES                                // Add support for rules (+8k code)
  #define USE_EXPRESSION                         // Add support for expression evaluation in rules (+3k2 code, +64 bytes mem)
    #define SUPPORT_IF_STATEMENT 
#endif

//#define USE_SCRIPT                               // Add support for script (+17k code)
  //#define USE_SCRIPT_FATFS 4                     // Script: Add FAT FileSystem Support
  //#define SUPPORT_MQTT_EVENT                     // Support trigger event with MQTT subscriptions (+3k5 code)

//#define USE_UFILESYS                              //Enable the Universal File System including Flash File System
//#define GUI_TRASH_FILE                            //Allows to delete files from the GUI File Manager
//#define GUI_EDIT_FILE                             //Allows to edit text files in the Web GUI

// -- Thermostat control ----------------------------
#define USE_THERMOSTAT  
#ifdef USE_THERMOSTAT
  #undef THERMOSTAT_RELAY_NUMBER 
  #define THERMOSTAT_RELAY_NUMBER               2         // Default output relay number for the first controller (+i for following ones)
  #undef THERMOSTAT_CONTROLLER_OUTPUTS 
  #define THERMOSTAT_CONTROLLER_OUTPUTS         2         // Number of outputs to be controlled independently
  #undef THERMOSTAT_TEMP_INIT
  #define THERMOSTAT_TEMP_INIT                  300
#endif 

#ifdef USE_I2C
  #define USE_BMP 
  #define USE_BH1750  
  #define USE_INA219                             // [I2cDriver14] Enable INA219 (I2C address 0x40, 0x41 0x44 or 0x45) Low voltage and current sensor (+1k code)
  #define USE_INA226 
  #define USE_DS3231                             // [I2cDriver26] Enable DS3231 external RTC in case no Wifi is avaliable. See docs in the source file (+1k2 code)
//    #define USE_RTC_ADDR  0x68
  #define USE_PCF8574                            // [I2cDriver2] Enable PCF8574 I/O Expander (I2C addresses 0x20 - 0x26 and 0x39 - 0x3F) (+1k9 code)
    #define USE_PCF8574_SENSOR                   // enable PCF8574 inputs and outputs in SENSOR message
    #define USE_PCF8574_DISPLAYINPUT             // enable PCF8574 inputs display in Web page
    #define USE_PCF8574_MQTTINPUT 
  #define USE_DHT12  
  #define USE_DISPLAY
#endif

#ifdef USE_DISPLAY
  #undef USE_DISPLAY_MATRIX                  // [DisplayModel 3] [I2cDriver5] Enable 8x8 Matrix display (I2C adresseses see below) (+11k code)
  #undef USE_DISPLAY_SEVENSEG
#endif

#undef USE_SHUTTER 

#ifdef USE_WEBSERVER 
  #undef USE_EMULATION_HUE                      // Enable Hue Bridge emulation for Alexa (+14k code, +2k mem common)
  #undef USE_EMULATION_WEMO 
#endif

#define USE_A4988_STEPPER

#endif  // _USER_CONFIG_OVERRIDE_H_
