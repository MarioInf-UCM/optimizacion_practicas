#ifndef HEURISTIC_ARTIFFICIALBEECOLONY_H_
#define HEURISTIC_ARTIFFICIALBEECOLONY_H_

#include <iostream>
#include <string>

#include "../Heuristic.h"

using namespace std;


class Heuristic_ArtificialBeeColony:public Heuristic{

    public:
        Heuristic_ArtificialBeeColony();
        ~Heuristic_ArtificialBeeColony();

        bool execHeuristic();

};



#endif