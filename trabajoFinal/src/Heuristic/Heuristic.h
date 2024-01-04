#ifndef HEURISTIC_H_
#define HEURISTIC_H_

#include <iostream>
#include <string>

using namespace std;


class Heuristic{
    private:
        const string ID;
        

    public:
        Heuristic();
        Heuristic(string ID);
        ~Heuristic();

        bool execHeuristic();

        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************
        string getID() const;
};



#endif