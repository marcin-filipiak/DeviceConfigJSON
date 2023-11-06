#include "DeviceConfigJSON.h"

DeviceConfigJSON::DeviceConfigJSON(const String& formn, const String& formt) {
    this->formname = formn;
    this->formtitle = formt;
    clear();
}

void DeviceConfigJSON::label(const String& name, String value) {
    if (!firstItemMembers) {
        jsonMembers += ",";
    }
    jsonMembers += "{";
    jsonMembers += "\"type\": \"label\",";
    jsonMembers += "\"name\": \"" + name + "\",";
    jsonMembers += "\"value\": \"" + value + "\"";
    jsonMembers += "}";
    firstItemMembers = false;
}

void DeviceConfigJSON::text(const String& label, const String& name, String value) {
    if (!firstItemMembers) {
        jsonMembers += ",";
    }
    jsonMembers += "{";
    jsonMembers += "\"type\": \"text\",";
    jsonMembers += "\"label\": \"" + label + "\",";
    jsonMembers += "\"name\": \"" + name + "\",";
    jsonMembers += "\"value\": \"" + value + "\"";
    jsonMembers += "}";
    firstItemMembers = false;
}

void DeviceConfigJSON::password(const String& label, const String& name, String value) {
    if (!firstItemMembers) {
        jsonMembers += ",";
    }
    jsonMembers += "{";
    jsonMembers += "\"type\": \"password\",";
    jsonMembers += "\"label\": \"" + label + "\",";
    jsonMembers += "\"name\": \"" + name + "\",";
    jsonMembers += "\"value\": \"" + value + "\"";
    jsonMembers += "}";
    firstItemMembers = false;
}

void DeviceConfigJSON::state(const String& label, const String& name, bool value) {
    if (!firstItemMembers) {
        jsonMembers += ",";
    }
    jsonMembers += "{";
    jsonMembers += "\"type\": \"state\",";
    jsonMembers += "\"label\": \"" + label + "\",";
    jsonMembers += "\"name\": \"" + name + "\",";
    if (value == true) {
        jsonMembers += "\"value\": true";
    } else {
        jsonMembers += "\"value\": false";
    }
    jsonMembers += "}";
    firstItemMembers = false;
}

void DeviceConfigJSON::binswitch(const String& label, const String& name, bool set, bool autosend) {
    if (!firstItemMembers) {
        jsonMembers += ",";
    }
    jsonMembers += "{";
    jsonMembers += "\"type\": \"binswitch\",";
    jsonMembers += "\"label\": \"" + label + "\",";
    jsonMembers += "\"name\": \"" + name + "\",";
    if (set == true) {
        jsonMembers += "\"set\": true,";
    } else {
        jsonMembers += "\"set\": false,";
    }
    if (autosend == true) {
        jsonMembers += "\"autosend\": true";
    } else {
        jsonMembers += "\"autosend\": false";
    }
    jsonMembers += "}";
    firstItemMembers = false;
}

void DeviceConfigJSON::select(const String& label, const String& name, int set, String values[][2], int numValues) {
    if (!firstItemMembers) {
        jsonMembers += ",";
    }
    jsonMembers += "{";
    jsonMembers += "\"type\":\"select\",";
    jsonMembers += "\"label\":\"" + label + "\",";
    jsonMembers += "\"name\":\"" + name + "\",";
    jsonMembers += "\"set\":" + String(set) + ",";
    jsonMembers += "\"values\":[";
    
    for (int i = 0; i < numValues; i++) {
        jsonMembers += "{";
        jsonMembers += "\"value\":\"" + values[i][0] + "\",";
        jsonMembers += "\"label\":\"" + values[i][1] + "\"";
        jsonMembers += "}";
        if (i < numValues - 1) {
            jsonMembers += ", ";
        }
    }
    
    jsonMembers += "]";
    jsonMembers += "}";
    firstItemMembers = false;
}

String DeviceConfigJSON::getJSON() {
    String result = "{";
    result += "\"forms\":[";
    result += "{\"name\":\"" + this->formname + "\",";
    result += "\"title\":\"" + this->formtitle + "\",";

    result += "\"members\": [";
    result += jsonMembers;
    result += "],";

    result += "\"button\":[";
    result += "{\"type\": \"save\",\"label\": \"Save\",\"name\": \"save\"},";
    result += "{\"type\": \"reset\",\"label\": \"Reset\",\"name\": \"reset\"}";
    result += "]";
    
    result += "}]}\r\n";
    clear();
    return result;
}

void DeviceConfigJSON::clear() {
    jsonMembers = "";
    firstItemMembers = true;
}

String DeviceConfigJSON::getValue(String& js, const String& searchString) {
    int startPos = js.indexOf(searchString);

    if (startPos != -1) {
        int openBracePos = js.lastIndexOf('{', startPos);
        int closeBracePos = js.indexOf('}', startPos);

        if (openBracePos != -1 && closeBracePos != -1) {
            String extractedSection = js.substring(openBracePos, closeBracePos + 1);

            String fieldName = "value";
            int valueStart = extractedSection.indexOf("\"" + fieldName + "\":");
            extractedSection = extractedSection.substring(valueStart + 8);

            int ppc = extractedSection.indexOf('"');
            int pdc = extractedSection.indexOf('"', ppc + 1);

            String value = extractedSection.substring(ppc + 1, pdc);
            return value;
        }
    }

    return "";
}

String DeviceConfigJSON::getSet(String& js, const String& searchString) {
    int startPos = js.indexOf(searchString);

    if (startPos != -1) {
        int openBracePos = js.lastIndexOf('{', startPos);
        int closeBracePos = js.indexOf('}', startPos);

        if (openBracePos != -1 && closeBracePos != -1) {
            String extractedSection = js.substring(openBracePos, closeBracePos + 1);

            String fieldName = "set";
            int valueStart = extractedSection.indexOf("\"" + fieldName + "\":");
            extractedSection = extractedSection.substring(valueStart + 8);

            int ppc = extractedSection.indexOf('"');
            int pdc = extractedSection.indexOf('"', ppc + 1);

            String value = extractedSection.substring(ppc + 1, pdc);
            return value;
        }
    }

    return "";
}
