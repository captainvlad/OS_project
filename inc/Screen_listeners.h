//
// Created by vlad on 29.12.20.
//

#ifndef SOLO_SCREEN_LISTENERS_H
#define SOLO_SCREEN_LISTENERS_H

#include "Screen.h"
#include "database_manipulation.h"

//    These are listeners for different buttons clicks and are used in 'Screen.h' file.
    void Screen::OnInfo() {
        init_info_window();
    }

    void Screen::OnQuit() {
        init_post_quit_window();
    }

    void Screen::OnBack() {
        if (headline_label->text() == QString("Welcome"))
            return;

        if (headline_label->text() == QString("Welcome to Info") ||
            headline_label->text() == QString("Welcome to Explore screen")) {
            init_welcome_window();
        } else {
            init_explore_window();
        }

        grapghIsUsed = false;
    }

    void Screen::OnExplore() {
        init_explore_window();
    }

    void Screen::OnProcesses() {
        init_processes_window();
    }

    void Screen::OnCPU() {
        init_cpu_window();
    }

    void Screen::OnFilesystem() {
        init_filesystem_window();
    }

    void Screen::OnMemory() {
        init_memory_window();
    }

    void Screen::OnRemoveGraph() {
        grapghIsUsed = false;
    }

    void Screen::clear_database_and_quit() {
        workerThread->terminate();
        clear_all_tables();
        QApplication::quit();
    }

    void Screen::quit() {
        workerThread->terminate();
        QApplication::quit();
    }

#endif //SOLO_SCREEN_LISTENERS_H
