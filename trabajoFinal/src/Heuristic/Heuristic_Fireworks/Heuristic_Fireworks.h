#ifndef HEURISTIC_FIREWORKS_H_
#define HEURISTIC_FIREWORKS_H_

#include <iostream>
#include <string>

#include "../Heuristic.h"

using namespace std;


class Heuristic_Fireworks:public Heuristic{

    public:
        Heuristic_Fireworks();
        ~Heuristic_Fireworks();

        bool execHeuristic(WorldConfiguration worldConfiguration, RankConfiguration RankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose=false);

};



#endif