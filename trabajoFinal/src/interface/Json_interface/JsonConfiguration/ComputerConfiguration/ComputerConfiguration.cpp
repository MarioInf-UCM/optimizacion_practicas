#include <string>
#include <sstream>
#include <vector>

#include "ComputerConfiguration.h"
#include "../RankConfiguration/RankConfiguration.h"

using namespace std;

//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
ComputerConfiguration::ComputerConfiguration():
    IP("0.0.0.0"),
    logCommonFile(),
    rankConfigurationList(vector<RankConfiguration>())
{}
ComputerConfiguration::ComputerConfiguration(string IP, vector<RankConfiguration> rankConfigurationList, string logCommonFile):
    IP(IP),
    logCommonFile(logCommonFile),
    rankConfigurationList(vector<RankConfiguration>())
{
    setRankConfigurationList(rankConfigurationList);
}
ComputerConfiguration::~ComputerConfiguration(){}




//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string ComputerConfiguration::displayInfo(){
    stringstream value;
    value << "\tIP: " << getIP() << "    LogCommonFile: " << getLogCommonFile() << endl;
    value << "\trankConfigurationList[" << endl;
    for(int i=0 ; i<getRankConfigurationList().size() ; i++){
        value << rankConfigurationList[i].displayInfo();
    }
    value << "\t]" << endl;
    return value.str();
}



//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
string ComputerConfiguration::getIP() const { return IP; }
void ComputerConfiguration::setIP(string newIP){ IP = newIP; }

string ComputerConfiguration::getLogCommonFile() const { return logCommonFile; }
void ComputerConfiguration::setLogCommonFile(string data){ logCommonFile = data; }


vector<RankConfiguration>& ComputerConfiguration::getRankConfigurationList() { return rankConfigurationList; }
RankConfiguration ComputerConfiguration::getRankConfiguration_byIndex(unsigned int index) {
    return getRankConfigurationList()[index];
}
void ComputerConfiguration::setRankConfigurationList(vector<RankConfiguration> newList){
    getRankConfigurationList().clear();
    for (int i=0 ; i<newList.size() ; i++) {
        getRankConfigurationList().push_back(newList[i]);
    }
}
void ComputerConfiguration::setRankConfiguration_byIndex(unsigned int index, RankConfiguration value){
    getRankConfigurationList()[index] = value;
}

