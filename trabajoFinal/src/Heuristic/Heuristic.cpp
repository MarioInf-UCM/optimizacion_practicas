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
bool Heuristic::execHeuristic(){
    return true;
}



//**********************************************
//* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
//**********************************************
string Heuristic::getID() const{ return ID; }