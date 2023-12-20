#include "WorldConfiguration.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;



//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
WorldConfiguration::WorldConfiguration(){
    setID("");
    setDimensions(0);
    setFitnessFunctionID("");
}
WorldConfiguration::WorldConfiguration(string ID, unsigned int dimensions, string fitnessFunctionID){
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


unsigned int WorldConfiguration::getDimensions(){return this->dimensions;}
void WorldConfiguration::setDimensions(unsigned int newDimensions) {
    cout <<"pepe1: " << newDimensions << endl;
    this->dimensions = newDimensions;
    cout <<"pepe2: " << dimensions << endl;
    }


string WorldConfiguration::getFitnessFunctionID() {return fitnessFunctionID;}
void WorldConfiguration::setFitnessFunctionID(string newFitnessFunction) {fitnessFunctionID = newFitnessFunction;}





