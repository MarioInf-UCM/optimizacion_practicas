#include "RankConfiguration.h"
#include <string>
#include <sstream>
#include <vector>
#include <string.h>

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
        value << "\t\tRankList[";
        for(int i=0 ; i<getRankList().size() ; i++){
            if(i == (getRankList().size()-1)){
                value << rankList[i] << ends;
            }else{
                value << rankList[i] << ", " << ends;
            }
        }
        value <<"]" << "    OutputFile: " << getOutputFile() << "    HeuristicID: " << getHeuristicID() << "    Iterations: " << getIterations() << "    Poblation: " << getPoblation() << "    valueList[";
        for(int i=0 ; i<getValueList().size() ; i++){
            if(i == (getValueList().size()-1)){
                value << valueList[i] << ends;
            }else{
                value << valueList[i] << ", " << ends;
            }
        }
        value <<"]" <<endl;
    }

    return value.str();
}

// Método para serializar la instancia en un vector de bytes
vector<char> RankConfiguration::serialize() const {
    vector<char> buffer(sizeof(RankConfiguration));
    char* ptr = buffer.data();

    // Copiar los datos de la instancia a la memoria del buffer
    memcpy(ptr, this, sizeof(RankConfiguration));

    // Serializar vectores
    size_t rankListSize = rankList.size();
    size_t valueListSize = valueList.size();

    memcpy(ptr + sizeof(RankConfiguration), rankList.data(), rankListSize * sizeof(unsigned int));
    memcpy(ptr + sizeof(RankConfiguration) + rankListSize * sizeof(unsigned int), valueList.data(), valueListSize * sizeof(float));

    return buffer;
}

// Método para deserializar un vector de bytes en una instancia
RankConfiguration RankConfiguration::deserialize(const vector<char>& buffer) {
    RankConfiguration instance;

    // Copiar los datos desde el buffer a la instancia
    memcpy(&instance, buffer.data(), sizeof(RankConfiguration));

    // Deserializar vectores
    size_t rankListSize = instance.rankList.size();
    size_t valueListSize = instance.valueList.size();

    memcpy(instance.rankList.data(), buffer.data() + sizeof(RankConfiguration), rankListSize * sizeof(unsigned int));
    memcpy(instance.valueList.data(), buffer.data() + sizeof(RankConfiguration) + rankListSize * sizeof(unsigned int), valueListSize * sizeof(float));

    return instance;
}

//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
bool RankConfiguration::getIsDefault() const { return isDefault; }
void RankConfiguration::setIsDefault(bool newIsDefault){ isDefault =newIsDefault; }


vector<unsigned int>& RankConfiguration::getRankList() { return rankList; }
unsigned int RankConfiguration::getRank_byIndex(unsigned int index){ 
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


vector<float>& RankConfiguration::getValueList() { return valueList; }
float RankConfiguration::getValue_byIndex(unsigned int index){
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
