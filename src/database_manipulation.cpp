//
// Created by vlad on 03.11.20.
//

#include "database_manipulation.h"
#include "proc_analysis.h"
#include <sys/stat.h>
#include <iostream>
#include <iterator>
#include <sstream>
#include <utils.h>

std::string DATABASE_NAME = "local_database.db";

std::string PROCESSES_TABLE = "processes";
std::string CPU_TABLE = "cpu";
std::string FILES_TABLE = "files";
std::string MEMORY_TABLE = "memory";

std::string PROCESSES_TABLE_FIELDS = "(running_processes TEXT, blocked_processes TEXT, open_processes TEXT, forks_since_boot TEXT, time_since_boot TEXT)";
std::string CPU_TABLE_FIELDS = "(cpu_utilization_label TEXT, cpu_usage_label TEXT)";
std::string FILES_TABLE_FIELDS = "(allocated_descriptors TEXT, free_descriptors TEXT)";
std::string MEMORY_TABLE_FIELDS = "(cached_ram TEXT, active_ram TEXT, inactive_ram TEXT, dirty_ram TEXT, used_virtual_ram TEXT)";

int execute_sql(sqlite3* connection, std::string query, std::string error_message) {
    char* err = NULL;
    int ret_code = sqlite3_exec(connection, query.c_str(), NULL, 0, &err);

    if (ret_code) {
        std::cout << error_message << " return code: " << ret_code << std::endl;
    }

    return ret_code;
}

sqlite3* open_database() {
    sqlite3 *db;
    int rc;
    rc = sqlite3_open(DATABASE_NAME.c_str(), &db);

    if (rc) {
        std::cout << "Problems with opening " << std::endl;
        return nullptr;
    } else {
        return db;
    }
}

void close_database(sqlite3 *connection) {
    sqlite3_close(connection);
}

int create_table(sqlite3 *connection, std::string table_name, std::string fields) {
    std::string query = "CREATE TABLE " + table_name + " " + fields + ";";
    std::string error_message = "Problems with creating table!";

    return execute_sql(connection, query, error_message);
}

std::vector<std::string> select_from_database(sqlite3* connection, int column_index, std::string sql) {
    sqlite3_stmt* stmt;
    auto result = std::vector<std::string>();

    // compile sql statement to binary
    if(sqlite3_prepare_v2(connection, sql.c_str(), -1, &stmt, NULL) != SQLITE_OK) {
        printf("ERROR: while compiling sql: %s\n", sqlite3_errmsg(connection));
        sqlite3_close(connection);
        sqlite3_finalize(stmt);
        return result;
    }

    // execute sql statement, and while there are rows returned, print ID
    int ret_code = 0;
    while((ret_code = sqlite3_step(stmt)) == SQLITE_ROW) {
        std::string entry = reinterpret_cast<const char*>(sqlite3_column_text(stmt, column_index));
        result.push_back(entry);
    }

    if(ret_code != SQLITE_DONE) {
        //this error handling could be done better, but it works
        printf("ERROR: while performing sql: %s\n", sqlite3_errmsg(connection));
        printf("ret_code = %d\n", ret_code);
    }

    //release resources
    sqlite3_finalize(stmt);
    return result;
}

int delete_from_table(sqlite3* connection, std::string table_name) {
    std::string query = "DELETE FROM " + table_name + ";";
    std::string error_message = "Problems with deleting from table!";

    return execute_sql(connection, query, error_message);
}

int drop_table(sqlite3* connection, std::string table_name) {
    std::string query = "DROP TABLE " + table_name + ";";
    std::string error_message = "Problems with dropping table!";

    return execute_sql(connection, query, error_message);
}

int insert_in_table(sqlite3 *connection, std::string table_name, std::string arguments) {
    std::string query = "INSERT INTO " + table_name + arguments + ";";
    std::string error_message = "Problems with inserting in table!";

    return execute_sql(connection, query, error_message);
}

inline bool database_exists (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

void initialize_database_and_tables() {
    if (!database_exists(DATABASE_NAME)) {
        auto db = open_database();

        create_table(db, PROCESSES_TABLE, PROCESSES_TABLE_FIELDS);
        create_table(db, CPU_TABLE, CPU_TABLE_FIELDS);
        create_table(db, FILES_TABLE, FILES_TABLE_FIELDS);
        create_table(db, MEMORY_TABLE, MEMORY_TABLE_FIELDS);

        close_database(db);
    }
}

void clear_all_tables() {
    auto db = open_database();

    delete_from_table(db, PROCESSES_TABLE);
    delete_from_table(db, CPU_TABLE);
    delete_from_table(db, FILES_TABLE);
    delete_from_table(db, MEMORY_TABLE);

    close_database(db);
}

void update_processes_table() {
    auto running_process = std::to_string(get_running_processes_amount());
    auto blocked_processes = std::to_string(get_blocked_processes_amount());
    auto open_processes = std::to_string(get_total_open_processes_amount());
    auto forks_since_boot = std::to_string(get_forks_since_boot());
    auto time_since_boot = std::to_string(get_time_since_boot());

    std::string arguments = " ('running_processes', 'blocked_processes', 'open_processes', 'forks_since_boot', 'time_since_boot') VALUES ('" + running_process + "','" + blocked_processes + "','" + open_processes + "','" + forks_since_boot + "','" + time_since_boot + "')";

    auto db = open_database();
    insert_in_table(db, PROCESSES_TABLE, arguments);
    close_database(db);
}

void update_cpu_table() {
    auto cpu_utilization = get_cpu_utilization();
    std::string cpu_usage_string = "";

    for (auto x: get_cpu_usage()) {
        cpu_usage_string += x + " ";
    }

    std::string arguments = " ('cpu_utilization_label', 'cpu_usage_label') VALUES ('" + cpu_utilization + "','" + cpu_usage_string + "')";

    auto db = open_database();
    insert_in_table(db, CPU_TABLE, arguments);
    close_database(db);
}

void update_files_table() {
    auto allocated_decriptors_number = std::to_string(get_total_allocated_descriptors());
    auto free_descriptors_number = std::to_string(get_total_free_descriptors());

    std::string arguments = " ('allocated_descriptors', 'free_descriptors') VALUES ('" + allocated_decriptors_number + "','" + free_descriptors_number + "')";

    auto db = open_database();
    insert_in_table(db, FILES_TABLE, arguments);
    close_database(db);
}

void update_memory_table() {
    auto cached_ram = get_cached_ram();
    auto active_ram = get_active_ram();
    auto inactive_ram = get_inactive_ram();
    auto dirty_ram = get_dirty_ram();
    auto used_virtual_address = get_used_virtual_adress();

    std::string arguments = " ('cached_ram', 'active_ram', 'inactive_ram', 'dirty_ram', 'used_virtual_ram') VALUES ('" + cached_ram + "','" + active_ram + + "','" + inactive_ram + "','" + dirty_ram + "','" + used_virtual_address + "')";

    auto db = open_database();
    insert_in_table(db, MEMORY_TABLE, arguments);
    close_database(db);
}