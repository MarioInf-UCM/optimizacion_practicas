#include "WorldConfiguration.h"
#include <string>
#include <sstream>
#include <iostream>

using namespace std;



//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
WorldConfiguration::WorldConfiguration():
    ID(""), 
    fitnessFunctionID(""),
    limitUp(0),
    limitDown(0),
    limitLeft(0),
    limitRight(0)
{}

WorldConfiguration::WorldConfiguration(string ID, string fitnessFunctionID, long double limitUp, long double limitDown, long double limitLeft, long double limitRight):
    ID(ID), 
    fitnessFunctionID(fitnessFunctionID),
    limitUp(limitUp),
    limitDown(limitDown),
    limitLeft(limitLeft),
    limitRight(limitRight)
{}

WorldConfiguration::~WorldConfiguration(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string WorldConfiguration::displayInfo(){
    stringstream value;
    value << "\tID: " << getID() << "    FitnessFunctionID: " << getFitnessFunctionID() << endl;
    value << "\tLimitUp: " << getLimitUp() << "    LimitDown: " << getLimitDown() << "    LimitRight: " << getLimitRight() << "    Limitleft: " << getLimitLeft() << endl;
    return value.str();
}



//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
string WorldConfiguration::getID() const {return ID;}
void WorldConfiguration::setID(string newID) {ID = newID;}

string WorldConfiguration::getFitnessFunctionID() const {return fitnessFunctionID;}
void WorldConfiguration::setFitnessFunctionID(string newFitnessFunction) {fitnessFunctionID = newFitnessFunction;}

long double WorldConfiguration::getLimitUp() const { return limitUp; }
void WorldConfiguration::setLimitUp(long double data){ limitUp = data; }

long double WorldConfiguration::getLimitDown() const { return limitDown; }
void WorldConfiguration::setLimitDown(long double data){limitDown = data; }

long double WorldConfiguration::getLimitRight() const { return limitRight; }
void WorldConfiguration::setLimitRight(long double data){ limitRight = data; }

long double WorldConfiguration::getLimitLeft() const { return limitLeft; }
void WorldConfiguration::setLimitLeft(long double data){ limitLeft = data; }



