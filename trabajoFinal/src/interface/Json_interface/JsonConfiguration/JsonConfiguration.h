#ifndef JSONCONFIGURATION_H_
#define JSONCONFIGURATION_H_

#include "WorldConfiguration/WorldConfiguration.h"
#include "ComputerConfiguration/ComputerConfiguration.h"

class JsonConfiguration{
    private:
        WorldConfiguration worldConfiguration = WorldConfiguration();
        ArrayList<ComputerConfiguration> computerConfigurationList = ArrayList<ComputerConfiguration>();

    public:
        JsonConfiguration();
        ~JsonConfiguration();

        WorldConfiguration getWorldConfiguration();
        void sertWorldConfiguration(WorldConfiguration newWorldConfiguration);

        ArrayList<ComputerConfiguration> getComputerConfigurationList();
        void setComputerConfigurationList_reference(ArrayList<ComputerConfiguration> *newlist);
        void setComputerConfigurationList_duplicate(ArrayList<ComputerConfiguration> newlist);

};


#endif