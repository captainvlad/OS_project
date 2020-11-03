//
// Created by vlad on 03.11.20.
//

#include <iostream>
#include "database_manipulation.h"
#include "utils.h"

sqlite3* open_database() {
    sqlite3 *db;
    int rc;

    rc = sqlite3_open("local_database.db", &db);

    if(rc) {
        std::cout << "Problems with opening " << std::endl;
        return nullptr;
    } else {
        return db;
    }
}

void close_database(sqlite3 *connection) {
    sqlite3_close(connection);
}

int create_table(sqlite3 *connection, std::string table_name) {
    char* err = NULL;

    std::string result = "CREATE TABLE " + table_name + " " + "(value TEXT  NOT NULL, timestamp TIMESTAMP NOT NULL);";
    int ret_code = sqlite3_exec(connection, result.c_str(), NULL, 0, &err);

    if (ret_code) {
        std::cout << "Problems with creating table!" << std::endl;
    }

    return ret_code;
}

int select_from_database(sqlite3 *connection, std::string table_name) {
    char* err = NULL;
    char *zErrMsg = 0;
    const char* data = "Callback function called";

    std::string result = "SELECT * FROM " + table_name;
    int ret_code = sqlite3_exec(connection, result.c_str(), callback, (void*)data, &zErrMsg);

    if ( ret_code != SQLITE_OK ) {
        std::cout << "SQL error: " << zErrMsg << std::endl;
        sqlite3_free(zErrMsg);
    }

    return ret_code;
}

static int callback(void *data, int argc, char **argv, char **azColName){
    std::cout << "Selected data: " << (const char*)data << std::endl;
}