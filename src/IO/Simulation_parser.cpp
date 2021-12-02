
#include "Simulation_parser.h"


PDE::IO::Simulation_parser::Simulation_parser(const  char *filename){
    file.open(filename, std::ios::in);
    if (! file.is_open()){
        throw "file not found exception";
    }
}

PDE::IO::Simulation_parser::~Simulation_parser(){
    this -> file.close();
}

void PDE::IO::Simulation_parser::Simulation_parse(){

    while (file) {
        std::string line;
        std:getline(file, line);
               
        if (line[0] =='%'){
            continue;
        } else {
            STR.push_back(line);
        }
    }
}

void PDE::IO::Simulation_parser::Displayer(){
    
    std::cout << "\n" << std::endl;

    for (int i = 0;  i < STR.size(); i++){
        std::cout << STR[i] << "\n";
    }
    std::cout <<  "\n" << std::endl;
}

