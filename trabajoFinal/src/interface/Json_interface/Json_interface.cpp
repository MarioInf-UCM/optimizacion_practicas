#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
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
JsonConfiguration Json_interface::getJSONConfiguration_FromFile(vector<string>& ipv4Addresses, vector<string>& ipv6Addresses) {

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
    
    jsonConfiguration.getWorldConfiguration().setFitnessFunctionID(root["worldConfiguration"]["fitnessFunctionID"].asString());
    jsonConfiguration.getWorldConfiguration().setID(root["worldConfiguration"]["id"].asString());
    jsonConfiguration.getWorldConfiguration().setDimensions(root["worldConfiguration"]["dimensions"].asUInt());
   
    Value computerConfigurationSelected = Value::null;
    for (const auto &computerConfig : root["computerConfiguration"]) {
        if(checkIp(ipv4Addresses, computerConfig["IP"].asString()) || checkIp(ipv6Addresses, computerConfig["IP"].asString())){
            computerConfigurationSelected = computerConfig;
            break;
        }
    }
    if(computerConfigurationSelected == Value::null){
        cerr << "No se encontro ninguna configuración compatible con las direcciones IP del equipo." << endl ;
        jsonConfiguration.setStatus(false);
        return jsonConfiguration;
    }

    cout << "ENCONTRADA CONFIGURACIÓN IP:" << computerConfigurationSelected["IP"].asString() << endl << endl;



/*  

    int i=0, j=0, k=0;
        } */
       // jsonConfiguration.getComputerConfigurationList()[i].setIP(computerConfig["IP"].asString());

        /*
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
        */
      


    return jsonConfiguration;
}


bool Json_interface::checkIp(vector<string>& addressList, string concretAddress){
    auto iterador = find(addressList.begin(), addressList.end(), concretAddress);
    if (iterador != addressList.end()) {
        int posicion = distance(addressList.begin(), iterador);
        return true;
    }
    return false;
}



//********************************************************
// ZONA DE DEFINICIÓN DE MÉTODOS DE ACCESO A LAS VARIABLES
//********************************************************
string Json_interface::getFileURL(){ return fileURL; }
void Json_interface::setFileURL(string data){ fileURL = data; }


