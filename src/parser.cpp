#include "parser.h"

PDE::IO::parser::parser(const char *filename) {
    file.open(filename,std::ios::in);
    if (! file.is_open()) {
        throw "file not found exception";
    } else {
        data["CHECK"] = std::make_pair<double,bool>(0,false);
    }
}

PDE::IO::parser::~parser() {
    this -> file.close();
}

void PDE::IO::parser::parse() {
    while(file) {
        std::string line;
        std::getline(file,line);
        boost::algorithm::ireplace_all(line," ","");

        if (line.length() < 1 || line[0]=='%') {
            continue;
        } else {
            std::vector<std::string> split_lines;
            boost::algorithm::split(split_lines,line,boost::is_any_of("="));
            data[split_lines[0]] = std::make_pair<double, bool>(std::atof(split_lines[1].c_str()),true);
        }
    }
}

bool PDE::IO::parser::check(std::ostream &out) {
    bool parsed = true; 

    for (auto v: data) {
        if ( !v.second.second) {
            parsed = false;
            out << "KEY " << v.first << " NOT FOUND IN CONFIG FILE!" << std::endl;
        }
    }
    return parsed;
}

const std::map<std::string, std::pair<double,bool>> &PDE::IO::parser::get() {
    return data;
}
