#include <iostream>
#include <fstream>
#include <string_utils.hh>
#include <array_utils.hh>

int main(char **argv, int argc) {
    int i;
    bool number_lines = false, show_ends = false;
    for(i = 0; i < argc; i++) {
        if(argv[argc][0] == '-') {
            char *t = "";
            if(argv[argc][1] == '-')
                for(int j = 2; j < sizeof(argv[argc]); j++)
                    t[j - 2] = argv[argc][j];
            else for(int j = 1; j < sizeof(argv[argc]); j++)
                t[j - 1] = argv[argc][j];
            if(t == "number" || t == "n" || t == "number_lines" || t == "number-lines") {
                number_lines = true;
            } else if(t == "ends" || t == "e" || t == "show_ends" || t == "show-ends") {
                show_ends = true;
            }
        } else break;
    }
    if(i == argc) {
        char *t;
        while(true) {
            std::cin >> t;
            if(t != "exit" && t != ".exit" && t != "^C" && t != "^D") {
                if(number_lines) for(int j = 0; j < sizeof(t); j++) {
                    // TODO Add line numerics
                }
                if(show_ends) str_replace(str_replace(t, "\r\n", "$\r\n"), "\n", "$\n");
                std::cout << t << std::endl;
            }
            else break;
        }
    } else {
        std::ofstream out;
        int j;
        for(j = i; j < argc; j++) {
            if(argv[j][0] == '>') {
                char* t = substr(argv[j], 1);
                out = std::ofstream(strcat(t, join(" ", argv, j + 1)));
                if(j == i) {
                    char *t;
                    while(true) {
                        std::cin >> t;
                        if(t != "exit" && t != ".exit" && t != "^C" && t != "^D") {
                            if(number_lines) for(int j = 0; j < sizeof(t); j++) {
                                // TODO Add line numerics
                            }
                            if(show_ends) str_replace(str_replace(t, "\r\n", "$\r\n"), "\n", "$\n");
                            out << t << "\n";
                        }
                        else break;
                    }
                }
                break;
            }
        }
        if(&out == nullptr) {
            char *x = join(" ", argv, i);
            std::ifstream ifs(x);
            char *t;
            while((ifs >> t) && t != nullptr) {
                std::cout << t;
            }
        }
        else {
            char *x = join(" ", subarr(argv, i, j));
            std::ifstream ifs(x);
            char* t;
            while((ifs >> t) && t != nullptr)
                out << t;
        }
    }
    return 0;
}
