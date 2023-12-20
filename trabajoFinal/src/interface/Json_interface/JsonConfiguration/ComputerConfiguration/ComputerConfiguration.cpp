#include <string>
#include <sstream>
#include "ComputerConfiguration.h"
#include "../RankConfiguration/RankConfiguration.h"

using namespace std;

template class ArrayList<RankConfiguration>;


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
ComputerConfiguration::ComputerConfiguration(){
    setIsDefault(false);
    setIP("0.0.0.0");
    rankConfigurationList = ArrayList<RankConfiguration>();

}
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




//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string ComputerConfiguration::displayInfo(){
    stringstream value;
    value << "IsDefault?: " << (getIsDefault()? "true" : "false") << "    IP: " << getIP() << "    rankConfigurationList{" << std::endl;
    for(int i=0 ; i<getRankConfigurationList().size() ; i++){
        value << getRankConfigurationList().get(i)->data.displayInfo();
        value << endl << endl;
    }
    value << "}";
    return value.str();
}



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


