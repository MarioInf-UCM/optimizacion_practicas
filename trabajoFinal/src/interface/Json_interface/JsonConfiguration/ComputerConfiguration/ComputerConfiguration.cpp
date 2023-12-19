#include <string>
#include "ComputerConfiguration.h"
#include "../RankConfiguration/RankConfiguration.h"

using namespace std;



//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
ComputerConfiguration::ComputerConfiguration(){}
ComputerConfiguration::ComputerConfiguration(bool isDefault, string IP, ArrayList<RankConfiguration> rankConfigurationList){
    setIsDefault(isDefault);
    setIP(IP);
    setRankConfigurationList_duplicate(rankConfigurationList);
}
ComputerConfiguration::ComputerConfiguration(bool isDefault, string IP, ArrayList<RankConfiguration> *rankConfigurationList){
    setIsDefault(isDefault);
    setIP(IP);
    setRankConfigurationList_reference(rankConfigurationList);
}


ComputerConfiguration::~ComputerConfiguration(){}



//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
bool ComputerConfiguration::getIsDefault(){ return isDefault; }
void ComputerConfiguration::setIsDefault(bool newIsDefault){ isDefault =newIsDefault; }

string ComputerConfiguration::getIP(){ return IP; }
void ComputerConfiguration::setIP(string newIP){ IP = newIP; }

ArrayList<RankConfiguration> ComputerConfiguration::getRankConfigurationList() { return rankConfigurationList; }
void ComputerConfiguration::setRankConfigurationList_reference(ArrayList<RankConfiguration> *newRank) { rankConfigurationList = *newRank; }
void ComputerConfiguration::setRankConfigurationList_duplicate(ArrayList<RankConfiguration> newRank) { rankConfigurationList = newRank; }