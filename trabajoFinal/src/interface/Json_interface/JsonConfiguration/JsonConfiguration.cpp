#include <sstream>
#include <iostream>
#include "JsonConfiguration.h"


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
JsonConfiguration::JsonConfiguration():
    status(true),
    worldConfiguration(WorldConfiguration()),
    computerConfigurationList(vector<ComputerConfiguration>())
{}
JsonConfiguration::JsonConfiguration(bool newStatus, WorldConfiguration newWorldConfiguration, vector<ComputerConfiguration> newComputerConfigurationList):
    status(newStatus),
    worldConfiguration(newWorldConfiguration),
    computerConfigurationList(vector<ComputerConfiguration>())
{
    setComputerConfigurationList(newComputerConfigurationList);
}
JsonConfiguration::~JsonConfiguration(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string JsonConfiguration::displayInfo(){
    stringstream value;
    value << "Status: " << (getStatus()? "true" : "false" ) << endl;
    value << "WorldConfiguration{" << endl << getWorldConfiguration().displayInfo() << endl << "}" <<endl;
    value << "ComputerConfigurationList[ "<<endl;
    for(int i=0 ; i<getComputerConfigurationList().size() ; i++){
        value << "\t" << computerConfigurationList[i].displayInfo();
    }
    value << " ]" << ends;
    return value.str();
}



//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
bool JsonConfiguration::getStatus(){ return status; }
void JsonConfiguration::setStatus(bool data){ status=data; }


WorldConfiguration& JsonConfiguration::getWorldConfiguration() { return worldConfiguration; }
void JsonConfiguration::setWorldConfiguration(WorldConfiguration newWorldConfiguration){ worldConfiguration = newWorldConfiguration; }


vector<ComputerConfiguration> JsonConfiguration::getComputerConfigurationList() const {return computerConfigurationList;}
ComputerConfiguration JsonConfiguration::getComputerConfiguration_byIndex(unsigned int index) const {
    return getComputerConfigurationList()[index];
}
void JsonConfiguration::setComputerConfigurationList(vector<ComputerConfiguration> newList){
    getComputerConfigurationList().clear();
    for (int i=0 ; i<newList.size() ; i++) {
        getComputerConfigurationList().push_back(newList[i]);
    }
}
void JsonConfiguration::setComputerConfiguration_byIndex(unsigned int index, ComputerConfiguration value){
    getComputerConfigurationList()[index] = value;
}