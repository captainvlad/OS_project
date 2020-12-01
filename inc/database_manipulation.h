//
// Created by vlad on 03.11.20.
//

#ifndef SOLO_DATABASE_MANIPULATION_H
#define SOLO_DATABASE_MANIPULATION_H

#include <sqlite3.h>
#include <string>
#include <vector>

sqlite3* open_database();
void close_database(sqlite3 *connection);

int create_table(sqlite3 *connection, std::string table_name, std::string fields);
std::vector<std::string> select_from_database(sqlite3* connection, int column_index, std::string sql);

int insert_in_table(sqlite3 *connection, std::string table_name, std::string arguments);
int delete_from_table(sqlite3* connection, std::string table_name);

int drop_table(sqlite3* connection, std::string table_name);
void initialize_database_and_tables();

void clear_all_tables();
void update_processes_table();

void update_cpu_table();
void update_files_table();

void update_memory_table();
inline bool database_exists (const std::string& name);

#endif //SOLO_DATABASE_MANIPULATION_H
