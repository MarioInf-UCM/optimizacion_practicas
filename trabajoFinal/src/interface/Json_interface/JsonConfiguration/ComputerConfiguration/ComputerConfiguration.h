#ifndef COMPUTERCONFIGURATION_H
#define COMPUTERCONFIGURATION_H

#include <string>
#include <limits.h>
#include "../RankConfiguration/RankConfiguration.h"
#include "../../../../../libs/ArrayList/ArrayList.h"

using namespace std;

class ComputerConfiguration{

    private:
        bool isDefault;
        string IP;
        ArrayList<RankConfiguration> rankConfigurationList;

    public:
        ComputerConfiguration();
        ComputerConfiguration(bool isDefault, string IP, ArrayList<RankConfiguration> rankConfigurationList);
        ComputerConfiguration(bool isDefault, string IP, ArrayList<RankConfiguration> *rankConfigurationList);
        ~ComputerConfiguration();

        string displayInfo();

        bool getIsDefault();
        void setIsDefault(bool isDefault);

        string getIP();
        void setIP(string newIP);
        
        ArrayList<RankConfiguration> getRankConfigurationList();
        void setRankConfigurationList_reference(ArrayList<RankConfiguration> *newRank);
        void setRankConfigurationList_duplicate(ArrayList<RankConfiguration> newRank);

};
#endif


