#ifndef RANKCONFIGURATION_H
#define RANKCONFIGURATION_H

#include <string>
#include <limits.h>
#include <vector>


using namespace std;


class RankConfiguration{
    
    private:
        bool isDefault;
        vector<unsigned int> rankList;
        string outputFile;
        
        string heuristicID;
        unsigned int iterations;
        unsigned int poblation;
        unsigned int dimensions;

        vector<float> valueList;

    public:
        RankConfiguration();
        RankConfiguration(vector<unsigned int>rankList, string outputFile, string heuristicID, unsigned int iterations, unsigned int poblation, vector<float> valueList);
        ~RankConfiguration();

        string displayInfo();
        
        vector<char> serialize() const;
        static RankConfiguration deserialize(const vector<char>& buffer);



        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************
        bool getIsDefault() const;
        void setIsDefault(bool isDefault);

        vector<unsigned int>& getRankList();
        unsigned int getRank_byIndex(unsigned int index);
        void setRankList(vector<unsigned int> newList);
        void setRank_byIndex(unsigned int index, unsigned int value);
        
        string getOutputFile() const;
        void setOutputFile(string newOutputFile);

        string getHeuristicID() const;
        void setHeuristicID(string newHeuristicID);
        
        unsigned int getIterations() const;
        void setIterations(unsigned int newIterations);
        
        unsigned int getPoblation() const;
        void setPoblation(unsigned int newPoblation);

        unsigned int getDimensions() const;
        void setDimensions(unsigned int newDimensions);
        
        vector<float>& getValueList();
        float getValue_byIndex(unsigned int index);
        void setValueList(vector<float> newList);
        void setValue_byIndex(unsigned int index, float value);

};

#endif