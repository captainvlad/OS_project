#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "proc_analysis.h"

int main() {

//    std::cout << get_interrupts_amount() << "\n";
//    for (auto val: files_manager()) {
//        std::cout << val << "\n";
//    }

//    bool b = get_cpu_n_stat()[1] == "";
//
//    std::cout << files_manager() << "\n";
    std::cout << get_open_descriptors_limit() << "\n";
    return 0;
}
