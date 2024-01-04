#ifndef FILEWRITER_INTERFACE_H_
#define FILEWRITER_INTERFACE_H_

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class FileWriter_interface{

    private:
        string fileURL;
        ofstream fileStream;

    public:
        FileWriter_interface();
        FileWriter_interface(string fileURL);
        ~FileWriter_interface();

        //**********************************
        // DEFINICIÓN DE MÉTODOS FUNCIONALES
        //**********************************
        bool openFile();
        bool write(string data, bool verbose = false);
        bool writeln(string data, bool verbose = false);
        bool closeFile();
        

        //**********************************************
        //* MÉTODOS DE TRATAMIENTO DE VARIABLES PRIVADAS
        //**********************************************
        string getFileURL() const;
        void setFileURL(string data);

};


#endif