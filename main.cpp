#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <charconv>
#include <fstream>
#include <string_view>

int ParseToInt(const std::string& s) {
    int result;
    std::string_view view = s;
    auto [_, err] = std::from_chars(view.data(), view.data() + view.size(), result);

    if (err == std::errc::invalid_argument) {
        std::cerr << s << " is not a number" << std::endl;
        std::exit(EXIT_FAILURE);
    } else if (err == std::errc::result_out_of_range) {
        std::cerr << "Too big number" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return result;
}

struct Options {
    int lines = 0;
    bool is_tail = false;
    std::string delimiter = "\n";
    bool is_full = true;
    bool is_end = false;
    std::string name_file;
};

int main(int argc, char** argv) {
    std::vector<std::string> args = {argv, argv + argc};

    Options opt;

    for (int i = 1; i < args.size(); ++i) { // -l 5 --lines=5 /
        if (!opt.is_end) {
            if (args[i] == "-l" || args[i].substr(0, 8) == "--lines=") {
                if (args[i] == "-l") { // следующий элемент
                    if (i + 1 < args.size()) {
                        int result = ParseToInt(args[i + 1]);
                        opt.is_full = false;
                        opt.lines = result;
                        ++i;
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
                        opt.delimiter = args[i + 1];
                        ++i;
                    } else {
                        std::cerr << "Not given character for -d argument" << std::endl;
                        return 0;
                    }
                } else {
                    if (args[i].size() >= 13) {
                        if (args[i].substr(12) == "\\\\") {
                            opt.delimiter = "\\";
                        } else if (args[i].substr(12) == "\\n") {
                            opt.delimiter = "\n";
                        } else if (args[i].substr(12) == "\\t") {
                            opt.delimiter = "\t";
                        } else if (args[i].substr(12) == "\\\'") {
                            opt.delimiter = "\'";
                        } else if (args[i].substr(12) == "\\\"") {
                            opt.delimiter = "\"";
                        } else {
                            opt.delimiter = args[i].substr(12, 1);
                        }
                    } else {
                        std::cerr << "Not given character for delimiter" << std::endl;
                        return 0;
                    }
                }
            } else {
                opt.is_end = true; // для того чтобы после файла не вводились аргументы
                opt.name_file = args[i];
            }
        } else {
        std::cerr << "You cannot use arguments after specifying the file" << std::endl;
        return 0;
        }
    } 

    std::ifstream file(opt.name_file);
    if (!file.is_open()) {
        std::cerr << "Failed to open file" << std::endl;
        return 1;
    }

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line)) {
        line += opt.delimiter;
        lines.push_back(line);
    }

    file.close();

    if (opt.is_full) {
        if (opt.is_tail) {
            // full tail
        } else {
            for (const auto& l : lines) {
                std::cout << l;
            }
        }
    } else if (opt.lines > 0) {
        if (opt.is_tail) {
            // tail c lines
        } else {
            for (int i = 0; i < opt.lines; ++i) {
                std::cout << lines[i];
            }
        }
    }

    return 0;
}