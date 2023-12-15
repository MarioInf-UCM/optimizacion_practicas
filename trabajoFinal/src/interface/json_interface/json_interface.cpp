#include <iostream>
#include <fstream>

#include "json_interface.h"

void Json_interface::processJSONFile() {

    std::ifstream jsonFileStream(jsonFileURL);
    if (!jsonFileStream.is_open()) {
        std::cerr << "Error al abrir el archivo JSON.\n" << std::endl;;
        return;
    }

    // Parsear el contenido JSON
    Json::Value root;
    Json::CharReaderBuilder reader;
    Json::parseFromStream(reader, jsonFileStream, &root, nullptr);

    // Acceder a los datos específicos
    std::string ipAddress = root["pc"]["ip"].asString();
    std::string worldId = root["pc"]["world"]["id"].asString();
    int worldDimensions = root["pc"]["world"]["dimensions"].asInt();
    std::string worldFitness = root["pc"]["world"]["fitness"].asString();

    std::cout << "IP Address: " << ipAddress << "\n";
    std::cout << "World ID: " << worldId << "\n";
    std::cout << "World Dimensions: " << worldDimensions << "\n";
    std::cout << "World Fitness: " << worldFitness << "\n";

    // Acceder a la lista de rangos
    const Json::Value& rankList = root["pc"]["rank"];
    for (const auto& rank : rankList) {
        int rankId = rank["id"][0].asInt();
        std::string outFileURL = rank["outFIleURL"].asString();
        std::string heuristicName = rank["heuristic"]["name"].asString();
        int heuristicIterations = rank["heuristic"]["iterations"].asInt();
        int heuristicPoblation = rank["heuristic"]["poblation"].asInt();

        std::cout << "\nRank ID: " << rankId << "\n";
        std::cout << "Out File URL: " << outFileURL << "\n";
        std::cout << "Heuristic Name: " << heuristicName << "\n";
        std::cout << "Heuristic Iterations: " << heuristicIterations << "\n";
        std::cout << "Heuristic Poblation: " << heuristicPoblation << "\n";

        // Acceder a la lista de valores en la heurística
        const Json::Value& heuristicValues = rank["heuristic"]["values"];
        std::cout << "Heuristic Values: ";
        for (const auto& value : heuristicValues) {
            std::cout << value.asDouble() << " ";
        }
        std::cout << "\n";
    }



}
