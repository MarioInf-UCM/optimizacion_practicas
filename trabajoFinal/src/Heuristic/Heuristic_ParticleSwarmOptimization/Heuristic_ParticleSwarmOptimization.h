#ifndef HEURISTIC_PARTICLESWARMOPTIMIZATION_H_
#define HEURISTIC_PARTICLESWARMOPTIMIZATION_H_

#include <iostream>
#include <string>

#include "../Heuristic.h"

using namespace std;


class Heuristic_ParticleSwarmOptimization:public Heuristic{

    public:
        Heuristic_ParticleSwarmOptimization();
        Heuristic_ParticleSwarmOptimization(string ID);
        ~Heuristic_ParticleSwarmOptimization();

        bool execHeuristic();

};



#endif