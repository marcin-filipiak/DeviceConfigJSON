/**************************
DeviceConfigJSON Example

for ESP32 dev module
example with Bluetooth

**************************/


#include <DeviceConfigJSON.h>

#include <BluetoothSerial.h>
BluetoothSerial SerialBT;


DeviceConfigJSON DeviceConfigJSON("form_name","Here is a form title");


bool confsend = false;

void setup() {
    Serial.begin(115200);
    
    // Bluetooth device name 
    SerialBT.begin("ESP32"); 
    // Set a PIN for Bluetooth connection
    SerialBT.setPin("1111"); // Replace "1111" with your desired PIN

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

        //for example we are reading value from "name_text"
        String name_text_value = DeviceConfigJSON.getValue(incoming, "name_text");
        Serial.print("\nValue from 'name_text' is:");
        Serial.print(name_text_value);

        //for example we are reading value from "name_password"
        String name_password_value = DeviceConfigJSON.getValue(incoming, "name_password");
        Serial.print("\nValue from 'name_password' is:");
        Serial.print(name_password_value);

        //for example we are reading value from "name_binswitch"
        bool name_state_value = DeviceConfigJSON.getSet<bool>(incoming, "name_binswitch");
        Serial.print("\nSetted state in 'name_binswitch' is:");
        Serial.print(name_state_value);

        //for example we are reading value from "name_option"
        int name_option_value = DeviceConfigJSON.getSet<int>(incoming, "name_option");
        Serial.print("\nSelected option in 'name_option' is:");
        Serial.print(name_option_value);
    }

    // If device is connected by bluetooth - send config JSON after 1000ms
    if (SerialBT.connected() && !confsend) {
        delay(1000);
        Serial.println("Device connected. Sending JSON.");

        ////////////////////////////////
        // example elements to config //
        DeviceConfigJSON.label("name_label1", "example label1");
        DeviceConfigJSON.label("name_label2", "example label2");
        DeviceConfigJSON.text("Question","name_text","here is default text");
        DeviceConfigJSON.password("Password","name_password","secret password");
        DeviceConfigJSON.state("Power is","name_state",true);
        DeviceConfigJSON.binswitch("Lamp","name_binswitch",true,true);

        //3 elements to select
        String values[][2] = {
            {"name_option1", "option 1"},
            {"name_option2", "option 2"},
            {"name_option3", "option 3"}
        };
        DeviceConfigJSON.select("Please select","name_option",0,values, ARRAY_SIZE(values));

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
