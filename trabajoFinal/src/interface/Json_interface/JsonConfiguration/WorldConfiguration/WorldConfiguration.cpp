#include "WorldConfiguration.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;



//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
WorldConfiguration::WorldConfiguration():
    ID("pepe"), 
    dimensions(0), 
    fitnessFunctionID("")
{}

WorldConfiguration::WorldConfiguration(string ID, unsigned int dimensions, string fitnessFunctionID):
    ID(ID), 
    dimensions(dimensions), 
    fitnessFunctionID(fitnessFunctionID)
{}

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
string WorldConfiguration::getID() const {return ID;}
void WorldConfiguration::setID(string newID) {ID = newID;}


unsigned int WorldConfiguration::getDimensions() const {return dimensions;}
void WorldConfiguration::setDimensions(unsigned int newDimensions) {dimensions = newDimensions;}


string WorldConfiguration::getFitnessFunctionID() const {return fitnessFunctionID;}
void WorldConfiguration::setFitnessFunctionID(string newFitnessFunction) {fitnessFunctionID = newFitnessFunction;}





