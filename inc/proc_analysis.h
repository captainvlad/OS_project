//
// Created by vlad on 01.11.20.
//

#ifndef SOLO_PROC_ANALYSIS_H
#define SOLO_PROC_ANALYSIS_H

#include <string>
#include <vector>

int get_running_processes_amount();
int get_blocked_processes_amount();

int get_total_processes_amount();
int get_forks_since_boot();

int proc_stat_manager(std::string substring_to_find);
int get_time_since_boot();

int get_interrupts_amount();
int get_context_switches();

std::vector<std::string> get_cpu_n_stat(std::string n = "");
std::vector<std::string> get_cpu_stat(int i);

int get_cpu_amount();
std::vector<std::string> files_manager();

int get_total_allocated_descriptors();
int get_total_free_descriptors();

long get_open_descriptors_limit();

#endif //SOLO_PROC_ANALYSIS_H