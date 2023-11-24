/*

  Device Config JSON

  Written by Marcin Filipiak
  http://NoweEnergie.org

    This library is free software: you can redistribute it and/or modify
    it under the terms of the GNU LESSER GENERAL PUBLIC LICENSE as published by
    the Free Software Foundation, either version 2.1 of the License.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
    See the GNU LESSER GENERAL PUBLIC LICENSE for more details.

*/


#ifndef DeviceConfigJSON_h
#define DeviceConfigJSON_h

#include <Arduino.h>

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))

class DeviceConfigJSON {
public:
    DeviceConfigJSON(const String& formn, const String& formt);
    void label(const String& name, const String value);
    void text(const String& label, const String& name, String value);
    void password(const String& label, const String& name, String value);
    void state(const String& label, const String& name, bool value);
    void binswitch(const String& label, const String& name, bool set, bool autosend);
    void select(const String& label, const String& name, int set, String values[][2], int numValues);
    String getJSON();
    void clear();
    String getValue(String& js, const String& searchString);
    template <typename T>
    T getSet(String& js, const String& searchString);
    

private:
    String formname;
    String formtitle;
    String jsonMembers;
    bool firstItemMembers;
};

#endif
