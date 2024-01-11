#include <cmath>
#include "FitnessFunction_num8.h"

//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
FitnessFunction_num8::FitnessFunction_num8():
    FitnessFunction("num8")
{}
FitnessFunction_num8::FitnessFunction_num8(string ID):
    FitnessFunction(ID)
{}

FitnessFunction_num8::~FitnessFunction_num8()
{}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
float FitnessFunction_num8::execFunction(float x){
    return ( -x * sin(sqrt(abs(x))) );
}