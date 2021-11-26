#include "parser.h"

PDE::IO::parser::parser(const char *filename) {
    file.open(filename,std::ios::in);
    if (! file.is_open()) {
        throw "file not found exception";
    } else {
        //placeholder
    }
}

PDE::IO::parser::~parser() {
    this -> file.close();
}

void PDE::IO::parser::parse() {
    std::string raw_msh;

    while(file) {
        std::string line;
        std::getline(file,line);
        boost::algorithm::ireplace_all(line," ","");

        if (line.length() < 1 || line[0]=='%') {
            continue;
        } else {
            std::vector<std::string> split_lines;
            boost::algorithm::split(split_lines,line,boost::is_any_of("="));
            
            if (split_lines[0] == "TFINAL") {
                data.t_final = std::atof(split_lines[1].c_str());
            } else if (split_lines[0] == "CFL") {
                data.CFL = std::atof(split_lines[1].c_str());
            } else if (split_lines[0] == "METHOD") {
                data.method = split_lines[1];
            } else if (split_lines[0] == "FLUX") {
                data.flux = split_lines[1];
            } else if (split_lines[0] == "NX") {
                data.nx = std::atoi(split_lines[1].c_str())-1;
            } else if (split_lines[0] == "MESH") {
                raw_msh = split_lines[1];
            } else if (split_lines[0] == "LW_CORRECTION") {
                data.lw_correction = split_lines[1];
            } else if (split_lines[0] == "SLOPE_LIMITER") {
                data.slope_limiter = split_lines[1];
            } else if (split_lines[0] == "FILENAME") {
                data.Solution_filename = split_lines[1];
            }
            
        }
    }

    std::vector<std::string> split_raw_mesh;
    boost::algorithm::split(split_raw_mesh,raw_msh,boost::is_any_of(";"));

    data.mesh = std::vector<double>(data.nx);
    data.u0 = std::vector<double>(data.nx);

    for (int i=0; i<data.nx; i++) {
        std::string point = split_raw_mesh[i];
        boost::algorithm::ireplace_all(point,"(","");
        boost::algorithm::ireplace_all(point,")","");

        std::vector<std::string> point_data;
        boost::algorithm::split(point_data,point,boost::is_any_of(","));
        data.mesh[i] = std::atof(point_data[0].c_str());
        data.u0[i] = std::atof(point_data[1].c_str());
    }
}

PDE::IO::problem_data &PDE::IO::parser::get() {
    return data;
}
