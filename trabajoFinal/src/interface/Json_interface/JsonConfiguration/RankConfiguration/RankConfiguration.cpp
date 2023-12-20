#include "RankConfiguration.h"
#include <string>
#include <sstream>

using namespace std;


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
RankConfiguration::RankConfiguration():
    isDefault(true),
    rank(0),
    outputFile(""),
    heuristicID(""),
    iterations(USHRT_MAX),
    poblation(0)
{
    valueList_init();
}
RankConfiguration::RankConfiguration(unsigned int rank, string outputFile, string heuristicID, unsigned int poblation, float valueList[VALUELIST_SIZE]):
    isDefault(false),
    outputFile(outputFile),
    heuristicID(heuristicID)
{
    setValueList(valueList);
}

RankConfiguration::~RankConfiguration(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
string RankConfiguration::displayInfo(){
    stringstream value;

    if(!getIsDefault()){
        value << "\t\tRank: " << getRank() << "    OutputFile: " << getOutputFile() << 
            "    HeuristicID: " << getHeuristicID() << "    Iterations: " << getIterations() << "    Poblation: " << getPoblation() << "    valueList[ ";
        for(int i=0 ; i<VALUELIST_SIZE ; i++){
            value << valueList[i] << ", " << ends;
        }
        value <<" ]" <<endl;
    }

    return value.str();
}

//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
bool RankConfiguration::getIsDefault(){ return isDefault; }
void RankConfiguration::setIsDefault(bool newIsDefault){ isDefault =newIsDefault; }

unsigned int RankConfiguration::getRank(){ return rank; }
void RankConfiguration::setRank(unsigned int newRank){ rank = newRank; }

string RankConfiguration::getOutputFile() { return outputFile; }
void RankConfiguration::setOutputFile(string newOutputFile) { outputFile = newOutputFile; }

string RankConfiguration::getHeuristicID() { return heuristicID; }
void RankConfiguration::setHeuristicID(string newHeuristicID) { heuristicID = newHeuristicID; }

unsigned int RankConfiguration::getIterations() { return iterations; }
void RankConfiguration::setIterations(unsigned int newIterations) { iterations = newIterations; }

unsigned int RankConfiguration::getPoblation() { return poblation; }
void RankConfiguration::setPoblation(unsigned int newPoblation) { poblation = newPoblation; }

float *RankConfiguration::getValueList(){ return valueList; }
void RankConfiguration::setValueList(float newList[VALUELIST_SIZE]){
    for (int i=0 ; i<VALUELIST_SIZE ; i++) {
        valueList[i] = newList[i];
    }
}
void RankConfiguration::setValue_byIndex(unsigned int index, float value){
    valueList[index] = value;
}
void RankConfiguration::valueList_init(){
    for (int i=0 ; i<VALUELIST_SIZE ; i++) {
        valueList[i] = 0.0;
    } 
}

