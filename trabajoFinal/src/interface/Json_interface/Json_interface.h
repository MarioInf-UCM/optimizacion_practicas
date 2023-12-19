#ifndef __JSON_INTERFACE_H
#define __JSON_INTERFACE_H

#include <jsoncpp/json/json.h>
#include <string>

using namespace std;

class Json_interface {

    private:
        string jsonFileURL;

    public:

        Json_interface(string jsonFileURL){
            Json_interface::jsonFileURL = jsonFileURL;
        }
        ~Json_interface(){ }

        
        void processJSONFile();


        //********************************************************
        // ZONA DE DEFINICIÓN DE MÉTODOS DE ACCESO A LAS VARIABLES
        //********************************************************

        string get_jsonFileURL(void){
            return jsonFileURL;
        }
        void get_jsonFileURL(string data){
            jsonFileURL = data;
            return;
        }
};

#endif
