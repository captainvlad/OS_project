//
// Created by vlad on 30.11.20.
//

#ifndef SOLO_TESTS_H
#define SOLO_TESTS_H

void open_database_test();
void select_from_database_test();

void create_table_test();
void insert_in_table_test();

void delete_from_table_test();
void get_running_processes_amount_test();

void get_blocked_processes_amount_test();
void get_time_since_boot_test();

void get_interrupts_amount_test();
void get_context_switches_test();

void get_cpu_n_stat_test();
void get_cpu_stat_test();

void get_total_allocated_descriptors_test();
void get_total_free_descriptors_test();

void get_open_descriptors_limit_test();
void get_cpu_amount_test();

void get_cpu_vendor_id_test();
void get_cpu_model_name_test();

void test_cpu_specs();
void test_memory_specs();

#endif //SOLO_TESTS_H
