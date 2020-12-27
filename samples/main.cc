#include "XCSP3CoreParser.h"
#include "XCSP3PrintCallbacks.h"

using namespace XCSP3Core;

int main(int argc, char** argv) {
    XCSP3PrintCallbacks cb; // my interface between the parser and the solver

    if (argc != 2)
        throw std::runtime_error("usage: ./test xcsp3instance.xml");
    try {
        XCSP3CoreParser parser(&cb);
        parser.parse(argv[1]); // fileName is a string
    } catch (std::exception& e) {
        std::cout.flush();
        std::cerr << "\n\tUnexpected exception :\n";
        std::cerr << "\t" << e.what() << std::endl;
        exit(1);
    }

    return 0;
}
