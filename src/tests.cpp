//
// Created by vlad on 30.11.20.
//

#include <iostream>
#include <assert.h>
#include "tests.h"

#include "database_manipulation.h"
#include "proc_analysis.h"
#include "utils.h"

std::string SAMPLE_TABLE = "sample";
std::string SAMPLE_TABLE_FIELDS = "(sample_value TEXT)";
std::string arguments = " ('sample_value') VALUES ('sample')";

void open_database_test() {
    auto db = open_database();
    assert(database_exists("local_database.db"));
    assert(db != nullptr);
    close_database(db);

    std::cout << "Open database test: passed" << "\n";
}

void create_table_test() {
    auto db = open_database();
    create_table(db, SAMPLE_TABLE, SAMPLE_TABLE_FIELDS);

    auto entries = select_from_database(db, 0, "SELECT * FROM " + SAMPLE_TABLE);
    assert(entries.size() == 0);

    close_database(db);
    std::cout << "Create table in database test: passed" << "\n";
}

void select_from_database_test() {
    auto db = open_database();

    insert_in_table(db, SAMPLE_TABLE, arguments);

    auto entries = select_from_database(db, 0, "SELECT * FROM " + SAMPLE_TABLE);
    close_database(db);

    assert(entries.size() == 1);
    assert(entries[0] == "sample");
    std::cout << "Select from database test: passed" << "\n";
}

void insert_in_table_test() {
    auto db = open_database();
    delete_from_table(db, SAMPLE_TABLE);

    for (int i = 0; i < 10; i++) {
        insert_in_table(db, SAMPLE_TABLE, arguments);
    }

    auto entries = select_from_database(db, 0, "SELECT * FROM " + SAMPLE_TABLE);
    assert(entries.size() == 10);
    close_database(db);

    std::cout << "Insert in database table test: passed" << "\n";
}

void delete_from_table_test() {
    auto db = open_database();

    for (int i = 0; i < 10; i++) {
        insert_in_table(db, SAMPLE_TABLE, arguments);
    }

    auto entries = select_from_database(db, 0, "SELECT * FROM " + SAMPLE_TABLE);
    assert(entries.size() >= 10);

    delete_from_table(db, SAMPLE_TABLE);
    auto entries2 = select_from_database(db, 0, "SELECT * FROM " + SAMPLE_TABLE);
    assert(entries2.size() == 0);

    close_database(db);
    std::cout << "Delete from database table test: passed" << "\n";
}

void get_running_processes_amount_test() {
    assert(get_running_processes_amount() >= 0);
    std::cout << "Get running processes amount test passed" << "\n";
}

void get_blocked_processes_amount_test() {
    assert(get_blocked_processes_amount() >= 0);
    std::cout << "Get running processes amount test passed" << "\n";
}

void get_time_since_boot_test() {
    assert(get_time_since_boot() > 0);
    std::cout << "Get time since boot test passed" << "\n";
}

void get_interrupts_amount_test() {
    assert(get_interrupts_amount() > 0);
    std::cout << "Get interrupts amount test passed" << "\n";
}

void get_context_switches_test() {
    assert(get_context_switches() > 0);
    std::cout << "Get context switches test passed" << "\n";
}

void get_cpu_n_stat_test() {
    assert(get_cpu_n_stat().size() > 0);
    assert(get_cpu_n_stat("0").size() > 0);
    std::cout << "Get CPU stat by n test passed" << "\n";
}

void get_cpu_stat_test() {
    assert(get_cpu_stat(0).size() > 0);
    assert(get_cpu_stat(1).size() > 0);
    std::cout << "Get CPU stat test passed" << "\n";
}

void get_total_allocated_descriptors_test() {
    assert(get_total_allocated_descriptors() > 0);
    std::cout << "Get total allocated descriptors test passed" << "\n";
}

void get_total_free_descriptors_test() {
    assert(get_total_free_descriptors() >= 0);
    std::cout << "Get total free descriptors test passed" << "\n";
}

void get_open_descriptors_limit_test() {
    assert(get_open_descriptors_limit() > 0);
    std::cout << "Get open descriptors limit test passed" << "\n";
}

void get_cpu_amount_test() {
    assert(get_cpu_amount() > 0);
    std::cout << "Get CPU amount test passed" << "\n";
}

void get_cpu_vendor_id_test() {
    assert(get_cpu_vendor_id() != "");
    std::cout << "Get CPU vendor test passed" << "\n";
}

void get_cpu_model_name_test() {
    assert(get_cpu_model_name() != "");
    std::cout << "Get CPU model name test passed" << "\n";
}

void test_cpu_specs() {
    assert(get_last_level_cache_size() != "");
    std::cout << "Get CPU last level cache test passed" << "\n";
    assert(get_cpu_cores_amount() != "");
    std::cout << "Get CPU cores amount test passed" << "\n";
    assert(get_cpu_bogomips() != "");
    std::cout << "Get CPU bogomips test passed" << "\n";
    assert(get_cpu_bugs() != "");
    std::cout << "Get CPU bugs passed";
    assert(get_cpu_utilization() != "");
    std::cout << "Get CPU utilization test passed" << "\n";
    assert(get_cpu_usage().size() > 0);
    std::cout << "Get CPU usage test passed" << "\n";
}

void test_memory_specs() {
    assert(get_availible_ram() != "");
    std::cout << "Get availible RAM test passed" << "\n";
    assert(get_cached_ram() != "");
    std::cout << "Get cached RAM test passed" << "\n";
    assert(get_active_ram() != "");
    std::cout << "Get active RAM test passed" << "\n";
    assert(get_inactive_ram() != "");
    std::cout << "Get inactive RAM test passed" << "\n";
    assert(get_dirty_ram() != "");
    std::cout << "Get dirty RAM test passed" << "\n";
    assert(get_total_virtual_adress() != "");
    std::cout << "Get total virtual address test passed" << "\n";
    assert(get_used_virtual_adress() != "");
    std::cout << "Get used virtual address test passed" << "\n";
    assert(get_version() != "");
    std::cout << "Get version test passed" << "\n";
}