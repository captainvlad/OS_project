#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "proc_analysis.h"

int main() {

    std::cout << get_total_open_processes_amount() << "\n";
    return 0;
}
