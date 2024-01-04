#include <iostream>
#include <fstream>
#include <string>

#include "FileWriter_interface.h"

using namespace std;

//******************************************
// DEFINICIÓN DE CONSTRUCORES Y DESTRUCTORES
//******************************************
FileWriter_interface::FileWriter_interface():
    fileURL("")
{}
FileWriter_interface::FileWriter_interface(string fileURL):
    fileURL(fileURL)
{}

FileWriter_interface::~FileWriter_interface(){}



//**********************************
// DEFINICIÓN DE MÉTODOS FUNCIONALES
//**********************************
bool FileWriter_interface::openFile(){
    if (fileStream.is_open()){
        return true;
    }
    return false;
}


bool FileWriter_interface::write(string data, bool verbose){
    fileStream << data << ends;
    if(verbose){
        cout << data << ends;
    }
    return true;
}

bool FileWriter_interface::writeln(string data, bool verbose){
    fileStream << data << endl;
    if(verbose){
        cout << data << endl;
    }
    return true;
}


bool FileWriter_interface::closeFile(){
    fileStream.close();
    return true;
}




//**********************************************
//* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
//**********************************************
string FileWriter_interface::getFileURL() const{ return fileURL; }
void FileWriter_interface::setFileURL(string data){ 
    fileURL = data; 
    fileStream = ofstream(getFileURL());
}
