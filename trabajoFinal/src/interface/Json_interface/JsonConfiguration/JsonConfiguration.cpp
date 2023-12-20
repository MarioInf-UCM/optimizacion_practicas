#include <sstream>
#include "JsonConfiguration.h"
#include "../../../../libs/ArrayList/ArrayList.h"
#include "../../../../libs/ArrayList/ArrayList.cpp"

template class ArrayList<ComputerConfiguration>;


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
JsonConfiguration::JsonConfiguration(){
    setStatus(true);
    setWorldConfiguration(WorldConfiguration());
    computerConfigurationList = ArrayList<ComputerConfiguration>();
}
JsonConfiguration::~JsonConfiguration(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string JsonConfiguration::displayInfo(){
    stringstream value;
    value << "Status: " << (getStatus()? "true" : "false" ) << endl;
    value << "WorldConfiguration{" << endl <<getWorldConfiguration().displayInfo() << endl << "}" <<endl;
    value << "ComputerConfigurationList{" <<endl;
    for(int i=0 ; i<getComputerConfigurationList().size() ; i++){
        value << getComputerConfigurationList().get(i)->data.displayInfo();
    }
    value << "}";
    return value.str();
}



//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
bool JsonConfiguration::getStatus(){ return status; }
void JsonConfiguration::setStatus(bool data){ status=data; }

WorldConfiguration JsonConfiguration::getWorldConfiguration(){ return this->worldConfiguration; }
void JsonConfiguration::setWorldConfiguration(WorldConfiguration newWorldConfiguration){ this->worldConfiguration = newWorldConfiguration; }

ArrayList<ComputerConfiguration> JsonConfiguration::getComputerConfigurationList(){ return computerConfigurationList; }
void JsonConfiguration::setComputerConfigurationList_reference(ArrayList<ComputerConfiguration> *newlist){ computerConfigurationList = *newlist; }
void JsonConfiguration::setComputerConfigurationList_duplicate(ArrayList<ComputerConfiguration> newlist){ computerConfigurationList = newlist; }