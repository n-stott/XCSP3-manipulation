#include "XCSP3CoreParser.h"
#include "XCSP3SummaryCallbacks.h"
#include <fstream>
#include <sstream>
#include <string>

using namespace XCSP3Core;

int main(int argc, char** argv) {

    if (argc != 2)
        throw std::runtime_error("usage: ./test instances.csv");

    std::cout << "instance,variables,constraints,obj,type\n";

    std::ifstream infile(argv[1]);
    std::string line;
    while (std::getline(infile, line)) {
        try {
            XCSP3SummaryCallbacks cb; // my interface between the parser and the solver
            XCSP3CoreParser parser(&cb);
            std::cout << line << ",";
            parser.parse(line.c_str()); // fileName is a string
        } catch (std::exception& e) {
            std::cout.flush();
            std::cerr << "\n\tUnexpected exception :\n";
            std::cerr << "\t" << e.what() << std::endl;
            exit(1);
        }   
    }

    return 0;
}
