#ifndef COMPUTERCONFIGURATION_H
#define COMPUTERCONFIGURATION_H

#include <string>
#include <limits.h>
#include "../RankConfiguration/RankConfiguration.h"

#define RANKCONFIGURATIONLIST_SIZE 16

using namespace std;

class ComputerConfiguration{

    private:
        bool isDefault;
        string IP;
        RankConfiguration rankConfigurationList[RANKCONFIGURATIONLIST_SIZE];

    public:
        ComputerConfiguration();
        ComputerConfiguration(string IP, RankConfiguration rankConfigurationList[RANKCONFIGURATIONLIST_SIZE]);
        ~ComputerConfiguration();

        string displayInfo();

        bool getIsDefault();
        void setIsDefault(bool isDefault);

        string getIP();
        void setIP(string newIP);
        
        RankConfiguration *getRankConfigurationList();
        void setRankConfigurationList(RankConfiguration newList[RANKCONFIGURATIONLIST_SIZE]);
        void rankConfigurationList_init();

};
#endif


