#ifndef FITNESSFUNCTION_NUM8_H_
#define FITNESSFUNCTION_NUM8_H_

#include <iostream>
#include <string>

#include "../FitnessFunction.h"

using namespace std;


class FitnessFunction_num8: public FitnessFunction{
        
    public:
        FitnessFunction_num8();
        FitnessFunction_num8(string ID);
        ~FitnessFunction_num8();

        static float execFunction(float x);

        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************

};



#endif