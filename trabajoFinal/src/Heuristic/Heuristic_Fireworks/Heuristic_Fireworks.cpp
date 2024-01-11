#include "Heuristic_Fireworks.h"
#include <cfloat>
#include <cmath>


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
Heuristic_Fireworks::Heuristic_Fireworks():
    Heuristic("Fireworks")
{}

Heuristic_Fireworks::~Heuristic_Fireworks(){}


//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
bool Heuristic_Fireworks::execHeuristic(float (*fitnessFunction)(float), WorldConfiguration worldConfiguration, RankConfiguration rankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ostringstream printStream;
    printStream << "Proceso:" << rank << " - Inicio ejecución heurística" << getID(); file_commonLog.writeln(printStream, flagVerbose);


    setDimensions(rankConfiguration.getDimensions());
    setIterations(rankConfiguration.getIterations());
    setNumFireworks(rankConfiguration.getPoblation());
    setMaxSparks(rankConfiguration.getValue_byIndex(0));
    if(rankConfiguration.getValue_byIndex(1) < rankConfiguration.getValue_byIndex(2)){
        setConstSparkLimitA(rankConfiguration.getValue_byIndex(1));
        setConstSparkLimitB(rankConfiguration.getValue_byIndex(2));
    }else{
        setConstSparkLimitA(rankConfiguration.getValue_byIndex(2));
        setConstSparkLimitB(rankConfiguration.getValue_byIndex(1));
    }
    setMaxAmplitudeExplosion(rankConfiguration.getValue_byIndex(3));


    vector<float> minPosList = vector<float>();
    for(int i=0 ; i<dimensions ; i++){
        minPosList.push_back(  worldConfiguration.getLimitLeft() + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (worldConfiguration.getLimitRight() - worldConfiguration.getLimitLeft()))) );
    }

    //Paso 1: Seleccionamos N localizaciones aleatorias iniciales
    vector<float> locationList = vector<float>();
    for(int i=0 ; i<numFireworks ; i++){
        locationList.push_back(generarNumeroAleatorio(worldConfiguration.getLimitLeft(), worldConfiguration.getLimitRight()));
    }
    



    
    return true;
}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
unsigned int Heuristic_Fireworks::calculateSparkNum(float locationIndex, vector<float> locationList,  float (*fitnessFunction)(float)){
    float Si=0.0, sumatory=0.0, worstFitnessValue=0.0;
    float fitnessResultTemp=0.0;
    int result = 0;

    for(int i=0 ; i<locationList.size() ; i++){
        fitnessResultTemp = fitnessFunction(locationList[i]); 
        sumatory = sumatory + (worstFitnessValue - fitnessResultTemp);
        if(fitnessResultTemp>worstFitnessValue){
            worstFitnessValue = fitnessResultTemp;
        }
    }
    Si = getMaxSparks() * ( worstFitnessValue - (fitnessFunction(locationList[locationIndex]) + FLT_MIN) / (sumatory + FLT_MIN) );
    if(Si < getConstSparkLimitA() * getMaxSparks()){
        result = round(getConstSparkLimitA()*getMaxSparks());
    }else if( Si > getConstSparkLimitB()*getMaxSparks()){
        result = round(getConstSparkLimitB()*getMaxSparks());
    }
    return result;
}


float Heuristic_Fireworks::CalculateExplosionAmplitude(float locationIndex, vector<float> locationList,  float (*fitnessFunction)(float)){
    float Ai=0.0, sumatory=0.0, bestFitnessValue=0.0;
    float fitnessResultTemp=0.0;

    for(int i=0 ; i<locationList.size() ; i++){
        fitnessResultTemp = fitnessFunction(locationList[i]); 
        sumatory = sumatory + (fitnessResultTemp - bestFitnessValue);
        if(fitnessResultTemp<bestFitnessValue){
            bestFitnessValue = fitnessResultTemp;
        }
    }
    Ai = getMaxAmplitudeExplosion() * ( (fitnessFunction(locationList[locationIndex]) - bestFitnessValue + FLT_MIN) / (sumatory + FLT_MIN) );
    return Ai;
}


unsigned int Heuristic_Fireworks::selectAfectedDimensions(){
    return round(getDimensions() * generarNumeroAleatorio(0,1));
}


double Heuristic_Fireworks::generarNumeroAleatorio(double minimo, double maximo) {
    double numeroAleatorio = minimo + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (maximo - minimo)));
    return numeroAleatorio;
}


float Heuristic_Fireworks::calculateSparkPosition(float x, vector<float> locationList, float (*fitnessFunction)(float)){
/*     float X2 = x;
    int dimensionSelected=0;
    vector<int>dimensionSelectedList = vector<int>();

    int affectedDimensions=selectAfectedDimensions();
    vector<int>SelectorList = vector<int>();
    for(int i=0 ; i<dimensions ; i++){
        SelectorList.push_back(i);
    }
    for(int i=0 ; i<affectedDimensions ; i++){
        dimensionSelected = generarNumeroAleatorio(0, SelectorList.size());
        dimensionSelectedList.push_back(dimensionSelected);
        SelectorList.erase(SelectorList.begin() + dimensionSelected);
    }

    float displacement = CalculateExplosionAmplitude(x, locationList, fitnessFunction) * generarNumeroAleatorio(-1, 1);

    for(int i=0 ; i<dimensionSelectedList.size() ; i++){

    }

 */

}



//*******************************************
// MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
//*******************************************
unsigned int Heuristic_Fireworks::getDimensions() const {
    return dimensions;
}

void Heuristic_Fireworks::setDimensions(unsigned int newDimensions) {
    dimensions = newDimensions;
}

unsigned int Heuristic_Fireworks::getIterations() const {
    return iterations;
}

void Heuristic_Fireworks::setIterations(unsigned int newIterations) {
    iterations = newIterations;
}

unsigned int Heuristic_Fireworks::getNumFireworks() const {
    return numFireworks;
}

void Heuristic_Fireworks::setNumFireworks(unsigned int newNumFireworks) {
    numFireworks = newNumFireworks;
}

float Heuristic_Fireworks::getMaxSparks() const {
    return maxSparks;
}

void Heuristic_Fireworks::setMaxSparks(float newMaxSparks) {
    maxSparks = newMaxSparks;
}

float Heuristic_Fireworks::getConstSparkLimitA() const {
    return constSparkLimitA;
}

void Heuristic_Fireworks::setConstSparkLimitA(float newConstSparkLimitA) {
    constSparkLimitA = newConstSparkLimitA;
}

float Heuristic_Fireworks::getConstSparkLimitB() const {
    return constSparkLimitB;
}

void Heuristic_Fireworks::setConstSparkLimitB(float newConstSparkLimitB) {
    constSparkLimitB = newConstSparkLimitB;
}

float Heuristic_Fireworks::getMaxAmplitudeExplosion() const {
    return maxAmplitudeExploxion;
}

void Heuristic_Fireworks::setMaxAmplitudeExplosion(float newMaxAmplitudeExplosion) {
    maxAmplitudeExploxion = newMaxAmplitudeExplosion;
}