#include <sstream>
#include <iostream>
#include "JsonConfiguration.h"



//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
JsonConfiguration::JsonConfiguration():
    status(true),
    worldConfiguration(WorldConfiguration())
{
    computerConfigurationList_init();
}
JsonConfiguration::JsonConfiguration(bool newStatus, WorldConfiguration newWorldConfiguration, ComputerConfiguration newComputerConfigurationList[COMPUTERCONFIGURATIONLIST_SIZE]):
    status(newStatus),
    worldConfiguration(newWorldConfiguration)
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
    value << "WorldConfiguration{" << endl <<getWorldConfiguration().displayInfo() << endl << "}" <<endl;
    value << "ComputerConfigurationList[ "<<endl;
    for(int i=0 ; i<COMPUTERCONFIGURATIONLIST_SIZE ; i++){
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

WorldConfiguration JsonConfiguration::getWorldConfiguration(){ return worldConfiguration; }
void JsonConfiguration::setWorldConfiguration(WorldConfiguration newWorldConfiguration){ worldConfiguration = newWorldConfiguration; }

ComputerConfiguration * JsonConfiguration::getComputerConfigurationList(){ return computerConfigurationList; }
void JsonConfiguration::setComputerConfigurationList(ComputerConfiguration newList[COMPUTERCONFIGURATIONLIST_SIZE]){
    for (int i=0 ; i<COMPUTERCONFIGURATIONLIST_SIZE ; i++) {
        computerConfigurationList[i] = newList[i];
    }
}
void JsonConfiguration::computerConfigurationList_init(){
    for (int i=0 ; i<COMPUTERCONFIGURATIONLIST_SIZE ; i++) {
        computerConfigurationList[i] = ComputerConfiguration();
    }
}