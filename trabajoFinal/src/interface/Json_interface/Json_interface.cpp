#include <iostream>
#include <fstream>
#include <string>
#include <jsoncpp/json/json.h>

#include "Json_interface.h"
#include "JsonConfiguration/JsonConfiguration.h"
#include "../../../libs/ArrayList/ArrayList.h"
#include "../../../libs/ArrayList/ArrayList.cpp"

using namespace std;
using namespace Json;

template class ArrayList<RankConfiguration>;
template class ArrayList<ComputerConfiguration>;





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

    JsonConfiguration jsonConfiguration;
    ifstream file(getFileURL());
    if (!file.is_open()) {
        cerr << "Error al abrir el archivo JSON (" << getFileURL() << ")"  << endl;
        jsonConfiguration.setStatus(false);
        return jsonConfiguration;
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
    

    jsonConfiguration.getWorldConfiguration().setID(root["worldConfiguration"]["id"].asString());
    jsonConfiguration.getWorldConfiguration().setDimensions(root["worldConfiguration"]["dimensions"].asUInt());

    jsonConfiguration.setStatus(true);
    cout << "status:" <<jsonConfiguration.getStatus() <<endl;
    jsonConfiguration.setStatus(false);
    cout << "status" <<jsonConfiguration.getStatus() <<endl;

    jsonConfiguration.getWorldConfiguration().setFitnessFunctionID("JUANJO");
    cout << "fitness" << jsonConfiguration.getWorldConfiguration().getFitnessFunctionID() << endl;

    cout << "dimensiones:"<< root["worldConfiguration"]["dimensions"].asUInt() << endl;
    cout << "dimensiones: " <<jsonConfiguration.getWorldConfiguration().getDimensions() <<endl;

    jsonConfiguration.getWorldConfiguration().setFitnessFunctionID(root["worldConfiguration"]["fitnessFunctionID"].asString());


    ComputerConfiguration computerConfigurationTemp;
    RankConfiguration rankConfigurationTemp;

    for (const auto &computerConfig : root["computerConfiguration"]) {
        computerConfigurationTemp = ComputerConfiguration();
        computerConfigurationTemp.setIsDefault(computerConfig["isDefault?"].asBool());
        computerConfigurationTemp.setIP(computerConfig["IP"].asString());

        for (const auto &rankConfig : computerConfig["rankConfigurationList"]) {
            rankConfigurationTemp = RankConfiguration();
            rankConfigurationTemp.setIsDefault(rankConfig["isDefault?"].asBool());
            for (const auto &rank : rankConfig["rankList"]) {
                rankConfigurationTemp.getRankList().add(rank.asUInt());
            }

            rankConfigurationTemp.setOutputFile(rankConfig["outFIleURL"].asString());
            rankConfigurationTemp.setHeuristicID(rankConfig["heuristicID"].asString());
            rankConfigurationTemp.setIterations(rankConfig["iterations"].asUInt());
            rankConfigurationTemp.setPoblation(rankConfig["poblation"].asUInt());

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
string Json_interface::getFileURL(){ return fileURL; }
void Json_interface::setFileURL(string data){ fileURL = data; }


