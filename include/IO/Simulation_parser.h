#if !defined(LOGO_H)
#define LOGO_H

#include <string>
#include <iostream>
#include <vector>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <map>



namespace PDE::IO {
    class Simulation_parser {
        private:
            std::fstream file;
            std::vector<std::string> STR ;
        public:
            Simulation_parser(const char *filename);
            ~Simulation_parser();
            void Simulation_parse();
            void Displayer();
    };
}

#endif //LOGO_H
