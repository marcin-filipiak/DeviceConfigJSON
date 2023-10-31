#ifndef DeviceConfigJSON_h
#define DeviceConfigJSON_h

#define ARRAY_SIZE(array) ((sizeof(array))/(sizeof(array[0])))

class DeviceConfigJSON {
public:
    DeviceConfigJSON() {
        clear();
    }

    //pole label//
    void label( const String& name, const String& value) {
        if (!firstItemMembers) {
            jsonMembers += ",";
        }
        jsonMembers += "{";
        jsonMembers += "\"type\": \"label\",";
        //jsonMembers += "\"label\": \"" + label + "\",";
        jsonMembers += "\"name\": \"" + name + "\",";
        jsonMembers += "\"value\": \"" + value + "\"";
        jsonMembers += "}";
        firstItemMembers = false;
    }
    
    //pole tekstowe//
    void text(const String& label, const String& name, const String& value) {
        if (!firstItemMembers) {
            jsonMembers += ",";
        }
        jsonMembers += "{";
        jsonMembers += "\"type\": \"text\",";
        jsonMembers += "\"label\": \""+label+"\",";
        jsonMembers += "\"name\": \""+name+"\",";
        jsonMembers += "\"value\": \""+value+"\"";
        jsonMembers += "}";
        firstItemMembers = false;
    }
    
    //pole password//
    void password(const String& label, const String& name, const String& value) {
        if (!firstItemMembers) {
            jsonMembers += ",";
        }
        jsonMembers += "{";
        jsonMembers += "\"type\": \"password\",";
        jsonMembers += "\"label\": \""+label+"\",";
        jsonMembers += "\"name\": \""+name+"\",";
        jsonMembers += "\"value\": \""+value+"\"";
        jsonMembers += "}";
        firstItemMembers = false;
    }
    
    //pole state
    void state(const String& label, const String& name, bool value) {
        if (!firstItemMembers) {
            jsonMembers += ",";
        }
        jsonMembers += "{";
        jsonMembers += "\"type\": \"state\",";
        jsonMembers += "\"label\": \""+label+"\",";
        jsonMembers += "\"name\": \""+name+"\",";
        if (value == true){
          jsonMembers += "\"value\": true";
        }
        else {
          jsonMembers += "\"value\": false";
        }
        jsonMembers += "}";
        firstItemMembers = false;
    }
    
    //pole binswitch
    void binswitch(const String& label, const String& name, bool set, bool autosend) {
        if (!firstItemMembers) {
            jsonMembers += ",";
        }
        jsonMembers += "{";
        jsonMembers += "\"type\": \"binswitch\",";
        jsonMembers += "\"label\": \""+label+"\",";
        jsonMembers += "\"name\": \""+name+"\",";
        if (set == true){
          jsonMembers += "\"isset\": true,";
        }
        else {
          jsonMembers += "\"isset\": false,";
        }
        if (autosend == true){
          jsonMembers += "\"autosend\": true";
        }
        else {
          jsonMembers += "\"autosend\": false";
        }        
        
        jsonMembers += "}";
        firstItemMembers = false;
    }
    
    //pole select//
    void select(const String& label, const String& name, int set, String values[][2], int numValues) {
        if (!firstItemMembers) {
            jsonMembers += ",";
        }
        jsonMembers += "{";
        jsonMembers += "\"type\":\"select\",";
        jsonMembers += "\"label\":\"" + label + "\",";
        jsonMembers += "\"name\":\"" + name + "\",";
        jsonMembers += "\"set\":\"" + String(set) + "\"";
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

    //zwracanie zbudowanego JSON
    String getJSON() {
        //formularz
        String result = "{";
        result += "\"forms\":[";
        result += "{\"name\":\"testform\",";
        result += "\"title\":\"form testowy\",";

        //elementy forma
        result += "\"members\": [";
        result += jsonMembers;
        result += "],";

        //przyciski
        result += "\"button\":[";
        result += "{\"type\": \"save\",\"label\": \"Zapisz\",\"name\": \"save\"},";
        result += "{\"type\": \"reset\",\"label\": \"Resetuj\",\"name\": \"reset\"}";
        result += "]";
        
        result += "}]}";
        clear();
        return result;
    }

    void clear() {
        jsonMembers = "";
        firstItemMembers = true;
    }

    //pobranie z JSONA wartości value dla danego pola szukanego po name//
    String getValue(String& js, String& searchString) {
        int startPos = js.indexOf(searchString);
    
        if (startPos != -1) {
            int openBracePos = js.lastIndexOf('{', startPos);
            int closeBracePos = js.indexOf('}', startPos);
    
            if (openBracePos != -1 && closeBracePos != -1) {
                String extractedSection = js.substring(openBracePos, closeBracePos + 1);
    
                // Szukana nazwa pola
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

    //pobranie z JSONA wartości set dla danego pola szukanego po name//
    String getSet(String& js, String& searchString) {
        int startPos = js.indexOf(searchString);
    
        if (startPos != -1) {
            int openBracePos = js.lastIndexOf('{', startPos);
            int closeBracePos = js.indexOf('}', startPos);
    
            if (openBracePos != -1 && closeBracePos != -1) {
                String extractedSection = js.substring(openBracePos, closeBracePos + 1);
    
                // Szukana nazwa pola
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


private:
    String jsonMembers;
    bool firstItemMembers;
};

#endif
