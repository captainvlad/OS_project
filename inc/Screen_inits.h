//
// Created by vlad on 29.12.20.
//

#ifndef SOLO_SCREEN_INITS_H
#define SOLO_SCREEN_INITS_H

#include "Screen.h"

void Screen::init_welcome_window() {
    hide_all_items();
    headline_label->setText("Welcome");

    headline_label->setVisible(true);
    info_button->setVisible(true);

    explore_button->setVisible(true);
    quit_button->setVisible(true);
}

void Screen::init_cpu_window() {
    hide_all_items();

    headline_label->setText("Welcome to CPU screen");
    headline_label->setVisible(true);

    cpu_amount_label->setVisible(true);
    cpu_vendor_id_label->setVisible(true);

    cpu_model_name_label->setVisible(true);
    last_level_cache_size_label->setVisible(true);

    cpu_bogomips_label->setVisible(true);
    cpu_usage_label->setVisible(true);

    back_button->setVisible(true);
    cpu_bugs_label->setVisible(true);

    cpu_utilization_label->setVisible(true);
}

void Screen::init_info_window() {
    hide_all_items();
    headline_label->setText("Welcome to Info");
    headline_label->setVisible(true);

    back_button->setVisible(true);

    description_label->setText(description_text);
    description_label->setVisible(true);
}

void Screen::init_explore_window() {
    hide_all_items();

    headline_label->setText("Welcome to Explore screen");
    description_label->setText("Choose which component to explore: ");

    headline_label->setVisible(true);
    description_label->setVisible(true);

    cpu_button->setVisible(true);
    back_button->setVisible(true);

    memory_button->setVisible(true);
    processes_button->setVisible(true);

    filesystem_button->setVisible(true);
}

void Screen::init_processes_window() {
    hide_all_items();

    headline_label->setText("Welcome to Processes screen");

    back_button->setVisible(true);
    headline_label->setVisible(true);

    open_processes_label->setVisible(true);
    running_processes_label->setVisible(true);

    time_since_boot_label->setVisible(true);
    forks_since_boot_label->setVisible(true);
}

void Screen::init_filesystem_window() {
    hide_all_items();

    headline_label->setText("Welcome to Filesystem screen");
    headline_label->setVisible(true);

    back_button->setVisible(true);
    allocated_descriptors_label->setVisible(true);

    free_descriptors_label->setVisible(true);
    open_descriptors_limit->setVisible(true);
}

void Screen::init_memory_window() {
    hide_all_items();

    headline_label->setText("Welcome to Memory screen");
    headline_label->setVisible(true);

    back_button->setVisible(true);
    ram_size_label->setVisible(true);

    cached_ram_size_label->setVisible(true);
    available_ram_size_label->setVisible(true);

    dirty_ram->setVisible(true);
    active_ram->setVisible(true);

    inactive_ram->setVisible(true);
}

void Screen::init_post_quit_window() {
    hide_all_items();

    headline_label->setText("Do you want to clear database?");
    headline_label->setVisible(true);

    clear_database_button->setVisible(true);
    no_clear_database_button->setVisible(true);
}

void Screen::init_all_window_items() {
    prepare_window();
    prepare_headline();

    prepare_cpu_bugs();
    prepare_cpu_usage();

    prepare_quit_button();
    prepare_info_button();

    prepare_back_button();
    prepare_explore_button();

    prepare_description();
    prepare_processes_button();

    prepare_cpu_button();
    prepare_open_processes();

    prepare_memory_button();
    prepare_filesystem_button();

    prepare_time_since_boot();
    prepare_forks_since_boot();

    prepare_cpu_amount();
    prepare_cpu_vendor_id();

    prepare_cpu_bogomips();
    prepare_cpu_model_name();

    prepare_last_level_cache_size();
    prepare_running_processes_label();

    prepare_cpu_utilization();
    prepare_allocated_descriptors_label();

    prepare_free_descriptors_label();
    prepare_open_descriptors_limit();

    prepare_ram_size_label();
    prepare_available_ram_size();

    prepare_cached_ram_size();
    prepare_active_ram_size();

    prepare_inactive_ram_size();
    prepare_dirty_ram_size();

    prepare_remove_graph_button();
    prepare_yes_no_clear_buttons();

    prepare_chartview();
}

#endif //SOLO_SCREEN_INITS_H
