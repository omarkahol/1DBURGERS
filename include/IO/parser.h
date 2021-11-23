#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <map>

#include "problem_data.h"

namespace PDE::IO {
    class parser {
        private: 
            std::fstream file;
            PDE::IO::problem_data data;
        public:
            parser(const char *filename);
            ~parser();
            void parse();
            PDE::IO::problem_data &get();
    };
}
#endif
