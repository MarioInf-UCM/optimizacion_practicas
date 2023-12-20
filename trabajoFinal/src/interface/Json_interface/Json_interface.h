#ifndef __JSON_INTERFACE_H
#define __JSON_INTERFACE_H

#include <jsoncpp/json/json.h>
#include <string>
#include "JsonConfiguration/JsonConfiguration.h"


using namespace std;

class Json_interface {

    private:
        string fileURL;

    public:
        Json_interface();
        Json_interface(string jsonFileURL);
        ~Json_interface();
        
        JsonConfiguration getJSONConfiguration_FromFile();

        string getFileURL();
        void setFileURL(string data);

};

#endif
