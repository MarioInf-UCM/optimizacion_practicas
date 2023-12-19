#include <sstream>
#include "JsonConfiguration.h"


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
JsonConfiguration::JsonConfiguration(){}

JsonConfiguration::~JsonConfiguration(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string JsonConfiguration::displayInfo(){
    stringstream value;
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
WorldConfiguration JsonConfiguration::getWorldConfiguration(){ return worldConfiguration; }
void JsonConfiguration::sertWorldConfiguration(WorldConfiguration newWorldConfiguration){ worldConfiguration = newWorldConfiguration; }

ArrayList<ComputerConfiguration> JsonConfiguration::getComputerConfigurationList(){ return computerConfigurationList; }
void JsonConfiguration::setComputerConfigurationList_reference(ArrayList<ComputerConfiguration> *newlist){ computerConfigurationList = *newlist; }
void JsonConfiguration::setComputerConfigurationList_duplicate(ArrayList<ComputerConfiguration> newlist){ computerConfigurationList = newlist; }