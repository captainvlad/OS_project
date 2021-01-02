//
// Created by vlad on 29.12.20.
//

#ifndef SOLO_SCREEN_PREPARATIONS_H
#define SOLO_SCREEN_PREPARATIONS_H

#include "Screen.h"

void Screen::prepare_ram_size_label() {
    std::string value = "Total RAM size: " + get_total_ram_size();

    QFont font = ram_size_label->font();
    font.setPointSize(26);

    ram_size_label->setFont(font);
    ram_size_label->setText(QString::fromStdString(value));

    ram_size_label->setFixedHeight(50);
    ram_size_label->move(100, 200);
    ram_size_label->setAlignment(Qt::AlignCenter);
}

void Screen::prepare_allocated_descriptors_label() {
    std::string value = "Total allocated descriptors number: " + std::to_string(get_total_allocated_descriptors());

    QFont font = allocated_descriptors_label->font();
    font.setPointSize(26);

    allocated_descriptors_label->setFont(font);

    allocated_descriptors_label->setFixedHeight(50);
    allocated_descriptors_label->setFixedWidth(800);

    allocated_descriptors_label->move(100, 200);

    allocated_descriptors_label->setText(QString::fromStdString(value));
}

void Screen::prepare_free_descriptors_label() {
    std::string value = "Total free descriptors number:  " + std::to_string(get_total_free_descriptors());

    QFont font = free_descriptors_label->font();
    font.setPointSize(26);

    free_descriptors_label->setFont(font);
    free_descriptors_label->setText(QString::fromStdString(value));

    free_descriptors_label->setFixedHeight(50);
    free_descriptors_label->setFixedWidth(800);

    free_descriptors_label->move(100, 300);
}

void Screen::prepare_running_processes_label() {
    std::string value = "Running processes number: " +
                        std::to_string(get_running_processes_amount());

    QFont font = running_processes_label->font();
    font.setPointSize(26);

    running_processes_label->setFont(font);
    running_processes_label->setText(QString::fromStdString(value));

    running_processes_label->setFixedHeight(50);
    running_processes_label->setFixedWidth(700);

    running_processes_label->move(100, 400);
}

void Screen::prepare_back_button() {
    QFont font = back_button->font();

    font.setPointSize(36);
    font.setBold(true);

    back_button->setFont(font);
    back_button->move(200, 800);

    back_button->setFixedWidth(200);
    back_button->setFixedHeight(100);
}

void Screen::prepare_description() {
    description_label->setText(description_text);
    QFont font = description_label->font();
    font.setPointSize(36);

    description_label->setAlignment(Qt::AlignCenter);
    description_label->setFixedWidth(rec.width());

    description_label->move(0, 400);
    description_label->setFont(font);
    description_label->setWordWrap(true);
}

void Screen::prepare_window() {
    setWindowState(Qt::WindowMaximized);
    setWindowTitle(title);
}

void Screen::prepare_headline() {
    headline_label->setText("-");
    headline_label->setFixedWidth(rec.width());

    QFont font = headline_label->font();
    font.setPointSize(72);
    font.setBold(true);

    headline_label->setFont(font);
    headline_label->setFixedHeight(200);
    headline_label->setAlignment(Qt::AlignCenter);
}

void Screen::prepare_info_button() {
    QFont font = headline_label->font();
    font.setPointSize(32);
    info_button->setFont(font);

    info_button->setFixedWidth(200);
    info_button->setFixedHeight(100);
    info_button->move(rec.width() / 2 - 100, rec.height() / 2 - 200);
}

void Screen::prepare_explore_button() {
    QFont font = explore_button->font();

    font.setBold(true);
    font.setPointSize(32);

    explore_button->setFixedWidth(200);
    explore_button->setFixedHeight(100);

    explore_button->setFont(font);
    explore_button->move(rec.width() / 2 - 100, rec.height() / 2 - 50);
}

void Screen::prepare_quit_button() {
    QFont font = quit_button->font();

    font.setBold(true);
    font.setPointSize(32);

    quit_button->setFixedWidth(200);
    quit_button->setFixedHeight(100);

    quit_button->setFont(font);
    quit_button->move(rec.width() / 2 - 100, rec.height() / 2 + 100);
}

void Screen::prepare_processes_button() {
    QFont font = processes_button->font();

    font.setPointSize(36);

    processes_button->setFont(font);
    processes_button->move(1200, 500);

    processes_button->setFixedSize(400, 50);
}

void Screen::prepare_cpu_button() {
    QFont font = cpu_button->font();
    font.setPointSize(36);

    cpu_button->setFont(font);
    cpu_button->move(1200, 600);

    cpu_button->setFixedSize(400, 50);
}

