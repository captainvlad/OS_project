//
// Created by vlad on 01.11.20.
//
#include "proc_analysis.h"
#include "utils.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <filesystem>


int get_running_processes_amount() {
    return proc_stat_manager(std::string("procs_running") );
}

int get_blocked_processes_amount() {
    return proc_stat_manager(std::string("procs_blocked") );
}

int get_total_open_processes_amount() {
    int open_processes = 0;

    std::string path = "/proc";
    for (const auto &entry : std::filesystem::directory_iterator(path)) {
        open_processes += is_process_dir(entry.path());
    }

    return open_processes;
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
    return get_cpu_n_stat( std::to_string(i) );
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

    return std::stol(files_manager()[2], &sz);
}

std::vector<std::string> cpu_info_manager(std::string substring_to_find) {
    std::ifstream input("/proc/cpuinfo");
    auto container = std::vector<std::string> {};

    for( std::string line; getline( input, line ); ) {
        if (contains(&line, &substring_to_find)) {
            split_string(line, container, ' ');
            return container;
        }
    }

    return container;
}

std::string get_cpu_vendor_id() {
    std::string result = "";
    auto substring_collection = cpu_info_manager("vendor_id");

    for (int i = 1; i < substring_collection.size(); i++) {
        result += substring_collection[i] + " ";
    }

    return result;
}

std::string get_cpu_model_name() {
    std::string result = "";
    auto substring_collection = cpu_info_manager("model name");

    for (int i = 2; i < substring_collection.size(); i++) {
        result += substring_collection[i] + " ";
    }

    return result;
}

std::string get_last_level_cache_size() {
    std::string result = "";
    auto substring_collection = cpu_info_manager("cache size");

    for (int i = 2; i < substring_collection.size(); i++) {
        result += substring_collection[i] + " ";
    }

    return result;
}

std::string get_cpu_cores_amount() {
    return cpu_info_manager("cpu cores")[2];
}

std::string get_cpu_bogomips() {
    return cpu_info_manager("bogomips")[1];
}

std::string get_cpu_bugs() {
    std::string result = "";
    auto substring_collection = cpu_info_manager("bugs");

    for (int i = 1; i < substring_collection.size(); i++) {
        result += substring_collection[i] + " ";
    }

    return result;
}

std::string get_cpu_utilization() {
    std::string::size_type sz;
    unsigned long total_time = 0;
    unsigned long idle_time;
    std::string result;
    double utilization;

    for (int i = 2; i < get_cpu_n_stat().size(); i++ ) {
        total_time += std::stol(get_cpu_n_stat()[i], &sz);
    }

    idle_time = std::stol(get_cpu_n_stat()[5], &sz);

    utilization = (1 - idle_time / (double)total_time) * 100;
    utilization = std::round(utilization * 100) / 100;

    result = std::to_string(utilization);
    result.erase ( result.find_last_not_of('0') + 1, std::string::npos );
    result += " %";

    return result;
}

std::vector<std::string> get_cpu_usage() {
    std::string::size_type sz;
    auto regimes_template = std::vector<std::string> {
        "User mode: ",
        "Nice mode: ",
        "System mode: ",
        "Idle mode: ",
        "I/O wait mode: ",
        "Interrupts servicing time: ",
        "Softirqs servicing time: ",
        "Stolen time: ",
        "Guest mode: ",
        "Guest nice mode: "
    };

    unsigned long total_time = 0;
    unsigned long current_time = 0;

    for (int i = 2; i < get_cpu_n_stat().size(); i++ ) {
        total_time += std::stol(get_cpu_n_stat()[i], &sz);
    }

    for (int i = 2; i < get_cpu_n_stat().size(); i++ ) {
        current_time = std::stol(get_cpu_n_stat()[i], &sz);
        current_time = current_time * 10000 / (double)total_time;
        current_time = current_time / (double)100;

        regimes_template[i - 2] += std::to_string(current_time) + " %";
    }

    return regimes_template;
}

std::vector<std::string> memory_manager(std::string substring_to_find) {
    std::ifstream input("/proc/meminfo");
    auto container = std::vector<std::string> {};

    for( std::string line; getline( input, line ); ) {
        if (contains(&line, &substring_to_find)) {
            split_string(line, container, ' ');
            return container;
        }
    }

    return container;
}

std::string get_memory_spec(std::string string_to_find) {
    auto splitted_substrings = memory_manager(string_to_find);
    auto last_index = splitted_substrings.size() - 1;

    std::string result = splitted_substrings[last_index - 1] + " "
            + splitted_substrings[last_index];

    return result;
}

std::string get_total_ram_size() {
    return get_memory_spec("MemTotal");
}

std::string get_availible_ram() {
    return get_memory_spec("MemAvailable");
}

std::string get_cached_ram() {
    return get_memory_spec("Cached");
}

std::string get_active_ram() {
    return get_memory_spec("Active");
}

std::string get_inactive_ram() {
    return get_memory_spec("Inactive");
}

std::string get_dirty_ram() {
    return get_memory_spec("Dirty");
}

std::string get_total_virtual_adress() {
    return get_memory_spec("VmallocTotal");
}

std::string get_used_virtual_adress() {
    return get_memory_spec("VmallocUsed");
}

std::string get_version() {
    auto container = std::vector<std::string> {};
    std::ifstream input("/proc/version");
    std::string result;
    getline(input, result);

    return result;
}