#ifndef FITNESSFUNCTION_H_
#define FITNESSFUNCTION_H_

#include <iostream>
#include <string>

using namespace std;


class FitnessFunction{
    private:
        const string ID;
        

    public:
        FitnessFunction();
        FitnessFunction(string ID);
        ~FitnessFunction();

        float execFunction(float x);

        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************
        string getID() const;
};



#endif