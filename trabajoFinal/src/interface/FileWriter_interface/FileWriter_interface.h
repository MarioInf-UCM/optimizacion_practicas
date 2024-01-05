#ifndef FILEWRITER_INTERFACE_H_
#define FILEWRITER_INTERFACE_H_

#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <map>

using namespace std;

class FileWriter_interface{

    private:
        string fileURL;
        static map<string, mutex> mutexes;

    public:
        FileWriter_interface();
        FileWriter_interface(string fileURL);
        ~FileWriter_interface();

        //**********************************
        // DEFINICIÓN DE MÉTODOS FUNCIONALES
        //**********************************
        bool write(string data, bool verbose = false);
        bool writeln(string data, bool verbose = false);
        

        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************
        string getFileURL() const;
        void setFileURL(string data);

};


#endif