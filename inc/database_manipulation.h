//
// Created by vlad on 03.11.20.
//

#ifndef SOLO_DATABASE_MANIPULATION_H
#define SOLO_DATABASE_MANIPULATION_H

#include <sqlite3.h>
#include <string>

sqlite3* open_database();
void close_database(sqlite3 *connection);

int create_table(sqlite3 *connection, std::string table_name);
int select_from_database(sqlite3 *connection, std::string table_name);

static int callback(void *data, int argc, char **argv, char **azColName);

#endif //SOLO_DATABASE_MANIPULATION_H
