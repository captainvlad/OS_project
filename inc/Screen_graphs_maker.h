//
// Created by vlad on 31.12.20.
//

#ifndef SOLO_SCREEN_GRAPHS_MAKER_H
#define SOLO_SCREEN_GRAPHS_MAKER_H

#include "Screen.h"

void Screen::createCpuUtilizationGraph() {
    graph_title = "CPU utilization chart";
    table_name = "cpu";
    column_name = "cpu_utilization_label";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createRunningProcessesGraph() {
    graph_title = "Running processes chart";
    table_name = "processes";
    column_name = "running_processes";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createOpenProcessesGraph() {
    graph_title = "Open processes chart";
    table_name = "processes";
    column_name = "open_processes";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createForksSinceBoot() {
    graph_title = "Forks since boot chart";
    table_name = "processes";
    column_name = "forks_since_boot";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createTimeSinceBoot() {
    graph_title = "Time since boot chart";
    table_name = "processes";
    column_name = "time_since_boot";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createAllocatedDescriptors() {
    graph_title = "Allocated descriptors chart";
    table_name = "files";
    column_name = "allocated_descriptors";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createFreeDescriptors() {
    graph_title = "Free descriptors chart";
    table_name = "files";
    column_name = "free_descriptors";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createAvailibleRamSize() {
    graph_title = "Available RAM chart";
    table_name = "memory";
    column_name = "used_virtual_ram";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createCachedRamSize() {
    graph_title = "Cached RAM chart";
    table_name = "memory";
    column_name = "cached_ram";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createActiveRamSize() {
    graph_title = "Active RAM chart";
    table_name = "memory";
    column_name = "active_ram";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createInactiveRamSize() {
    graph_title = "Inactive RAM chart";
    table_name = "memory";
    column_name = "inactive_ram";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createDirtyRamSize() {
    graph_title = "Dirty RAM chart";
    table_name = "memory";
    column_name = "dirty_ram";

    createGraph(graph_title, table_name, column_name);
}

void Screen::createCPUusageGraph() {
    graph_title = "CPU usage chart";
    table_name = "cpu";
    column_name = "cpu_usage_label";

//    auto database_connection = open_database();
//    auto info = select_from_database(database_connection, 0, "SELECT " + column_name + " from " + table_name + ";");
//    close_database(database_connection);
//
//    for (auto x: info) {
//        std::cout << "Item: " << x << "\n";
//
//        for (auto xx: parseCPUusage(x)) {
//            std::cout << xx << "\n";
//        }
//    }

    createGraph(graph_title, table_name, column_name);
}

#endif //SOLO_SCREEN_GRAPHS_MAKER_H
