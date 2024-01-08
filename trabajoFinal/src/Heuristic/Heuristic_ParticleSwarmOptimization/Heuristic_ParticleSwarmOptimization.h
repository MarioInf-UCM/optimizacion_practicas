#ifndef HEURISTIC_PARTICLESWARMOPTIMIZATION_H_
#define HEURISTIC_PARTICLESWARMOPTIMIZATION_H_

#include <iostream>
#include <string>

#include "../Heuristic.h"

using namespace std;


class Heuristic_ParticleSwarmOptimization:public Heuristic{

    public:
        Heuristic_ParticleSwarmOptimization();
        ~Heuristic_ParticleSwarmOptimization();

        bool execHeuristic(float (*fitnessFunction)(float), WorldConfiguration worldConfiguration, RankConfiguration rankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose=false);

    private:
        double generarNumeroAleatorio(double minimo, double maximo);
        void checkAndSendMinimun(float posTemp, float oldMin, float newMin, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose=false);
        bool checkAndReciveMinimun(float *data,  FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose);
};



#endif