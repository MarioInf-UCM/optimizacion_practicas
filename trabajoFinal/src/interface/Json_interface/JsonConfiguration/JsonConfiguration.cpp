#include "JsonConfiguration.h"





//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
JsonConfiguration::JsonConfiguration(){}

JsonConfiguration::~JsonConfiguration(){}



//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
WorldConfiguration JsonConfiguration::getWorldConfiguration(){ return worldConfiguration; }
void JsonConfiguration::sertWorldConfiguration(WorldConfiguration newWorldConfiguration){ worldConfiguration = newWorldConfiguration; }

ArrayList<ComputerConfiguration> JsonConfiguration::getComputerConfigurationList(){}
void JsonConfiguration::setComputerConfigurationList_reference(ArrayList<ComputerConfiguration> *newlist){}
void JsonConfiguration::setComputerConfigurationList_duplicate(ArrayList<ComputerConfiguration> newlist){}