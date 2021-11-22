#include "parser.h"

int main(int argc, char *argv[])
{
	std::cout << "Initializing Parser" << std::endl;
	PDE::IO::parser p("config.1db");
	p.parse();
	std::cout << "File parsed correctly!" << std::endl;
}