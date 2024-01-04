#include <cmath>
#include "FitnessFunction_pow2.h"

//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
FitnessFunction_pow2::FitnessFunction_pow2():
    FitnessFunction("")
{}
FitnessFunction_pow2::FitnessFunction_pow2(string ID):
    FitnessFunction(ID)
{}

FitnessFunction_pow2::~FitnessFunction_pow2()
{}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
float FitnessFunction_pow2::execFunction(float x){
    return pow(x, 2);
}