void Screen::prepare_filesystem_button() {
    QFont font = filesystem_button->font();
    font.setPointSize(36);

    filesystem_button->setFont(font);
    filesystem_button->move(1200, 700);

    filesystem_button->setFixedSize(400, 50);
}

void Screen::prepare_memory_button() {
    QFont font = memory_button->font();

    font.setPointSize(36);

    memory_button->setFont(font);
    memory_button->move(1200, 800);

    memory_button->setFixedSize(400, 50);
}

void Screen::prepare_cpu_bugs() {
    std::string value = "CPU bugs: \n\t" + get_cpu_bugs();

    QFont font = cpu_bugs_label->font();
    font.setPointSize(26);

    cpu_bugs_label->setFont(font);
    cpu_bugs_label->setText(QString::fromStdString(value));

    cpu_bugs_label->setFixedHeight(75);
    cpu_bugs_label->move(100, 700);
}

void Screen::prepare_available_ram_size() {
    std::string value = "Available RAM size: " + get_availible_ram();

    QFont font = available_ram_size_label->font();
    font.setPointSize(26);

    available_ram_size_label->setFont(font);
    available_ram_size_label->setText(QString::fromStdString(value));

    available_ram_size_label->setFixedHeight(50);
    available_ram_size_label->setFixedWidth(600);

    available_ram_size_label->move(100, 300);
}

void Screen::prepare_cached_ram_size() {
    std::string value = "Cached RAM size:" + get_cached_ram();

    QFont font = cached_ram_size_label->font();
    font.setPointSize(26);

    cached_ram_size_label->setFont(font);
    cached_ram_size_label->setText(QString::fromStdString(value));

    cached_ram_size_label->setFixedHeight(50);
    cached_ram_size_label->setFixedWidth(600);

    cached_ram_size_label->move(100, 400);
}

void Screen::prepare_active_ram_size() {
    std::string value = "Active RAM size:" + get_active_ram();

    QFont font = active_ram->font();
    font.setPointSize(26);

    active_ram->setFont(font);
    active_ram->setText(QString::fromStdString(value));

    active_ram->setFixedHeight(50);
    active_ram->setFixedWidth(600);

    active_ram->move(100, 500);
}

void Screen::prepare_inactive_ram_size() {
    std::string value = "Inactive RAM size:" + get_inactive_ram();

    QFont font = inactive_ram->font();
    font.setPointSize(26);

    inactive_ram->setFont(font);
    inactive_ram->setText(QString::fromStdString(value));

    inactive_ram->setFixedHeight(50);
    inactive_ram->setFixedWidth(600);

    inactive_ram->move(100, 600);
}

void Screen::prepare_dirty_ram_size() {
    std::string value = "Dirty RAM size:" + get_dirty_ram();

    QFont font = dirty_ram->font();
    font.setPointSize(26);

    dirty_ram->setFont(font);
    dirty_ram->setText(QString::fromStdString(value));

    dirty_ram->setFixedHeight(50);
    dirty_ram->setFixedWidth(600);

    dirty_ram->move(100, 700);
}

void Screen::prepare_time_since_boot() {
    std::string value = "Total time since boot (Unix): " +
                        std::to_string(get_time_since_boot());

    QFont font = time_since_boot_label->font();
    font.setPointSize(26);

    time_since_boot_label->setFont(font);
    time_since_boot_label->setText(QString::fromStdString(value));

    time_since_boot_label->setFixedHeight(50);
    time_since_boot_label->setFixedWidth(700);

    time_since_boot_label->move(100, 700);
}

void Screen::prepare_open_descriptors_limit() {
    std::string value = "Open descriptors limit: " + std::to_string(get_open_descriptors_limit());

    QFont font = open_descriptors_limit->font();
    font.setPointSize(26);

    open_descriptors_limit->setFont(font);
    open_descriptors_limit->setText(QString::fromStdString(value));

    open_descriptors_limit->setFixedHeight(50);
    open_descriptors_limit->move(100, 400);
    open_descriptors_limit->setAlignment(Qt::AlignCenter);
}

void Screen::prepare_open_processes() {
    std::string value = "Total open processes number: " +
                        std::to_string(get_total_open_processes_amount());

    QFont font = open_processes_label->font();
    font.setPointSize(26);

    open_processes_label->setFont(font);
    open_processes_label->setText(QString::fromStdString(value));

    open_processes_label->setFixedHeight(50);
    open_processes_label->setFixedWidth(700);

    open_processes_label->move(100, 500);
}

void Screen::prepare_forks_since_boot() {
    std::string value = "Total forks since boot number: " +
                        std::to_string(get_forks_since_boot());

    QFont font = forks_since_boot_label->font();
    font.setPointSize(26);

    forks_since_boot_label->setFont(font);
    forks_since_boot_label->setText(QString::fromStdString(value));

    forks_since_boot_label->setFixedHeight(50);
    forks_since_boot_label->setFixedWidth(700);

    forks_since_boot_label->move(100, 600);
}

