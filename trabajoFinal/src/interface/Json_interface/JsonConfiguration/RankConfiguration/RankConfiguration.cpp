#include "RankConfiguration.h"
#include <string>
#include <sstream>

using namespace std;



//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
RankConfiguration::RankConfiguration(){}
RankConfiguration:: RankConfiguration(ArrayList<unsigned int> rankList, string outputFile, string heuristicID, unsigned int poblation, ArrayList<float> valueList){
    setRankList_duplicate(rankList);
    setOutputFile(outputFile);
    setHeuristicID(heuristicID);
}

RankConfiguration::~RankConfiguration(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string RankConfiguration::displayInfo(){
    stringstream value;
    value << "IsDefault?: " << (getIsDefault()? "true" : false) << "    OutputFile: " << getOutputFile() << "    rankList: ";
    for(int i=0 ; i<getRankList().size() ; i++){
        value << getRankList().get(i);
    }
    value << std::endl;
    
    value << " HeuristicID: " << getHeuristicID() << "    Iterations: " << getIterations() << "    Poblation: " << getPoblation() << "    valueList: ";
    for(int i=0 ; i<getValueList().size() ; i++){
        value << getValueList().get(i);
    }
    value << std::endl;

    return value.str();
}

//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
bool RankConfiguration::getIsDefault(){ return isDefault; }
void RankConfiguration::setIsDefault(bool newIsDefault){ isDefault =newIsDefault; }

ArrayList<unsigned int> RankConfiguration::getRankList() { return rankList; }
void RankConfiguration::setRankList_reference(ArrayList<unsigned int> *newRank) { rankList = *newRank; }
void RankConfiguration::setRankList_duplicate(ArrayList<unsigned int> newRank) { rankList = newRank; }

string RankConfiguration::getOutputFile() { return outputFile; }
void RankConfiguration::setOutputFile(string newOutputFile) { outputFile = newOutputFile; }

string RankConfiguration::getHeuristicID() { return heuristicID; }
void RankConfiguration::setHeuristicID(string newHeuristicID) { heuristicID = newHeuristicID; }

unsigned int RankConfiguration::getIterations() { return iterations; }
void RankConfiguration::setIterations(unsigned int newIterations) { iterations = newIterations; }

unsigned int RankConfiguration::getPoblation() { return poblation; }
void RankConfiguration::setPoblation(unsigned int newPoblation) { poblation = newPoblation; }

ArrayList<float> RankConfiguration::getValueList() { return valueList; }
void RankConfiguration::setValueList_reference(ArrayList<float> *newValueList) { valueList = *newValueList; }
void RankConfiguration::setValueList_duplicate(ArrayList<float> newValueList) { valueList = newValueList; }

