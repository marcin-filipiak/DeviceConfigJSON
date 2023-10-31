/**************************
DeviceConfigJSON Example

for ESP32 dev module
example with config by Bluetooth

**************************/


#include "DeviceConfigJSON.h"

#include <BluetoothSerial.h>
BluetoothSerial SerialBT;


DeviceConfigJSON DeviceConfigJSON("form_name","Here is a form title");


bool confsend = false;

void setup() {
    Serial.begin(115200);
    
    // Bluetooth device name 
    SerialBT.begin("ESP32"); 

    Serial.println("Waiting for a connection...");
}

void loop() {

    //if incoming JSON configuration from Bluetooth
    if (SerialBT.available()) {
        String incoming = SerialBT.readString();
        Serial.print("Received: ");
        Serial.println(incoming);

        ////////////////////////////////////////
        //here we get configuration from JSON//

        //we are reading only value from "name_text"
        String name_text_value = DeviceConfigJSON.getValue(incoming, "name_text");
      
        Serial.print("Parameter for name_text is:");
        Serial.print(name_text_value);
    }

    // If device is connected by bluetooth - send config JSON after 1000ms
    if (SerialBT.connected() && !confsend) {
        delay(1000);


        ////////////////////////////////
        // example elements to config //
        DeviceConfigJSON.label("name_label1", "wartosc1");
        DeviceConfigJSON.label("name_label2", "wartosc2");
        DeviceConfigJSON.text("Question:","name_text","here is default text");
        DeviceConfigJSON.password("Password:","name_password","secret password");
        DeviceConfigJSON.state("Power is:","name_state",true);
        DeviceConfigJSON.binswitch("Lamp:","name_binswitch",true,true);

        //3 elements to select
        String values[][2] = {
            {"name_option1", "option 1"},
            {"name_option2", "option 2"},
            {"name_option3", "option 3"}
        };
        DeviceConfigJSON.select("Please select:","name_option",0,values, ARRAY_SIZE(values));

        // string with generated json
        String jsonString = DeviceConfigJSON.getJSON();

        // clear json for new configuration
        DeviceConfigJSON.clear();

        
        //now we send JSON
        SerialBT.println(jsonString);
        Serial.println(jsonString);

        //set true, because we send only one time
        confsend = true; 
    }
}
