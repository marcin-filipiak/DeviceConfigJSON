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
    String getSet(String& js, const String& searchString);

private:
    String formname;
    String formtitle;
    String jsonMembers;
    bool firstItemMembers;
};

#endif
