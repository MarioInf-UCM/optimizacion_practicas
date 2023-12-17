#ifndef WORLDCONFIGURATION_H
#define WORLDCONFIGURATION_H

#include <string>

using namespace std;

class WorldConfiguration{

    private:
        string ID = "";
        unsigned int dimensions = 0;
        string fitnessFunctionID = "";

    public:
        WorldConfiguration();
        WorldConfiguration(string ID, unsigned int dimensions, string fitnessFunctionID);
        ~WorldConfiguration();

        string getID();
        void setID(string newID);

        unsigned int getDimensions();
        void setDimensions(unsigned int newDimensions);

        string getFitnessFunctionID();
        void setFitnessFunctionID(string newFitnessFunctionID);


};



#endif