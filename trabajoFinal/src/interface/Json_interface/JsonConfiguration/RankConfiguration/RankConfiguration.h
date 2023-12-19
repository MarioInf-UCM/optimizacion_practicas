#ifndef RANKCONFIGURATION_H
#define RANKCONFIGURATION_H

#include <string>
#include <limits.h>
#include "libs/ArrayList/ArrayList.h"

using namespace std;


class RankConfiguration{
    
    private:
        bool isDefault = false;
        ArrayList<unsigned int> rankList = ArrayList<unsigned int>();
        string outputFile = "";
        
        string heuristicID = "";       
        unsigned  int iterations = USHRT_MAX;
        unsigned int poblation = 0;
        ArrayList<float> valueList = ArrayList<float>();

    public:
        RankConfiguration();
        RankConfiguration(ArrayList<unsigned int> rankList, string outputFile, string heuristicID, unsigned int poblation, ArrayList<float> valueList);
        ~RankConfiguration();

        string displayInfo();


        bool getIsDefault();
        void setIsDefault(bool isDefault);

        ArrayList<unsigned int> getRankList();
        void setRankList_reference(ArrayList<unsigned int> *newRank);
        void setRankList_duplicate(ArrayList<unsigned int> newRank);
        
        string getOutputFile();
        void setOutputFile(string newOutputFile);

        string getHeuristicID();
        void setHeuristicID(string newHeuristicID);
        
        unsigned int getIterations();
        void setIterations(unsigned int newIterations);
        
        unsigned int getPoblation();
        void setPoblation(unsigned int newPoblation);
        
        ArrayList<float> getValueList();
        void setValueList_reference(ArrayList<float> *newValueList);
        void setValueList_duplicate(ArrayList<float> newValueList);


};

RankConfiguration::RankConfiguration(){
}

RankConfiguration::~RankConfiguration(){
}

#endif