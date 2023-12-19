#include "WorldConfiguration.h"
#include <string>
#include <sstream>

using namespace std;



//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
WorldConfiguration::WorldConfiguration(){}
WorldConfiguration:: WorldConfiguration(string ID, unsigned int dimensions, string fitnessFunctionID){
    setID(ID);
    setDimensions(dimensions);
    setFitnessFunctionID(fitnessFunctionID);
}

WorldConfiguration::~WorldConfiguration(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string WorldConfiguration::displayInfo(){
    stringstream value;
    value << "ID: " << getID() << "    Dimensions: " << getDimensions() << "    FitnessFunctionID: " << getFitnessFunctionID();
    return value.str();
}



//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
string WorldConfiguration::getID() {return ID;}
void WorldConfiguration::setID(string newID) {ID = newID;}


unsigned int WorldConfiguration::getDimensions(){return dimensions;}
void WorldConfiguration::setDimensions(unsigned int newDimensions) {dimensions = newDimensions;}


string WorldConfiguration::getFitnessFunctionID() {return fitnessFunctionID;}
void WorldConfiguration::setFitnessFunctionID(string newFitnessFunction) {fitnessFunctionID = newFitnessFunction;}





