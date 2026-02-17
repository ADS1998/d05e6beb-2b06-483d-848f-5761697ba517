#pragma once

#include <iostream>
#include <string>

#define VAR(x) std::cerr << __FILE__ << ", in " << __func__ << "(), line " << __LINE__  << ": " << #x << " = " << x << "\n"

namespace debug {
    inline int log_level = 0;

    inline void set_verbose_mode(int argc, char* argv[]) {
        for (int i = 1; i < argc; ++i) {
            std::string arg = argv[i];
            if (arg == "-v" && i+1 < argc) {
                log_level = std::stoi(argv[++i]);
            }
        }
    }

    template<typename T>
    void log(int level, const T& msg) {
        if (log_level >= level)
            std::cout << msg << std::endl;
    }

    template<typename T>
    void debug_print(const T& msg) {
        log(1, msg);
    }
}