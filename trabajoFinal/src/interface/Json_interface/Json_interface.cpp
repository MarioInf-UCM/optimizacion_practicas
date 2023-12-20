#include <iostream>
#include <fstream>
#include <string>
#include <jsoncpp/json/json.h>

#include "Json_interface.h"
#include "JsonConfiguration/JsonConfiguration.h"
#include "JsonConfiguration/ComputerConfiguration/ComputerConfiguration.h"
#include "JsonConfiguration/RankConfiguration/RankConfiguration.h"
#include "JsonConfiguration/WorldConfiguration/WorldConfiguration.h"

using namespace std;
using namespace Json;



//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
Json_interface::Json_interface(){}
Json_interface::Json_interface(string jsonFileURL){
    setFileURL(jsonFileURL);
}

Json_interface::~Json_interface(){ }



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
JsonConfiguration Json_interface::getJSONConfiguration_FromFile() {

    JsonConfiguration jsonConfiguration = JsonConfiguration();
     
    ifstream file(getFileURL());
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo JSON (" << getFileURL() << ")"  << endl;
        jsonConfiguration.setStatus(false);
    }

    CharReaderBuilder builder;
    Value root;
    CharReader *reader;
    JSONCPP_STRING errs;
    bool result = true;
    
    //Leemos el fichero JSON
    reader = builder.newCharReader();
    result = parseFromStream(builder, file, &root, &errs);
    if(!result){
        cerr << "Error al parsear el archivo JSON (" << getFileURL() << ")" << endl ;
        cerr << errs << endl;
        jsonConfiguration.setStatus(false);
        return jsonConfiguration;
    }
    file.close();
    
    WorldConfiguration worldConfigurationTemp;
    worldConfigurationTemp.setID(root["worldConfiguration"]["id"].asString());
    worldConfigurationTemp.setDimensions(root["worldConfiguration"]["dimensions"].asUInt());
    worldConfigurationTemp.setFitnessFunctionID(root["worldConfiguration"]["fitnessFunctionID"].asString());
    jsonConfiguration.setWorldConfiguration(worldConfigurationTemp);

    int i=0, j=0, k=0;
    for (const auto &computerConfig : root["computerConfiguration"]) {
        //computerConfigurationTemp.setIsDefault(computerConfig["isDefault?"].asBool());
        jsonConfiguration.getComputerConfigurationList()[i].setIsDefault(false);
        jsonConfiguration.getComputerConfigurationList()[i].setIP(computerConfig["IP"].asString());

        j=0;
        for (const auto &rankConfig : computerConfig["rankConfigurationList"]) {
            jsonConfiguration.getComputerConfigurationList()[i].getRankConfigurationList()[j].setIsDefault(false);
            jsonConfiguration.getComputerConfigurationList()[i].getRankConfigurationList()[j].setRank(rankConfig["rank"].asUInt());
            jsonConfiguration.getComputerConfigurationList()[i].getRankConfigurationList()[j].setOutputFile(rankConfig["outFIleURL"].asString());
            jsonConfiguration.getComputerConfigurationList()[i].getRankConfigurationList()[j].setHeuristicID(rankConfig["heuristicID"].asString());
            jsonConfiguration.getComputerConfigurationList()[i].getRankConfigurationList()[j].setIterations(rankConfig["iterations"].asUInt());
            jsonConfiguration.getComputerConfigurationList()[i].getRankConfigurationList()[j].setPoblation(rankConfig["poblation"].asUInt());

            k=0;
            for (const auto &value : rankConfig["valueList"]) {
                jsonConfiguration.getComputerConfigurationList()[i].getRankConfigurationList()[j].setValue_byIndex(k, value.asFloat());
                k++;
            }

            j++;
        }
        
        i++;
    } 

    return jsonConfiguration;
}


//********************************************************
// ZONA DE DEFINICIÓN DE MÉTODOS DE ACCESO A LAS VARIABLES
//********************************************************
string Json_interface::getFileURL(){ return fileURL; }
void Json_interface::setFileURL(string data){ fileURL = data; }


