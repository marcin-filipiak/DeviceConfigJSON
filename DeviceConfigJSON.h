#ifndef DeviceConfigJSON_h
#define DeviceConfigJSON_h

#include <Arduino.h>

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))

class DeviceConfigJSON {
public:
    DeviceConfigJSON();
    void label(const String& name, const String& value);
    void text(const String& label, const String& name, const String& value);
    void password(const String& label, const String& name, const String& value);
    void state(const String& label, const String& name, bool value);
    void binswitch(const String& label, const String& name, bool set, bool autosend);
    void select(const String& label, const String& name, int set, String values[][2], int numValues);
    String getJSON();
    void clear();
    String getValue(String& js, String& searchString);
    String getSet(String& js, String& searchString);

private:
    String jsonMembers;
    bool firstItemMembers;
};

#endif
