#include "Heuristic.h"



//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
Heuristic::Heuristic():
    ID("")
{}
Heuristic::Heuristic(string ID):
    ID(ID)
{}
Heuristic::~Heuristic(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
/* bool Heuristic::execHeuristic(WorldConfiguration worldConfiguration, RankConfiguration rankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV){
    return true;
} */



//**********************************************
//* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
//**********************************************
string Heuristic::getID(){ return ID; }