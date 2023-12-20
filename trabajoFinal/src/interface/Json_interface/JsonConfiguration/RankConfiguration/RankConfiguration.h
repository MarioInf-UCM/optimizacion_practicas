#ifndef RANKCONFIGURATION_H
#define RANKCONFIGURATION_H

#include <string>
#include <limits.h>

#define RANKLIST_SIZE 16
#define VALUELIST_SIZE 10

using namespace std;


class RankConfiguration{
    
    private:
        bool isDefault;
        unsigned int rank;
        string outputFile;
        
        string heuristicID;       
        unsigned  int iterations;
        unsigned int poblation;
        float valueList[VALUELIST_SIZE];

    public:
        RankConfiguration();
        RankConfiguration(unsigned int rank, string outputFile, string heuristicID, unsigned int poblation, float valueList[VALUELIST_SIZE]);
        ~RankConfiguration();

        string displayInfo();



        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************
        bool getIsDefault();
        void setIsDefault(bool isDefault);

        unsigned int getRank();
        void setRank(unsigned int newRank);
        
        string getOutputFile();
        void setOutputFile(string newOutputFile);

        string getHeuristicID();
        void setHeuristicID(string newHeuristicID);
        
        unsigned int getIterations();
        void setIterations(unsigned int newIterations);
        
        unsigned int getPoblation();
        void setPoblation(unsigned int newPoblation);
        
        float *getValueList();
        void setValueList(float newList[VALUELIST_SIZE]);
        void setValue_byIndex(unsigned int index, float value);
        void valueList_init();

};

#endif