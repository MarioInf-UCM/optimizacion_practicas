#include "RankConfiguration.h"
#include <string>

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


//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************

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

