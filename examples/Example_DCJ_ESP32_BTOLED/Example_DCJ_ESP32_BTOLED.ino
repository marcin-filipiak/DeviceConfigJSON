/**************************
DeviceConfigJSON Example

for ESP32 WeMos dev module
example with Bluetooth
and OLED

**************************/


#include <DeviceConfigJSON.h>
DeviceConfigJSON DeviceConfigJSON("form1","Its example form");

#include <BluetoothSerial.h>
BluetoothSerial SerialBT;

/////////////////////////////////////////////////////
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

////////////////////////////////////////////////////

//tone generator
void tone(int pin, int hz, int tdelay) {
  int okr = 1000000 / hz; 
  int halfokr = okr / 2;     

  for (long i = 0; i < (hz * tdelay) / 1000; i++) {
    digitalWrite(pin, HIGH); 
    delayMicroseconds(halfokr);
    digitalWrite(pin, LOW);  
    delayMicroseconds(halfokr);
  }
}


/////////////////////////////////////

bool confsend = false;
String example_text = "---";
bool sound = false;


void setup() {

  Serial.begin(115200);
  
  pinMode(15, OUTPUT);

  // Start I2C Communication SDA = 5 and SCL = 4 on Wemos Lolin32 ESP32 with built-in SSD1306 OLED
  Wire.begin(5, 4);

   if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C, false, false)) {
    Serial.println(F("SSD1306 allocation failed\n"));
    for(;;);
  }

  // Clear the buffer.
  display.clearDisplay();

  // Font size and color
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  // Bluetooth device name 
  SerialBT.begin("ESP32"); 
  // Set a PIN for Bluetooth connection
  //SerialBT.setPin("1111"); // Replace "1111" with your desired PIN
  
}


void loop() {

  //if incoming JSON configuration from Bluetooth
  if (SerialBT.available()) {
        String incoming = SerialBT.readString();

        //Serial.println(incoming);
    
        ////////////////////////////////////////
        //here we get configuration from JSON//
        example_text = DeviceConfigJSON.getValue(incoming, "example_text");
        sound = DeviceConfigJSON.getSet<bool>(incoming, "sound"); //return set in bool format
  }

  // If device is connected by bluetooth - send config JSON after 1000ms
  if (SerialBT.connected() && !confsend) {
        delay(1000);
        Serial.println("Device connected. Sending JSON.");

        ////////////////////////////////
        // example elements to config //
        DeviceConfigJSON.text("Text","example_text","");
        DeviceConfigJSON.binswitch("sound","sound",sound,true);

        // string with generated json
        String jsonString = DeviceConfigJSON.getJSON();

        // clear json for new configuration
        DeviceConfigJSON.clear();

        //now we send JSON
        SerialBT.println(jsonString);

        //set true, because we send only one time
        confsend = true; 
  }  

  
  display.clearDisplay();

  if (!confsend){
    display.setCursor(1, 5);
    display.print("Please connect");
  }
  else {
    display.setCursor(1, 5);
    display.print("Connected");
    display.setCursor(5, 20);
    display.print("Text: "+example_text);
    if (sound){
      display.setCursor(5, 30);
      display.print("Sound: on");
      tone(15,1000,300);
    }
    else {
          display.setCursor(5, 30);
          display.print("Sound: off");
    }
  }
  
  display.display();
  
  delay(500);
  
}
