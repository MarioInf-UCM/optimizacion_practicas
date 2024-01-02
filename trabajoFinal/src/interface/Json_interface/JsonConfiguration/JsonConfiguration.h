#ifndef JSONCONFIGURATION_H_
#define JSONCONFIGURATION_H_

#include <vector>

#include "WorldConfiguration/WorldConfiguration.h"
#include "ComputerConfiguration/ComputerConfiguration.h"

using namespace std;


class JsonConfiguration{
    
    private:
        bool status;
        WorldConfiguration worldConfiguration;
        vector<ComputerConfiguration> computerConfigurationList;
    
    public:
        JsonConfiguration();
        JsonConfiguration(bool newStatus, WorldConfiguration newWorldConfiguration, vector<ComputerConfiguration>);
        ~JsonConfiguration();

        string displayInfo();

        bool getStatus();
        void setStatus(bool data);

        WorldConfiguration& getWorldConfiguration();
        void setWorldConfiguration(WorldConfiguration newWorldConfiguration);

        vector<ComputerConfiguration> getComputerConfigurationList() const;
        ComputerConfiguration getComputerConfiguration_byIndex(unsigned int index) const;
        void setComputerConfigurationList(vector<ComputerConfiguration> newList);
        void setComputerConfiguration_byIndex(unsigned int index, ComputerConfiguration value);

};


#endif