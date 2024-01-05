#include <iostream>
#include <fstream>
#include <string>

#include "FileWriter_interface.h"

using namespace std;


//***************************************************************
// DEFINICIÓN DE CONSTRUCORES, DESTRUCTORES Y VARIABLES ESTÁTICAS
//***************************************************************
map<string, mutex> FileWriter_interface::mutexes;

FileWriter_interface::FileWriter_interface():
    fileURL("./defaultName_")
{}
FileWriter_interface::FileWriter_interface(string fileURL):
    fileURL(fileURL)
{}

FileWriter_interface::~FileWriter_interface(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
bool FileWriter_interface::write(string data, bool verbose){
    std::lock_guard<std::mutex> lock(mutexes[fileURL]);
    std::ofstream archivo(fileURL, ios::app);

    if (archivo.is_open()) {

        archivo << data << ends;
        if(verbose){
            cout << data << ends;
        }
        archivo.close();

    } else {
        cerr << "El archivo de escritura no se abrió correctamente." << endl;
        return false;
    }

    return true;
}

bool FileWriter_interface::writeln(string data, bool verbose){
    std::lock_guard<std::mutex> lock(mutexes[fileURL]);
    std::ofstream archivo(fileURL, ios::app);

    if (archivo.is_open()) {

        archivo << data << endl;
        if(verbose){
            cout << data << endl;
        }
        archivo.close();

    } else {
        cerr << "El archivo de escritura no se abrió correctamente." << endl;
        return false;
    }
    return true;
}





//**********************************************
//* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
//**********************************************
string FileWriter_interface::getFileURL() const{ return fileURL; }
void FileWriter_interface::setFileURL(string data){ 
    fileURL = data; 
}
