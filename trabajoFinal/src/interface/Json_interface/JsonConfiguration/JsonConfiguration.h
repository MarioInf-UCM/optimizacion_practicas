#ifndef JSONCONFIGURATION_H_
#define JSONCONFIGURATION_H_

#include "WorldConfiguration/WorldConfiguration.h"
#include "ComputerConfiguration/ComputerConfiguration.h"

#define COMPUTERCONFIGURATIONLIST_SIZE 16

class JsonConfiguration{
    private:
        bool status;
        WorldConfiguration worldConfiguration;
        ComputerConfiguration computerConfigurationList[COMPUTERCONFIGURATIONLIST_SIZE];
    public:

        JsonConfiguration();
        JsonConfiguration(bool newStatus, WorldConfiguration newWorldConfiguration, ComputerConfiguration newComputerConfigurationList[COMPUTERCONFIGURATIONLIST_SIZE]);
        ~JsonConfiguration();

        string displayInfo();

        bool getStatus();
        void setStatus(bool data);

        WorldConfiguration getWorldConfiguration();
        void setWorldConfiguration(WorldConfiguration newWorldConfiguration);

        ComputerConfiguration *getComputerConfigurationList();
        void setComputerConfigurationList(ComputerConfiguration newList[COMPUTERCONFIGURATIONLIST_SIZE]);
        void computerConfigurationList_init();

};


#endif