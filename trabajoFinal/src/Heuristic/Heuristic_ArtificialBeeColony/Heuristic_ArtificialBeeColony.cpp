#include <sstream>
#include "Heuristic_ArtificialBeeColony.h"


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
Heuristic_ArtificialBeeColony::Heuristic_ArtificialBeeColony():
    Heuristic("ArtificialBeeColony")
{}
Heuristic_ArtificialBeeColony::~Heuristic_ArtificialBeeColony(){}


//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
bool Heuristic_ArtificialBeeColony::execHeuristic(WorldConfiguration worldConfiguration, RankConfiguration RankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose){
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    ostringstream printStream;
    printStream << "Proceso:" << rank << " - Inicio ejecución heurística" << getID(); file_commonLog.writeln(printStream, flagVerbose);


    
    return true;
}

