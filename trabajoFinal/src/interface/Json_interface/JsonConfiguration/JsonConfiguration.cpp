#include <sstream>
#include <iostream>
#include "JsonConfiguration.h"


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
JsonConfiguration::JsonConfiguration():
    status(true),
    worldConfiguration(WorldConfiguration()),
    computerConfiguration(ComputerConfiguration())
{}
JsonConfiguration::JsonConfiguration(bool newStatus, WorldConfiguration newWorldConfiguration, ComputerConfiguration computerConfiguration):
    status(newStatus),
    worldConfiguration(newWorldConfiguration),
    computerConfiguration(computerConfiguration)
{}
JsonConfiguration::~JsonConfiguration(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string JsonConfiguration::displayInfo(){
    stringstream value;
    value << "Status: " << (getStatus()? "true" : "false" ) << endl;
    value << "WorldConfiguration{" << endl << "\t" << getWorldConfiguration().displayInfo() << endl << "}" <<endl;
    value << "ComputerConfiguration{" << endl << "\t" << getComputerConfiguration().displayInfo() << "}" << endl;
    return value.str();
}



//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
bool JsonConfiguration::getStatus(){ return status; }
void JsonConfiguration::setStatus(bool data){ status=data; }


WorldConfiguration& JsonConfiguration::getWorldConfiguration() { return worldConfiguration; }
void JsonConfiguration::setWorldConfiguration(WorldConfiguration newWorldConfiguration){ worldConfiguration = newWorldConfiguration; }


ComputerConfiguration& JsonConfiguration::getComputerConfiguration() {return computerConfiguration;}
void JsonConfiguration::setComputerConfigurationList(ComputerConfiguration newComputerCnfiguration){ computerConfiguration = newComputerCnfiguration; }