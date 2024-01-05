#ifndef COMPUTERCONFIGURATION_H
#define COMPUTERCONFIGURATION_H

#include <string>
#include <vector>
#include <limits.h>

#include "../RankConfiguration/RankConfiguration.h"

using namespace std;


class ComputerConfiguration{

    private:
        string IP;
        string logCommonFile;
        vector<RankConfiguration> rankConfigurationList;

    public:
        ComputerConfiguration();
        ComputerConfiguration(string IP, vector<RankConfiguration> rankConfigurationList, string logCommonFile);
        ~ComputerConfiguration();


        string displayInfo();

        string getIP() const;
        void setIP(string newIP);

        string getLogCommonFile() const;
        void setLogCommonFile(string data);
        
        vector<RankConfiguration>& getRankConfigurationList();
        RankConfiguration getRankConfiguration_byIndex(unsigned int index);
        void setRankConfigurationList(vector<RankConfiguration> newList);
        void setRankConfiguration_byIndex(unsigned int index, RankConfiguration value);

};
#endif


