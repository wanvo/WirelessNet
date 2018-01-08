#define SKETCH_NAME "ds18b20"
#define SKETCH_MAJOR_VER "1"
#define SKETCH_MINOR_VER "0"

// Enable debug prints to serial monitor
#define MY_DEBUG 
#define MY_BAUD_RATE 9600
#define MY_NODE_ID AUTO

// Enable and select radio type attached
//#define MY_RADIO_NRF24
#define MY_RADIO_RFM69
#define MY_IS_RFM69HW
#define MY_RFM69_NEW_DRIVER   // ATC on RFM69 works only with the new driver (not compatible with old=default driver)
//#define MY_RFM69_ATC_TARGET_RSSI_DBM (-70)  // target RSSI -70dBm
//#define MY_RFM69_MAX_POWER_LEVEL_DBM (10)   // max. TX power 10dBm = 10mW


// Message signing settings
/*#define MY_RFM69_ENABLE_ENCRYPTION
#define MY_SIGNING_SOFT
#define MY_SIGNING_SOFT_RANDOMSEED_PIN 7
#define MY_SIGNING_REQUEST_SIGNATURES*/

#define CHILD_ID_RX_RSSI        (4)

#include <SPI.h>
#include <MySensors.h>  
#include <DallasTemperature.h>
#include <OneWire.h>

#define COMPARE_TEMP 1 // Send temperature only if changed? 1 = Yes 0 = No

#define ONE_WIRE_BUS 3 // Pin where dallase sensor is connected 
#define MAX_ATTACHED_DS18B20 16
unsigned long SLEEP_TIME = 30000; // Sleep time between reads (in milliseconds)
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass the oneWire reference to Dallas Temperature. 
float lastTemperature[MAX_ATTACHED_DS18B20];
int numSensors=0;
bool receivedConfig = false;
bool metric = true;
int batteryPcnt = 56;

// Initialize temperature message
MyMessage msg(0,V_TEMP);
MyMessage msgRxRSSI(CHILD_ID_RX_RSSI, V_VAR5);

void before()
{
  // Startup up the OneWire library
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(5, LOW);// GND pin for power manager
  digitalWrite(6, HIGH);//Vcc pin for power manager
  sensors.begin();
}

void setup()  
{ 
  // requestTemperatures() will not block current thread
  sensors.setWaitForConversion(false);
}

void presentation() {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo(SKETCH_NAME, SKETCH_MAJOR_VER "." SKETCH_MINOR_VER);

  // Fetch the number of attached temperature sensors  
  numSensors = sensors.getDeviceCount();

  // Present all sensors to controller
  for (int i=0; i<numSensors && i<MAX_ATTACHED_DS18B20; i++) {   
     present(i, S_TEMP, "ds18b20");
  }
}

void loop()     
{     
  // Fetch temperatures from Dallas sensors
  sensors.requestTemperatures();

  // query conversion time and sleep until conversion completed
  int16_t conversionTime = sensors.millisToWaitForConversion(sensors.getResolution());
  // sleep() call can be replaced by wait() call if node need to process incoming messages (or if node is repeater)
  sleep(conversionTime);

  // Read temperatures and send them to controller 
  for (int i=0; i<numSensors && i<MAX_ATTACHED_DS18B20; i++) {
 
    // Fetch and round temperature to one decimal
    float temperature = static_cast<float>(static_cast<int>((getControllerConfig().isMetric?sensors.getTempCByIndex(i):sensors.getTempFByIndex(i)) * 10.)) / 10.;
 
    // Only send data if temperature has changed and no error
    #if COMPARE_TEMP == 1
    if (lastTemperature[i] != temperature && temperature != -127.00 && temperature != 85.00) {
    #else
    if (temperature != -127.00 && temperature != 85.00) {
    #endif
 
      // Send in the new temperature
      send(msg.setSensor(i).set(temperature,1));
      // Save new temperatures for next compare
      lastTemperature[i]=temperature;
    }
  }
  sendBatteryLevel(batteryPcnt);
  //sendin RSSI for MyController
  // send(msgRxRSSI.set(transportGetSignalReport(SR_RX_RSSI)));
  int rssi=transportGetSignalReport(SR_RX_RSSI);
  char str[11];
sprintf (str, "rssi:%d dBm", rssi);
  msgRxRSSI.set(str);
  send(msgRxRSSI);
  sleep(SLEEP_TIME);
}
