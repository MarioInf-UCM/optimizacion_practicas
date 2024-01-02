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
        vector<RankConfiguration> rankConfigurationList;

    public:
        ComputerConfiguration();
        ComputerConfiguration(string IP, vector<RankConfiguration> rankConfigurationList);
        ~ComputerConfiguration();


        string displayInfo();

        string getIP() const;
        void setIP(string newIP);
        
        vector<RankConfiguration> getRankConfigurationList() const;
        RankConfiguration getRankConfiguration_byIndex(unsigned int index) const;
        void setRankConfigurationList(vector<RankConfiguration> newList);
        void setRankConfiguration_byIndex(unsigned int index, RankConfiguration value);

};
#endif


