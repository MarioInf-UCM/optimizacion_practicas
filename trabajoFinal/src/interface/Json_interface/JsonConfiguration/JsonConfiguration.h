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
        ComputerConfiguration computerConfiguration;
    
    public:
        JsonConfiguration();
        JsonConfiguration(bool newStatus, WorldConfiguration newWorldConfiguration, ComputerConfiguration computerConfiguration);
        ~JsonConfiguration();

        string displayInfo();

        bool getStatus();
        void setStatus(bool data);

        WorldConfiguration& getWorldConfiguration();
        void setWorldConfiguration(WorldConfiguration newWorldConfiguration);

        ComputerConfiguration& getComputerConfiguration();
        void setComputerConfigurationList(ComputerConfiguration newComputerCnfiguration);

};


#endif