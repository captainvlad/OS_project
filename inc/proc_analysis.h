//
// Created by vlad on 01.11.20.
//

#ifndef SOLO_PROC_ANALYSIS_H
#define SOLO_PROC_ANALYSIS_H

#include <string>
#include <vector>

int get_running_processes_amount();
int get_blocked_processes_amount();

int get_total_open_processes_amount();
int get_forks_since_boot();

int proc_stat_manager(std::string substring_to_find);
int get_time_since_boot();

int get_interrupts_amount();
int get_context_switches();

std::vector<std::string> get_cpu_n_stat(std::string n = "");
std::vector<std::string> get_cpu_stat(int i);

std::vector<std::string> files_manager();

int get_total_allocated_descriptors();
int get_total_free_descriptors();

long get_open_descriptors_limit();
std::vector<std::string> cpu_info_manager(std::string substring_to_find);

int get_cpu_amount();
std::string get_cpu_vendor_id();
std::string get_cpu_model_name();

std::string get_last_level_cache_size();
std::string get_cpu_cores_amount();

std::string get_cpu_bogomips();
std::string get_cpu_bugs();

std::string get_cpu_utilization();
std::vector<std::string> get_cpu_usage();

std::vector<std::string> memory_manager(std::string substring_to_find);
std::string get_total_ram_size();

std::string get_memory_spec(std::string string_to_find);
std::string get_availible_ram();

std::string get_cached_ram();
std::string get_active_ram();

std::string get_inactive_ram();
std::string get_dirty_ram();

std::string get_total_virtual_adress();
std::string get_used_virtual_adress();

std::string get_version();

#endif //SOLO_PROC_ANALYSIS_H