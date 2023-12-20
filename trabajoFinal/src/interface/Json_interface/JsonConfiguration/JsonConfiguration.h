#ifndef JSONCONFIGURATION_H_
#define JSONCONFIGURATION_H_

#include "WorldConfiguration/WorldConfiguration.h"
#include "ComputerConfiguration/ComputerConfiguration.h"
#include "../../../../libs/ArrayList/ArrayList.h"


class JsonConfiguration{
    private:
        bool status = true;
        WorldConfiguration worldConfiguration = WorldConfiguration();
        ArrayList<ComputerConfiguration> computerConfigurationList;

    public:
        JsonConfiguration();
        ~JsonConfiguration();

        string displayInfo();

        bool getStatus();
        void setStatus(bool data);

        WorldConfiguration getWorldConfiguration();
        void setWorldConfiguration(WorldConfiguration newWorldConfiguration);

        ArrayList<ComputerConfiguration> getComputerConfigurationList();
        void setComputerConfigurationList_reference(ArrayList<ComputerConfiguration> *newlist);
        void setComputerConfigurationList_duplicate(ArrayList<ComputerConfiguration> newlist);

};


#endif