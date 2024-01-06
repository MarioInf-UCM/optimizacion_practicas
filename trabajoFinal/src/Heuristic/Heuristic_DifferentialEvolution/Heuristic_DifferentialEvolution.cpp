#include "Heuristic_DifferentialEvolution.h"


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
Heuristic_DifferentialEvolution::Heuristic_DifferentialEvolution():
    Heuristic("DifferentialEvolution")
{}

Heuristic_DifferentialEvolution::~Heuristic_DifferentialEvolution(){}


//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
bool Heuristic_DifferentialEvolution::execHeuristic(WorldConfiguration worldConfiguration, RankConfiguration RankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ostringstream printStream;
    printStream << "Proceso:" << rank << " - Inicio ejecución heurística" << getID(); file_commonLog.writeln(printStream, flagVerbose);


    
    return true;
}

