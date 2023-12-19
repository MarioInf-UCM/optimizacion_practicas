#include <iostream>
#include <fstream>
#include <string>

#include "Json_interface.h"
#include "JsonConfiguration/JsonConfiguration.h"

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

    ifstream file(getFileURL());
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo JSON.\n" << endl;
        return;
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
        std::cerr << "Error al parsear el archivo JSON: " << errs << std::endl;
        return;
    }
    file.close();
    

    JsonConfiguration jsonConfiguration = JsonConfiguration();
    ComputerConfiguration computerConfigurationTemp;
    RankConfiguration rankConfigurationTemp;

    jsonConfiguration.getWorldConfiguration().setID(root["worldConfiguration"]["id"].asString());
    jsonConfiguration.getWorldConfiguration().setDimensions(root["worldConfiguration"]["dimensions"].asInt());
    jsonConfiguration.getWorldConfiguration().setFitnessFunctionID(root["worldConfiguration"]["fitnessFunctionID"].asString());

    for (const auto &computerConfig : root["computerConfiguration"]) {
        computerConfigurationTemp = ComputerConfiguration();
        computerConfigurationTemp.setIsDefault(computerConfig["isDefault?"].asBool());
        computerConfigurationTemp.setIP(computerConfig["IP"].asString());

        for (const auto &rankConfig : computerConfig["rankConfigurationList"]) {
            rankConfigurationTemp = RankConfiguration();
            rankConfigurationTemp.setIsDefault(rankConfig["isDefault?"].asBool());
            for (const auto &rank : rankConfig["rankList"]) {
                rankConfigurationTemp.getRankList().add(rank.asInt());
            }

            rankConfigurationTemp.setOutputFile(rankConfig["outFIleURL"].asString());
            rankConfigurationTemp.setHeuristicID(rankConfig["heuristicID"].asString());
            rankConfigurationTemp.setIterations(rankConfig["iterations"].asInt());
            rankConfigurationTemp.setPoblation(rankConfig["poblation"].asInt());

            for (const auto &value : rankConfig["valueList"]) {
                rankConfigurationTemp.getValueList().add(value.asFloat());
            }

            computerConfigurationTemp.getRankConfigurationList().add(rankConfigurationTemp);
        }

        jsonConfiguration.getComputerConfigurationList().add(computerConfigurationTemp);
    }

    return jsonConfiguration;
}


//********************************************************
// ZONA DE DEFINICIÓN DE MÉTODOS DE ACCESO A LAS VARIABLES
//********************************************************
string Json_interface::getFileURL(void){ return fileURL; }
void Json_interface::setFileURL(string data){ fileURL = data; }
