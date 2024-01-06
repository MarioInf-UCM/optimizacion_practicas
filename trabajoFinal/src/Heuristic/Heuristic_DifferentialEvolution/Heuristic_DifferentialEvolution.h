#ifndef HEURISTIC_DIFFERENTIALEVOLUTION_H_
#define HEURISTIC_DIFFERENTIALEVOLUTION_H_

#include <iostream>
#include <string>

#include "../Heuristic.h"

using namespace std;


class Heuristic_DifferentialEvolution:public Heuristic{

    public:
        Heuristic_DifferentialEvolution();
        ~Heuristic_DifferentialEvolution();

        bool execHeuristic(WorldConfiguration worldConfiguration, RankConfiguration RankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose=false);

};



#endif