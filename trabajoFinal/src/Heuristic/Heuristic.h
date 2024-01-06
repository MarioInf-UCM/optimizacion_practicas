#ifndef HEURISTIC_H_
#define HEURISTIC_H_

#include <iostream>
#include <string>
#include <mpi.h>
#include "../interface/Json_interface/JsonConfiguration/WorldConfiguration/WorldConfiguration.h"
#include "../interface/Json_interface/JsonConfiguration/RankConfiguration/RankConfiguration.h"
#include "../interface/FileWriter_interface/FileWriter_interface.h"

using namespace std;


class Heuristic{
    private:
        string ID;
        

    public:
        Heuristic();
        Heuristic(string ID);
        ~Heuristic();

        //bool execHeuristic(WorldConfiguration worldConfiguration, RankConfiguration RankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV);


        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************
        string getID();
};
#endif