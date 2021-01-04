#include "XCSP3CoreParser.h"
#include "XCSP3PrintCallbacks.h"
#include "XCSP3SummaryCallbacks.h"

using namespace XCSP3Core;

int main(int argc, char** argv) {
    XCSP3PrintCallbacks printcb;
    XCSP3SummaryCallbacks sumcb;
    XCSP3CoreCallbacksBase* cb = nullptr;

    bool ok = true;

    if (argc != 3) ok = false;
    if(std::strcmp(argv[1], "summary") == 0) {
        cb = &sumcb;
        std::cout << "// Print summary\n";
    } else if(std::strcmp(argv[1], "print") == 0) {
        cb = &printcb;
        std::cout << "// Print instance\n";
    } else {
        ok = false;
    }
    if(!ok) throw std::runtime_error("usage: ./sample [print/summary] xcsp3instance.xml");

    try {
        XCSP3CoreParser parser(cb);
        std::cout << "// Instance : " << argv[2] << '\n';
        parser.parse(argv[2]); // fileName is a string
    } catch (std::exception& e) {
        std::cout.flush();
        std::cerr << "\n\tUnexpected exception :\n";
        std::cerr << "\t" << e.what() << std::endl;
        exit(1);
    }

    return 0;
}