void Screen::prepare_cpu_amount() {
    std::string value = "CPU cores number: " + get_cpu_cores_amount();

    QFont font = cpu_amount_label->font();
    font.setPointSize(26);

    cpu_amount_label->setFont(font);
    cpu_amount_label->setText(QString::fromStdString(value));

    cpu_amount_label->setFixedHeight(50);
    cpu_amount_label->move(100, 600);
    cpu_vendor_id_label->setAlignment(Qt::AlignCenter);
}

void Screen::prepare_cpu_vendor_id() {
    std::string value = "CPU vendor: " + get_cpu_vendor_id();

    QFont font = cpu_vendor_id_label->font();
    font.setPointSize(26);

    cpu_vendor_id_label->setFont(font);
    cpu_vendor_id_label->setText(QString::fromStdString(value));

    cpu_vendor_id_label->setFixedHeight(50);
    cpu_vendor_id_label->move(800, 200);
    cpu_vendor_id_label->setAlignment(Qt::AlignCenter);
}

void Screen::prepare_cpu_model_name() {
    std::string value = "CPU model name: " + get_cpu_model_name();

    QFont font = cpu_model_name_label->font();
    font.setPointSize(26);

    cpu_model_name_label->setFont(font);
    cpu_model_name_label->setText(QString::fromStdString(value));

    cpu_model_name_label->setFixedHeight(50);
    cpu_model_name_label->move(800, 300);
    cpu_model_name_label->setAlignment(Qt::AlignCenter);
}

void Screen::prepare_last_level_cache_size() {
    std::string value = "Last level cache size: " + get_last_level_cache_size();

    QFont font = last_level_cache_size_label->font();
    font.setPointSize(26);

    last_level_cache_size_label->setFont(font);
    last_level_cache_size_label->setText(QString::fromStdString(value));

    last_level_cache_size_label->setFixedHeight(50);
    last_level_cache_size_label->move(800, 400);
    last_level_cache_size_label->setAlignment(Qt::AlignCenter);
}

void Screen::prepare_cpu_bogomips() {
    std::string value = "CPU bogomips: " + get_cpu_bogomips();

    QFont font = cpu_bogomips_label->font();
    font.setPointSize(26);

    cpu_bogomips_label->setFont(font);
    cpu_bogomips_label->setText(QString::fromStdString(value));

    cpu_bogomips_label->setFixedHeight(50);
    cpu_bogomips_label->move(800, 500);
    cpu_bogomips_label->setAlignment(Qt::AlignCenter);
}

void Screen::prepare_cpu_utilization() {
    std::string value = "CPU utilization: ";

    for (auto item: get_cpu_utilization()) {
        value += item;
    }

    QFont font = cpu_utilization_label->font();
    font.setPointSize(26);

    cpu_utilization_label->setFont(font);
    cpu_utilization_label->setText(QString::fromStdString(value));

    cpu_utilization_label->setFixedHeight(50);
    cpu_utilization_label->setFixedWidth(600);

    cpu_utilization_label->move(100, 200);
}

void Screen::prepare_cpu_usage() {
    std::string value = "CPU usage: ";

    for (auto item: get_cpu_usage()) {
        value += "\n\t";
        value += item;
    }

    QFont font = cpu_usage_label->font();
    font.setPointSize(26);

    cpu_usage_label->setFont(font);
    cpu_usage_label->setText(QString::fromStdString(value));

    cpu_usage_label->setFixedHeight(200);
    cpu_usage_label->setFixedWidth(600);

    cpu_usage_label->move(100, 300);
}

void Screen::prepare_remove_graph_button() {
    QFont font = remove_graph_button->font();

    font.setPointSize(36);
    font.setBold(true);

    remove_graph_button->setFont(font);
    remove_graph_button->move(1250, 160);

    remove_graph_button->setFixedWidth(600);
    remove_graph_button->setFixedHeight(100);
}

void Screen::prepare_chartview() {
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(800, 400);

    chartView->move(1000, 400);
}

void Screen::prepare_yes_no_clear_buttons() {
    QFont font = clear_database_button->font();

    font.setPointSize(36);
    font.setBold(true);

    clear_database_button->setFont(font);
    clear_database_button->move(250, 400);

    clear_database_button->setFixedWidth(600);
    clear_database_button->setFixedHeight(100);

    no_clear_database_button->setFont(font);
    no_clear_database_button->move(1050, 400);

    no_clear_database_button->setFixedWidth(600);
    no_clear_database_button->setFixedHeight(100);
}

#endif //SOLO_SCREEN_PREPARATIONS_H
