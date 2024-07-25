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
    char delimiter = '\n';
    bool is_full = true;
    bool is_end = false;
    std::string name_file;
};

int main(int argc, char** argv) {
    std::vector<std::string> args = {argv, argv + argc};

    Options opt;

    std::ifstream file;

    for (int i = 1; i < args.size(); ++i) { 
        if (!opt.is_end) {
            if (args[i] == "-l" || args[i].substr(0, 8) == "--lines=") {
                if (args[i] == "-l") { 
                    if (i + 1 < args.size()) {
                        int result = ParseToInt(args[i + 1]);
                        if (result <= 0) {
                            std::cerr << "The number cannot be negative" << std::endl;
                            return 0;
                        }
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
                        if (args[i + 1] == "\\\\") {
                            opt.delimiter = '\\';
                        } else if (args[i + 1] == "\\n") {
                            opt.delimiter = '\n';
                        } else if (args[i + 1] == "\\t") {
                            opt.delimiter = '\t';
                        } else if (args[i + 1] == "\\\'") {
                            opt.delimiter = '\'';
                        } else if (args[i + 1] == "\\\"") {
                            opt.delimiter = '\"';
                        } else if (args[i + 1] == "\\0") {
                            opt.delimiter = '\0';
                        } else {
                            if (args[i + 1].size() == 1) {
                                opt.delimiter = args[i][12];
                            } else {
                                std::cerr << "The argument is not a symbol" << std::endl;
                                return 0;
                            }
                        }
                        ++i;
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
                        } else if (args[i].substr(12) == "\\t") {
                            opt.delimiter = '\t';
                        } else if (args[i].substr(12) == "\\\'") {
                            opt.delimiter = '\'';
                        } else if (args[i].substr(12) == "\\\"") {
                            opt.delimiter = '\"';
                        } else if (args[i].substr(12) == "\\0") {
                            opt.delimiter = '\0';
                        } else {
                            if (args[i].substr(12).size() == 1) {
                                opt.delimiter = args[i][12];
                            } else {
                                std::cerr << "The argument is not a symbol" << std::endl;
                                return 0;
                            }
                        }
                        ++i;
                    } else {
                        std::cerr << "Not given character for delimiter" << std::endl;
                        return 0;
                    }
                }
            } else if (args[i][0] == '-'){
                std::cerr << "The '" << args[i] << "' command does not exist" << std::endl;
                return 0;
            } else {
                opt.is_end = true;
                opt.name_file = args[i];
                file = std::ifstream(opt.name_file);
                if (!file.is_open()) {
                    std::cerr << "Failed to open file" << std::endl;
                    return 1;
                }
            }
        } else {
            std::cerr << "You cannot use arguments after specifying the file" << std::endl;
            return 0;
        }
    } 

    std::vector<std::string> lines;
    std::string line;
    while (std::getline(file, line, opt.delimiter)) {
        lines.push_back(line);
    }

    file.close();

    if (opt.is_full || opt.lines >= static_cast<int>(lines.size())) {
        for (const auto& l : lines) {
            std::cout << l << opt.delimiter;
        }
    } else if (opt.lines > 0) {
        if (opt.is_tail) {
            for (int i = std::max(0, static_cast<int>(lines.size()) - opt.lines); i < lines.size(); ++i) {
                std::cout << lines[i] << opt.delimiter;
            }
        } else {
            for (int i = 0; i < opt.lines; ++i) {
                std::cout << lines[i] << opt.delimiter;
            }
        }
    }

    return 0;
}