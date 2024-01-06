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

        bool execHeuristic(WorldConfiguration worldConfiguration, RankConfiguration rankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose=false);

};



#endif