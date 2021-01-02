//
// Created by vlad on 29.12.20.
//

#ifndef SOLO_SCREEN_MANIPULATIONS_H
#define SOLO_SCREEN_MANIPULATIONS_H

#include <iostream>
#include "Screen.h"
#include "utils.h"
#include "database_manipulation.h"

void Screen::update_current_window() {

    if (headline_label->text().contains("Processes screen")) {
        init_all_window_items();
        init_processes_window();
    } else if (headline_label->text().contains("CPU screen")) {
        init_all_window_items();
        init_cpu_window();
    } else if (headline_label->text().contains("Filesystem screen")) {
        init_all_window_items();
        init_filesystem_window();
    } else if (headline_label->text().contains("Memory screen")) {
        init_all_window_items();
        init_memory_window();
    }

    if (graph_is_used) {
        createGraph(graph_title, table_name, column_name);
    }

    if (close_program) {
        workerThread->terminate();
        clear_all_tables();
        QApplication::quit();
    }
}

void Screen::hide_all_items() {
    explore_button->setVisible(false);
    headline_label->setVisible(false);
    info_button->setVisible(false);
    quit_button->setVisible(false);
    back_button->setVisible(false);
    description_label->setVisible(false);
    processes_button->setVisible(false);
    cpu_button->setVisible(false);
    filesystem_button->setVisible(false);
    memory_button->setVisible(false);
    running_processes_label->setVisible(false);
    open_processes_label->setVisible(false);
    forks_since_boot_label->setVisible(false);
    time_since_boot_label->setVisible(false);

    cpu_amount_label->setVisible(false);
    cpu_vendor_id_label->setVisible(false);
    cpu_model_name_label->setVisible(false);
    last_level_cache_size_label->setVisible(false);
    cpu_bogomips_label->setVisible(false);
    cpu_usage_label->setVisible(false);
    cpu_bugs_label->setVisible(false);
    cpu_utilization_label->setVisible(false);

    allocated_descriptors_label->setVisible(false);
    free_descriptors_label->setVisible(false);
    open_descriptors_limit->setVisible(false);

    ram_size_label->setVisible(false);
    available_ram_size_label->setVisible(false);
    cached_ram_size_label->setVisible(false);
    active_ram->setVisible(false);
    inactive_ram->setVisible(false);
    dirty_ram->setVisible(false);

    remove_graph_button->setVisible(false);
    chartView->setVisible(false);

    no_clear_database_button->setVisible(false);
    clear_database_button->setVisible(false);
}

void Screen::start_work_in_thread() {
    workerThread = new WorkerThread();
    connect(workerThread, SIGNAL(process_changed(QString)), SLOT(onProgressChanged(QString)));

    workerThread->start();
}

void Screen::createGraph(std::string title, std::string table_name, std::string column_name) {
    graph_is_used = true;
    remove_graph_button->setVisible(true);
    chartView->setVisible(true);

    chart->removeAllSeries();
    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();

    auto database_connection = open_database();
    auto info = select_from_database(database_connection, 0, "SELECT " + column_name + " from " + table_name + ";");

    int i = 0;

    if (column_name == "cpu_usage_label") {
        QtCharts::QLineSeries *series2 = new QtCharts::QLineSeries();
        QtCharts::QLineSeries *series3 = new QtCharts::QLineSeries();
        QtCharts::QLineSeries *series4 = new QtCharts::QLineSeries();

        series->setName("User mode");
        series2->setName("Nice mode");
        series3->setName("System mode");
        series4->setName("Idle mode");

        for (auto a: info) {
            auto parsed_info = parseCPUusage(a);
            series->append(i, parsed_info[0]);
            series2->append(i, parsed_info[1]);
            series3->append(i, parsed_info[2]);
            series4->append(i, parsed_info[3]);

            i++;
        }


        chart->addSeries(series);
        chart->addSeries(series2);
        chart->addSeries(series3);
        chart->addSeries(series4);

        chart->createDefaultAxes();

        chart->setTitle(QString().fromStdString(title));
        chartView->setRenderHint(QPainter::Antialiasing);

        close_database(database_connection);
        return;
    }

    for (auto x: info) {
        series->append(i, std::stod(x));
        i++;
    }

    chart->addSeries(series);
    chart->createDefaultAxes();

    chart->setTitle(QString().fromStdString(title));
    chartView->setRenderHint(QPainter::Antialiasing);

    close_database(database_connection);
}

#endif //SOLO_SCREEN_MANIPULATIONS_H
