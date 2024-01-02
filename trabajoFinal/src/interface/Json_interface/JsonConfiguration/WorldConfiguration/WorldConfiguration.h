#ifndef WORLDCONFIGURATION_H
#define WORLDCONFIGURATION_H

#include <string>

using namespace std;

class WorldConfiguration{

    private:
        string ID;
        unsigned int dimensions;
        string fitnessFunctionID;

    public:
        WorldConfiguration();
        WorldConfiguration(string ID, unsigned int dimensions, string fitnessFunctionID);
        ~WorldConfiguration();

        string displayInfo();



        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************
        string getID() const;
        void setID(string newID);

        unsigned int getDimensions() const;
        void setDimensions(unsigned int newDimensions);

        string getFitnessFunctionID() const;
        void setFitnessFunctionID(string newFitnessFunctionID);


};



#endif