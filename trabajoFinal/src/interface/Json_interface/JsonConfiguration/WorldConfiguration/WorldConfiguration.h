#ifndef WORLDCONFIGURATION_H
#define WORLDCONFIGURATION_H

#include <string>

using namespace std;

class WorldConfiguration{

    private:
        string ID;
        string fitnessFunctionID;
        long double limitUp;
        long double limitDown;
        long double limitRight;
        long double limitLeft;

    public:
        WorldConfiguration();
        WorldConfiguration(string ID, string fitnessFunctionID, long double limitUp, long double limitDown, long double limitLeft, long double limitRight);
        ~WorldConfiguration();

        string displayInfo();



        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************
        string getID() const;
        void setID(string newID);

        string getFitnessFunctionID() const;
        void setFitnessFunctionID(string newFitnessFunctionID);

        long double getLimitUp() const;
        void setLimitUp(long double data);

        long double getLimitDown() const;
        void setLimitDown(long double data);

        long double getLimitRight() const;
        void setLimitRight(long double data);

        long double getLimitLeft() const;
        void setLimitLeft(long double data);

};



#endif