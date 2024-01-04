#ifndef FITNESSFUNCTION_POW2_H_
#define FITNESSFUNCTION_POW2_H_

#include <iostream>
#include <string>

#include "../FitnessFunction.h"

using namespace std;


class FitnessFunction_pow2: public FitnessFunction{
        
    public:
        FitnessFunction_pow2();
        FitnessFunction_pow2(string ID);
        ~FitnessFunction_pow2();

        float execFunction(float x);

        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************

};



#endif