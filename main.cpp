//  C:\Users\Toflar\Desktop\Me\dev-cpp\MyFilePrinter\Debug\fprinter.exe
// cmake --build .
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <charconv>
#include <string_view>

int ParseToInt(const std::string& s) {
    int result;
    std::string_view view = s;
    auto [_, err] = std::from_chars(view.data(), view.data() + view.size(), result);

    if (err == std::errc::invalid_argument) {
        std::cerr << s << " is not number" << std::endl;

        std::exit(EXIT_FAILURE);
    } else if (err == std::errc::result_out_of_range) {
        std::cerr << "Too big number" << std::endl;

        std::exit(EXIT_FAILURE);
    }
    return result;
}

struct Options {
    int lines;
    bool is_tail = false;
    char delimiter = '\n';
    bool is_full = true;
};


int main(int argc, char** argv) {
    std::vector<std::string> args = {argv, argv + argc};

    // for (auto i : args) {
    //     std::cout << i << std::endl;
    // }

    Options opt;

    for (int i = 1; i < args.size(); ++i) { // -l 5 --lines=5
        if (args[i] == "-l" || args[i].substr(0, 8) == "--lines=") {
            if (args[i] == "-l") { // следующий элемент

                if (i + 1 < args.size()) {
                    int result = ParseToInt(args[i + 1]);
                    opt.is_full = false;
                    opt.lines = result;
                } else {
                    std::cerr << "Not given number for -l argument" << std::endl;
                    return 0;
                }

            } else {
                int result = ParseToInt(args[i].substr(8));
                opt.is_full = false;
                opt.lines = result;

            }
        } else if (args[i] == "--tail" || args[i] == "-t") {
            opt.is_tail = true;
        } else if (args[i] == "-d" || args[i].substr(0, 12) == "--delimiter=") {
            if (args[i] == "-d") {
                if (i + 1 < args.size()) {
                    opt.delimiter = args[i + 1][0];
                } else {
                    std::cerr << "Not given character for -d argument" << std::endl;
                    return 0;
                }
            } else {
                if (args[i].size() >= 13) {
                    if (args[i].substr(12) == "\\\\") {
                        opt.delimiter = '\\';
                    } else if (args[i].substr(12) == "\\n") {
                        opt.delimiter = '\n';
                    }
                    else if (args[i].substr(12) == "\\t") {
                        opt.delimiter = '\t';
                    }
                    else if (args[i].substr(12) == "\\\'") {
                        opt.delimiter = '\'';
                    }
                    else if (args[i].substr(12) == "\\\"") {
                        opt.delimiter = '\"';
                    } else {
                        opt.delimiter = args[i][12];
                    }
                } else {
                    std::cerr << "Not given character of delimiter" << std::endl;
                    return 0;
                }
            }
        }
    }

    std::cout << std::endl;

    std::cout << opt.lines << std::endl;
    std::cout << opt.is_full << std::endl;
    std::cout << opt.delimiter << std::endl;
    std::cout << opt.is_tail << std::endl;

    // Read полностью выводить, opt.lines выводить, поддерживать делимитер, выводить с хвоста

    return 0;
}

