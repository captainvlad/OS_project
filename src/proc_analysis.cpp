//
// Created by vlad on 01.11.20.
//
#include "proc_analysis.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <vector>

int get_running_processes_amount() {
    return proc_stat_manager(std::string("procs_running") );
}

int get_blocked_processes_amount() {
    return proc_stat_manager(std::string("procs_blocked") );
}

int get_total_processes_amount() {
    return get_blocked_processes_amount() + get_running_processes_amount();
}

int get_forks_since_boot() {
    return proc_stat_manager("processes");
}

int get_time_since_boot() {
    return proc_stat_manager("btime");
}

int get_context_switches() {
    return proc_stat_manager("ctxt");
}

int get_interrupts_amount() {
    return proc_stat_manager("intr");
}

int get_cpu_amount() {
    int result = -1;
    std::string substr_to_find = "cpu";
    std::ifstream input("/proc/stat");

    for( std::string line; getline( input, line ); ) {
        result += contains(&line, &substr_to_find);
    }

    return result;
}

std::vector<std::string> get_cpu_stat(int i) {
    get_cpu_n_stat( std::to_string(i) );
}

std::vector<std::string> get_cpu_n_stat(std::string n) {
    std::ifstream input("/proc/stat");
    std::string substring_to_find = "cpu" + n;
    auto splitted_string_container = std::vector<std::string> {};

    for( std::string line; getline( input, line ); ) {
       if (contains(&line, &substring_to_find)) {
           split_string(line, splitted_string_container, ' ');
           return splitted_string_container;
       }
    }
}

int proc_stat_manager(std::string substring_to_find) {
    std::ifstream input("/proc/stat");
    auto splitted_string_container = std::vector<std::string> {};

    for( std::string line; getline( input, line ); ) {
        if (contains(&line, &substring_to_find)) {
            split_string(line, splitted_string_container, ' ');
            return std::stoi(splitted_string_container[1]);
        }
    }
    return -1;
}

std::vector<std::string> files_manager() {
    std::string line;
    std::ifstream input("/proc/sys/fs/file-nr");
    auto splitted_string_container = std::vector<std::string>{};

    getline( input, line );
    split_string(line, splitted_string_container, '\t');
    return splitted_string_container;
}

int get_total_allocated_descriptors() {
    return stoi(files_manager()[0]);
}

int get_total_free_descriptors() {
    return stoi(files_manager()[1]);
}

long get_open_descriptors_limit() {
    std::string::size_type sz;

    return stol(files_manager()[2], &sz);
}