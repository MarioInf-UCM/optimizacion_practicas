#ifndef HEURISTIC_FIREWORKS_H_
#define HEURISTIC_FIREWORKS_H_

#include <iostream>
#include <string>

#include "../Heuristic.h"

using namespace std;


class Heuristic_Fireworks:public Heuristic{

    private:
        unsigned int dimensions;
        unsigned int iterations;
        unsigned int numFireworks;
        float maxSparks;
        float constSparkLimitA;
        float constSparkLimitB;
        float maxAmplitudeExploxion;

    public:
        Heuristic_Fireworks();
        ~Heuristic_Fireworks();

        bool execHeuristic(float (*fitnessFunction)(float), WorldConfiguration worldConfiguration, RankConfiguration rankConfiguration, FileWriter_interface file_commonLog, FileWriter_interface file_resultCSV, bool flagVerbose=false);

    private:
        double generarNumeroAleatorio(double minimo, double maximo);
        unsigned int calculateSparkNum(float locationIndex, vector<float> locationList,  float (*fitnessFunction)(float));
        float CalculateExplosionAmplitude(float locationIndex, vector<float> locationList,  float (*fitnessFunction)(float));
        float calculateSparkPosition(float x, vector<float> locationList, float (*fitnessFunction)(float));

        unsigned int selectAfectedDimensions();
        float calculateSparkPosition(float x);



    public:
        //*******************************************
        // MÉTODOS DE ACCESO A LAS VARIABLES PRIVADAS
        //*******************************************
        float getMaxSparks() const;
        void setMaxSparks(float newMaxSparks);

        float getConstSparkLimitA() const;
        void setConstSparkLimitA(float newConstSparkLimitA);

        float getConstSparkLimitB() const;
        void setConstSparkLimitB(float newConstSparkLimitB);

        float getMaxAmplitudeExplosion() const;
        void setMaxAmplitudeExplosion(float newMaxAmplitudeExplosion);

        unsigned int getDimensions() const;
        void setDimensions(unsigned int newDimensions);

        unsigned int getIterations() const;
        void setIterations(unsigned int newIterations);

        unsigned int getNumFireworks() const;
        void setNumFireworks(unsigned int newNumFireworks);

};
#endif