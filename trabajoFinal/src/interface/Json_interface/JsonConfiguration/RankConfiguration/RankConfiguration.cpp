#include "RankConfiguration.h"
#include <string>
#include <sstream>
#include <vector>

using namespace std;


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
RankConfiguration::RankConfiguration():
    isDefault(false),
    rankList(vector<unsigned int>()),
    outputFile(""),
    heuristicID(""),
    iterations(USHRT_MAX),
    poblation(0)
{}
RankConfiguration::RankConfiguration(vector<unsigned int>rankList, string outputFile, string heuristicID, unsigned int iterations, unsigned int poblation, vector<float> valueList):
    isDefault(false),
    rankList(vector<unsigned int>()),
    outputFile(outputFile),
    heuristicID(heuristicID),
    poblation(poblation),
    iterations(iterations),
    valueList(valueList)
{
    setRankList(rankList);
}

RankConfiguration::~RankConfiguration(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string RankConfiguration::displayInfo(){
    stringstream value;

    if(!getIsDefault()){
        value << "\t\tRankList: ";
        for(int i=0 ; i<getRankList().size() ; i++){
            if(i == (getRankList().size()-1)){
                value << rankList[i] << ends;
            }else{
                value << rankList[i] << ", " << ends;
            }
        }
        value <<" ]" <<endl;
        
        value << "    OutputFile: " << getOutputFile() << "    HeuristicID: " << getHeuristicID() << "    Iterations: " << getIterations() << "    Poblation: " << getPoblation() << "    valueList[ ";
        for(int i=0 ; i<getValueList().size() ; i++){
            if(i == (getRankList().size()-1)){
                value << valueList[i] << ends;
            }else{
                value << valueList[i] << ", " << ends;
            }
        }
        value <<" ]" <<endl;
    }

    return value.str();
}

//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
bool RankConfiguration::getIsDefault() const { return isDefault; }
void RankConfiguration::setIsDefault(bool newIsDefault){ isDefault =newIsDefault; }


vector<unsigned int> RankConfiguration::getRankList() const { return rankList; }
unsigned int RankConfiguration::getRank_byIndex(unsigned int index) const { 
    return getRankList()[index];
}
void RankConfiguration::setRankList(vector<unsigned int> newList){
    rankList.clear();
    for (int i=0 ; i<newList.size() ; i++) {
    rankList.push_back(newList[i]);
    }
}
void RankConfiguration::setRank_byIndex(unsigned int index, unsigned int value){
    rankList[index] = value;
}


string RankConfiguration::getOutputFile() const { return outputFile; }
void RankConfiguration::setOutputFile(string newOutputFile) { outputFile = newOutputFile; }


string RankConfiguration::getHeuristicID() const { return heuristicID; }
void RankConfiguration::setHeuristicID(string newHeuristicID) { heuristicID = newHeuristicID; }


unsigned int RankConfiguration::getIterations() const { return iterations; }
void RankConfiguration::setIterations(unsigned int newIterations) { iterations = newIterations; }


unsigned int RankConfiguration::getPoblation() const { return poblation; }
void RankConfiguration::setPoblation(unsigned int newPoblation) { poblation = newPoblation; }


vector<float> RankConfiguration::getValueList() const { return valueList; }
float RankConfiguration::getValue_byIndex(unsigned int index) const {
    return getValueList()[index];
}
void RankConfiguration::setValueList(vector<float> newList){
    getValueList().clear();
    for (int i=0 ; i<newList.size() ; i++) {
        getValueList().push_back(newList[i]);
    }
}
void RankConfiguration::setValue_byIndex(unsigned int index, float value){
    getValueList()[index] = value;
}
