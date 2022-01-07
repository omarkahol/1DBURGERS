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
                
                if (split_lines[1]=="EXPLICIT") {
                    data.method = &PDE::SOLVER::explicit_solver;
                } else if (split_lines[1]=="RK_2") {
                    data.method = &PDE::SOLVER::rk_2;
                } else if (split_lines[1]=="RK_3") {
                    data.method = &PDE::SOLVER::rk_3;
                } else {
                    std::cout << "UNKNOWN METHOD. ABORTING EXECUTION...";
                    throw 1;
                }

            } else if (split_lines[0] == "RIEMANN_SOLVER") {
               
                if (split_lines[1]=="GODUNOV") {
                    data.riemann_solver = &PDE::SOLVER::godunov;
                } else if (split_lines[1]=="ROE_FIX") {
                    data.riemann_solver = &PDE::SOLVER::roe_fix;
                } else {
                    std::cout << "UNKNOWN RIEMANN SOLVER. ABORTING EXECUTION...";
                    throw 1;
                }

            } else if (split_lines[0] == "LIMITER") {
               
                if (split_lines[1]=="NONE") {
                    data.limiter =  [](double,double,double) {return 1.0;};
                } else if (split_lines[1]=="VAN_ALBADA") {
                    data.limiter = &PDE::SOLVER::vanAlbada;
                } else if (split_lines[1]=="VAN_LEER") {
                    data.limiter = &PDE::SOLVER::vanLeer;
                } else if (split_lines[1]=="MINMOD") {
                    data.limiter = &PDE::SOLVER::minmod;
                } else if (split_lines[1]=="SUPERBEE") {
                    data.limiter = &PDE::SOLVER::superbee;
                } else {
                    std::cout << "UNKNOWN LIMITER CHOICE. ABORTING EXECUTION...";
                    throw 1;
                }

            } else if (split_lines[0] == "NX") {
                data.nx = std::atoi(split_lines[1].c_str())-1;
            } else if (split_lines[0] == "MESH") {
                raw_msh = split_lines[1];
            } else if (split_lines[0] == "SECOND_ORDER_CORRECTION_TYPE") {
                if (split_lines[1]=="MUSCL_LINEAR") {
                    data.Reconstruction = &PDE::SOLVER::MUSCL_LINEAR;
                }else  if (split_lines[1] == "MUSCL_PARABOLIC"){
                    data.Reconstruction = &PDE::SOLVER::MUSCL_PARABOLIC;
                }else  if (split_lines[1] == "LAX_WENDROFF"){
                    data.Reconstruction = &PDE::SOLVER::LAX_WENDROFF;
                }else  if (split_lines[1] == "KT"){
                    data.Reconstruction = &PDE::SOLVER::KT;
                }else{
                    std::cout << "UNKNOWN RECONSTRUCTION METHOD, ABORTING EXECUTION...";
                    throw 1;
                }
                
            } else if(split_lines[0] == "SECOND_ORDER_CORRECTION"){
                data.SEC_ORD_CORR = (split_lines[1] == "TRUE")?true:false;
            }else if (split_lines[0] == "FILENAME") {
                data.solution_filename = split_lines[1];
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
