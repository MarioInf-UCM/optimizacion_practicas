#include "Heuristic_ParticleSwarmOptimization.h"


//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
Heuristic_ParticleSwarmOptimization::Heuristic_ParticleSwarmOptimization():
    Heuristic("")
{}
Heuristic_ParticleSwarmOptimization::Heuristic_ParticleSwarmOptimization(string ID):
    Heuristic(ID)
{}

Heuristic_ParticleSwarmOptimization::~Heuristic_ParticleSwarmOptimization(){}


//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
bool Heuristic_ParticleSwarmOptimization::execHeuristic(){
    return true;
}

