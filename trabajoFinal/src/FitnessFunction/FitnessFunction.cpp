#include "FitnessFunction.h"


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
FitnessFunction::FitnessFunction():
    ID("")
{}
FitnessFunction::FitnessFunction(string ID):
    ID(ID)
{}

FitnessFunction::~FitnessFunction(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
float FitnessFunction::execFunction(float x){
    return x;
}



//**********************************************
//* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
//**********************************************
string FitnessFunction::getID() const{ return ID; }