# Library Name: DeviceConfigJSON

* <a href="https://github.com/marcin-filipiak/DeviceConfigJSON#description">Description</a>
* <a href="https://github.com/marcin-filipiak/DeviceConfigJSON#how-it-works">How it works?</a>
* <a href="https://github.com/marcin-filipiak/DeviceConfigJSON#field-types">Field types</a>
* <a href="https://github.com/marcin-filipiak/DeviceConfigJSON#json-format">JSON Format</a>
* <a href="https://github.com/marcin-filipiak/DeviceConfigJSON#gui-for-easy-configuration">GUI for easy configuration</a>


## Description

DeviceConfigJSON is a C++ library that enables device configuration for ESP32 using the JSON format. This versatile library can serve configuration protocol for interacting with ESP32 devices through Bluetooth from (for example) an Android application. It allows users to dynamically customize their ESP32 settings, such as Wi-Fi network, communication parameters, and other options, using straightforward and intuitive JSON commands.

Key features of the DeviceConfigJSON library:
* Easy integration with ESP32 projects, enabling quick and flexible device configuration.
* JSON protocol support, providing a readable and understandable configuration format for users.
* Compatibility with Android applications, allowing configuration through a mobile interface.
* Support for various configuration parameters and options, making it adaptable for a wide range of use cases.
* Capability to manage and store configurations in JSON files.

DeviceConfigJSON is the ideal tool for IoT project creators, offering convenient device configuration while in use without the need to modify the source code.

https://www.arduino.cc/reference/en/libraries/deviceconfigjson/

## How it works?

With the DeviceConfigJSON library, you can create an object where you define the parameters you want to configure while specifying how they will be displayed on the interface. You can determine whether it's a simple message, a toggle switch, a password field, or other input types. In a way, you are defining an HTML-like form, which will be formatted into JSON.

This JSON format can be transmitted to various destinations via serial ports, Bluetooth, or network connections. The JSON data can also include information about the current settings in these fields. Sending back the formatted JSON allows for the retrieval of new settings.

In essence, this library provides a versatile and efficient means to configure and manage ESP32 devices, making it easy to adjust and exchange device settings through different communication channels.

## Field types

The DeviceConfigJSON library offers a range of field types for configuring device settings, each serving a specific purpose:
* Label: This field is used for displaying textual information or descriptions.
* Text Field: Ideal for entering text, this field allows users to input custom values.
* Password Field: Specifically designed for entering passwords, such as for Wi-Fi networks, to ensure security.
* State: This field conveys logical states, providing information on whether a particular feature or condition is currently active.
* Binary Switch: A binary switch is a two-state toggle switch. It allows users to turn something on or off, providing a simple way to enable or disable a feature.
* Select: The select field enables users to choose from a list of predefined options. It's particularly useful when selecting from available Wi-Fi networks or other multiple-choice scenarios.

With these diverse field types, the library facilitates the creation of versatile and user-friendly configuration interfaces for ESP32 devices, ensuring that each setting can be configured in a way that best suits its purpose.


## JSON format

I suggest you to explore the structure of the JSON format used for configuring the device. The method of transmission is identical for both sending data to the device and receiving data from it. This JSON format should include descriptions of what is being configured and the corresponding settings. This approach allows for a clear and consistent configuration process for your ESP32 devices.

By defining a well-structured JSON format for configuration, you can ensure that the information is transmitted accurately and can be easily understood by both the sender and the receiver. Here's a basic example of what the JSON format might look like:

```cpp
{
  "forms": [
    {
      "name": "test_form",
      "title": "Example Form",

      "members": [
        {
          "type": "label",
          "name": "temperature",
          "value": "25*C"
        },
        {
          "type": "text",
          "label": "Question",
          "name": "name_text",
          "value": "here is default text"
        },
        {
          "type": "password",
          "label": "Password:",
          "name": "name_password",
          "value": "secret password"
        },
        {
          "type": "state",
          "label": "Power is:",
          "name": "name_state",
          "value": true
        },
        {
          "type": "binswitch",
          "label": "Lamp:",
          "name": "name_binswitch",
          "set": true,
          "autosend": true
        },
        {
          "type": "select",
          "label": "Please select",
          "name": "name_option",
          "set": 0,
          "value": [
            {
              "value": "option0",
              "label": "option zero"
            },
            {
              "value": "option1",
              "label": "option one"
            },
            {
              "value": "option2",
              "label": "option two"
            }
          ]
        }
      ],
      "button": [
        {
          "type": "save",
          "label": "Click to save",
          "name": "save"
        },
        {
          "type": "reset",
          "label": "Click to reset",
          "name": "reset"
        }
      ]
    }
  ]
}
```

## GUI for easy configuration

In development, there are several programs (including Android) that will facilitate easy device configuration using this protocol and Bluetooth communication. Keep an eye on this section to stay up-to-date with the list of compatible programs.

### Android (bluetooth client):
* under construction
### Python (bluetoth client):
* https://github.com/marcin-filipiak/PyClientDeviceConfigJSON

