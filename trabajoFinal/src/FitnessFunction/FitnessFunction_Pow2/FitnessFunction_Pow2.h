#ifndef FITNESSFUNCTION_POW2_H_
#define FITNESSFUNCTION_POW2_H_

#include <iostream>
#include <string>

#include "../FitnessFunction.h"

using namespace std;


class FitnessFunction_Pow2: public FitnessFunction{
        
    public:
        FitnessFunction_Pow2();
        FitnessFunction_Pow2(string ID);
        ~FitnessFunction_Pow2();

        static float execFunction(float x);

        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************

};



#endif