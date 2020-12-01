//
// Created by vlad on 01.12.20.
//

#ifndef SOLO_CPU_SCREEN_H
#define SOLO_CPU_SCREEN_H

#include "proc_analysis.h"

class CpuScreen {
public:
    QLabel* label;
    QLabel* cpu_amount;
    QLabel* cpu_vendor_id;
    QLabel* cpu_model_name;
    QLabel* last_level_cache_size;
    QLabel* cpu_bogomips;
//    QLabel* cpu_bugs;

    QLabel* cpu_utilization;
    QLabel* cpu_usage;

    QWidget* window;
    QPushButton* back_button;

    CpuScreen() {
        window = new QWidget();
        label = new QLabel(window);

        cpu_amount = new QLabel(window);
        back_button = new QPushButton(window);

        cpu_vendor_id = new QLabel(window);
        cpu_model_name = new QLabel(window);

        last_level_cache_size = new QLabel(window);
        cpu_bogomips = new QLabel(window);

//        cpu_bugs = new QLabel(window);
        cpu_utilization = new QLabel(window);
        cpu_usage = new QLabel(window);

        prepare_window();
        prepare_headline();
        prepare_back_button();
        prepare_cpu_amount();
        prepare_cpu_vendor_id();
        prepare_cpu_model_name();
        prepare_last_level_cache_size();
        prepare_cpu_bogomips();
//        prepare_cpu_bugs();
        prepare_cpu_utilization();
        prepare_cpu_usage();
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
        label->setText("Welcome to CPU screen");
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

    void prepare_cpu_amount() {
        std::string value = "CPU cores number: " + get_cpu_cores_amount();

        QFont font = cpu_amount->font();
        font.setPointSize(26);

        cpu_amount->setFont(font);
        cpu_amount->setText(QString::fromStdString(value));

        cpu_amount->setFixedHeight(200);
        cpu_amount->move(100, 200);
        cpu_amount->setAlignment(Qt::AlignCenter);
    }

    void prepare_cpu_vendor_id() {
        std::string value = "CPU vendor: " + get_cpu_vendor_id();

        QFont font = cpu_vendor_id->font();
        font.setPointSize(26);

        cpu_vendor_id->setFont(font);
        cpu_vendor_id->setText(QString::fromStdString(value));

        cpu_vendor_id->setFixedHeight(200);
        cpu_vendor_id->move(100, 250);
        cpu_vendor_id->setAlignment(Qt::AlignCenter);
    }

    void prepare_cpu_model_name() {
        std::string value = "CPU model name: " + get_cpu_model_name();

        QFont font = cpu_model_name->font();
        font.setPointSize(26);

        cpu_model_name->setFont(font);
        cpu_model_name->setText(QString::fromStdString(value));

        cpu_model_name->setFixedHeight(200);
        cpu_model_name->move(100, 300);
        cpu_model_name->setAlignment(Qt::AlignCenter);
    }

    void prepare_last_level_cache_size() {
        std::string value = "Last level cache size: " + get_last_level_cache_size();

        QFont font = last_level_cache_size->font();
        font.setPointSize(26);

        last_level_cache_size->setFont(font);
        last_level_cache_size->setText(QString::fromStdString(value));

        last_level_cache_size->setFixedHeight(200);
        last_level_cache_size->move(100, 350);
        last_level_cache_size->setAlignment(Qt::AlignCenter);
    }

    void prepare_cpu_bogomips() {
        std::string value = "CPU bogomips: " + get_cpu_bogomips();

        QFont font = cpu_bogomips->font();
        font.setPointSize(26);

        cpu_bogomips->setFont(font);
        cpu_bogomips->setText(QString::fromStdString(value));

        cpu_bogomips->setFixedHeight(200);
        cpu_bogomips->move(100, 400);
        cpu_bogomips->setAlignment(Qt::AlignCenter);
    }

//    void prepare_cpu_bugs() {
//        std::string value = "CPU bugs: \n\t" + get_cpu_bugs();
//
//        QFont font = cpu_bugs->font();
//        font.setPointSize(26);
//
//        cpu_bugs->setFont(font);
//        cpu_bugs->setText(QString::fromStdString(value));
//
//        cpu_bugs->setFixedHeight(200);
//        cpu_bugs->move(100, 475);
//    }

    void prepare_cpu_utilization() {
        std::string value = "CPU utilization: ";

        for (auto item: get_cpu_utilization()) {
            value += item;
        }

        QFont font = cpu_bogomips->font();
        font.setPointSize(26);

        cpu_bogomips->setFont(font);
        cpu_bogomips->setText(QString::fromStdString(value));

        cpu_bogomips->setFixedHeight(200);
        cpu_bogomips->move(100, 400);
    }

    void prepare_cpu_usage() {
        std::string value = "CPU usage: ";

        for (auto item: get_cpu_usage()) {
            value += "\n\t";
            value += item;
        }

        QFont font = cpu_bogomips->font();
        font.setPointSize(26);

        cpu_usage->setFont(font);
        cpu_usage->setText(QString::fromStdString(value));

        cpu_usage->setFixedHeight(200);
        cpu_usage->move(1200, 525);
    }
};

#endif //SOLO_CPU_SCREEN_H
