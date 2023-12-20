#include <string>
#include <sstream>
#include "ComputerConfiguration.h"
#include "../RankConfiguration/RankConfiguration.h"

using namespace std;

//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
ComputerConfiguration::ComputerConfiguration():
    isDefault(true),
    IP("0.0.0.0")
{
    rankConfigurationList_init();
}
ComputerConfiguration::ComputerConfiguration(string IP, RankConfiguration rankConfigurationList[RANKCONFIGURATIONLIST_SIZE]):
    isDefault(false),
    IP(IP)
{
    setRankConfigurationList(rankConfigurationList);
}


ComputerConfiguration::~ComputerConfiguration(){}




//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string ComputerConfiguration::displayInfo(){
    stringstream value;
    if(!getIsDefault()){
        value << "IP: " << getIP() << "    rankConfigurationList{" << std::endl;
        for(int i=0 ; i<RANKCONFIGURATIONLIST_SIZE ; i++){
            value << rankConfigurationList[i].displayInfo();
        }
        value << endl << "}" << ends;
    }
    return value.str();
}



//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
bool ComputerConfiguration::getIsDefault(){ return isDefault; }
void ComputerConfiguration::setIsDefault(bool newIsDefault){ isDefault =newIsDefault; }

string ComputerConfiguration::getIP(){ return IP; }
void ComputerConfiguration::setIP(string newIP){ IP = newIP; }

RankConfiguration *ComputerConfiguration::getRankConfigurationList(){ return rankConfigurationList; }
void ComputerConfiguration::setRankConfigurationList(RankConfiguration newList[RANKCONFIGURATIONLIST_SIZE]){
    for (int i = 0 ; i<RANKCONFIGURATIONLIST_SIZE ; i++) {
        rankConfigurationList[i] = newList[i];
    }
}
void ComputerConfiguration::rankConfigurationList_init(){
    for (int i=0 ; i<RANKCONFIGURATIONLIST_SIZE ; i++) {
        rankConfigurationList[i] = RankConfiguration();
    } 
}


