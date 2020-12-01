//
// Created by vlad on 01.12.20.
//

#ifndef SOLO_PROCESSES_SCREEN_H
#define SOLO_PROCESSES_SCREEN_H

#include "proc_analysis.h"

class ProcessesScreen {
public:
    QLabel* label;
    QLabel* running_processes;
//    QLabel* cpu_vendor_id;
    QLabel* open_processes;
    QLabel* forks_since_boot;
    QLabel* time_since_boot;
    QWidget* window;
    QPushButton* back_button;

    ProcessesScreen() {
        window = new QWidget();
        label = new QLabel(window);

        running_processes = new QLabel(window);
        back_button = new QPushButton(window);

//        cpu_vendor_id = new QLabel(window);
        open_processes = new QLabel(window);

        forks_since_boot = new QLabel(window);
        time_since_boot = new QLabel(window);

        prepare_window();
        prepare_headline();
        prepare_back_button();
        prepare_running_processes();
//        prepare_blocked_processes();
        prepare_open_processes();
        prepare_forks_since_boot();
        prepare_time_since_boot();
    }

    void prepare_window() {
        window->setWindowState(Qt::WindowMaximized);
        window->setWindowTitle("GUI STATS");
    }

    void prepare_headline() {
        QFont font = label->font();
        font.setPointSize(72);
        font.setBold(true);

        label->setFont(font);
        QRect rec = QApplication::desktop()->screenGeometry();
        label->setText("Welcome to Process screen");
        label->setFixedWidth(rec.width());
        label->setFixedHeight(200);
        label->setAlignment(Qt::AlignCenter);
    }

    void prepare_back_button() {
        back_button->setText("Back");
        QFont font = back_button->font();

        font.setPointSize(36);
        font.setBold(true);

        back_button->setFont(font);
        back_button->move(200, 800);

        back_button->setBaseSize(100, 50);
    }

    void prepare_running_processes() {
        std::string value = "Running processes number: " +
                std::to_string(get_running_processes_amount());

        QFont font = running_processes->font();
        font.setPointSize(26);

        running_processes->setFont(font);
        running_processes->setText(QString::fromStdString(value));

        running_processes->setFixedHeight(200);
        running_processes->move(100, 400);
        running_processes->setAlignment(Qt::AlignCenter);
    }

//    void prepare_blocked_processes() {
//        std::string value = "Total blocked processes number: " +
//                            std::to_string(get_blocked_processes_amount());
//
//        QFont font = cpu_vendor_id->font();
//        font.setPointSize(26);
//
//        cpu_vendor_id->setFont(font);
//        cpu_vendor_id->setText(QString::fromStdString(value));
//
//        cpu_vendor_id->setFixedHeight(200);
//        cpu_vendor_id->move(100, 500);
//        cpu_vendor_id->setAlignment(Qt::AlignCenter);
//    }

    void prepare_open_processes() {
        std::string value = "Total open processes number: " +
                            std::to_string(get_total_open_processes_amount());

        QFont font = open_processes->font();
        font.setPointSize(26);

        open_processes->setFont(font);
        open_processes->setText(QString::fromStdString(value));

        open_processes->setFixedHeight(200);
        open_processes->move(100, 600);
        open_processes->setAlignment(Qt::AlignCenter);
    }

    void prepare_forks_since_boot() {
        std::string value = "Total forks since boot number: " +
                            std::to_string(get_forks_since_boot());

        QFont font = forks_since_boot->font();
        font.setPointSize(26);

        forks_since_boot->setFont(font);
        forks_since_boot->setText(QString::fromStdString(value));

        forks_since_boot->setFixedHeight(200);
        forks_since_boot->move(1000, 400);
        forks_since_boot->setAlignment(Qt::AlignCenter);
    }

    void prepare_time_since_boot() {
        std::string value = "Total time since boot (Unix): " +
                            std::to_string(get_time_since_boot());

        QFont font = time_since_boot->font();
        font.setPointSize(26);

        time_since_boot->setFont(font);
        time_since_boot->setText(QString::fromStdString(value));

        time_since_boot->setFixedHeight(200);
        time_since_boot->move(1000, 600);
        time_since_boot->setAlignment(Qt::AlignCenter);
    }
};

#endif //SOLO_PROCESSES_SCREEN_H
