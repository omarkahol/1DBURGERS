#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <vector>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string.hpp>
#include <fstream>
#include <map>

namespace PDE::IO {
    class parser {
        private: 
            std::fstream file;
            std::map<std::string, std::pair<double,bool>> data;
        public:
            parser(const char *filename);
            ~parser();
            void parse();
            bool check(std::ostream &out);
            const std::map<std::string, std::pair<double,bool>> &get();
    };
}
#endif
