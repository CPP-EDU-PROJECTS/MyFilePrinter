//  C:\Users\Toflar\Desktop\Me\dev-cpp\MyFilePrinter\Debug\fprinter.exe
// cmake --build .
#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char** argv) {
    setlocale(LC_ALL, "RU");
    std::string argvv;
    std::string argvv_name;
    std::string arg_lines;
    bool arg_tail;
    std::string arg_delimiter;

    for(int i = 1; i < argc; i++){
        for (int r = 0; r < 30; r++) {
            argvv += argv[i][r]; }
        for (int r = 0; r < 30; r++) {
            argvv_name += argv[i][r];
            if (argvv_name == "--lines" || argvv_name == "-l"){
                
                std::cout << "Сработал --lines" << std::endl;
                std::cout << arg_lines << std::endl;
                argvv_name = "";
                break;
            }
            if (argvv_name == "--tail" || argvv_name == "-t"){

                argvv_name = "";
                std::cout << "Сработал --tail" << std::endl;
                break;
            }
            if (argvv_name == "--delimiter" || argvv_name == "-d"){

                argvv_name = "";
                std::cout << "Сработал --delimiter" << std::endl;
                break;
            }
        }
    }



    return 0;
}

