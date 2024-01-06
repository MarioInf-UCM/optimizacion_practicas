#include <cmath>
#include "FitnessFunction_Pow2.h"

//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
FitnessFunction_Pow2::FitnessFunction_Pow2():
    FitnessFunction("Pow2")
{}
FitnessFunction_Pow2::FitnessFunction_Pow2(string ID):
    FitnessFunction(ID)
{}

FitnessFunction_Pow2::~FitnessFunction_Pow2()
{}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
float FitnessFunction_Pow2::execFunction(float x){
    return pow(x, 2);
}