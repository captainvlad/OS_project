#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <atomic>
#include <QtGui>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QDesktopWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>

#include "welcome_screen.h"
#include "explore_screen.h"
#include "processes_screen.h"
#include "info_screen.h"
#include "database_manipulation.h"
#include "cpu_screen.h"

std::atomic_bool close_signal = false;

void update_specs(int seconds_to_wait) {
    while (true) {
        sleep(seconds_to_wait);
        update_memory_table();

        if (close_signal) {
            return;
        }
    }
}

void init_info_screen();
void init_welcome_screen();

void init_explore_screen();
void init_processes_screen();

void init_cpu_screen();

void quit_app();


QApplication* app;

void back_button_callback() {
    app->closeAllWindows();
    auto window = WelcomeScreen();

//    QPushButton::connect(window.quit_button, &QPushButton::released, app, quit_button_callback);
//    QPushButton::connect(window.info_button, &QPushButton::released, app, info_button_callback);
    window.window->show();
}

void quit_app() {
    app->quit();
}

void init_welcome_screen() {
    app->closeAllWindows();
    auto window = WelcomeScreen();

    QPushButton::connect(window.quit_button, &QPushButton::released, app, quit_app);
    QPushButton::connect(window.info_button, &QPushButton::released, app, init_info_screen);
    QPushButton::connect(window.explore_button, &QPushButton::released, app, init_explore_screen);
    window.window->show();
}

void init_info_screen() {
    app->closeAllWindows();
    auto window = InfoScreen();

    QPushButton::connect(window.back_button, &QPushButton::released, app, init_welcome_screen);
    window.window->show();
}

void init_explore_screen() {
    app->closeAllWindows();
    auto window = ExploreScreen();

    QPushButton::connect(window.back_button, &QPushButton::released, app, init_welcome_screen);
    QPushButton::connect(window.processes_button, &QPushButton::released, app, init_processes_screen);
    QPushButton::connect(window.cpu_button, &QPushButton::released, app, init_cpu_screen);
    window.window->show();
}

void init_processes_screen() {
    app->closeAllWindows();
    auto window = ProcessesScreen();

    QPushButton::connect(window.back_button, &QPushButton::released, app, init_welcome_screen);
    window.window->show();
}

void init_cpu_screen() {
    app->closeAllWindows();
    auto window = CpuScreen();

    QPushButton::connect(window.back_button, &QPushButton::released, app, init_welcome_screen);
    window.window->show();
}

int main (int argc, char *argv[]) {

    app = new QApplication(argc, argv);
//    auto window = WelcomeScreen();
//
//    QPushButton::connect(window.quit_button, &QPushButton::released, app, quit_button_callback);
//    QPushButton::connect(window.info_button, &QPushButton::released, app, info_button_callback);
//
////    QPushButton::connect(back_button, &QPushButton::released, app, back_button_callback);
//
//    window.window->show();

    
    init_welcome_screen();
    return app->exec();
//    auto window = new QWidget();
//    window->setWindowState(Qt::WindowMaximized);
//    window->setWindowTitle("SAMPLE");
//
//    QLabel *label = new QLabel(window);
//    label->setText("Hello, world!");
//    label->setStyleSheet("background-color:blue");
//
//    QFont font = label->font();
//    font.setPointSize(72);
//    font.setBold(true);
//
//    label->setFont(font);
//    label->resize(1900, 500);


//

//    QPushButton *train_button = new QPushButton(window);
//    train_button->setText("Something");
//
//    QPushButton::connect(train_button, &QPushButton::clicked, app, );
//
////
//
//    QRect rec = QApplication::desktop()->screenGeometry();
//
//    label->setFixedWidth(rec.width());
//    label->setAlignment(Qt::AlignCenter);
//    label->show();
//    window->show();



//    std::thread thread_obj(update_specs, 1);
//
//    while (true) {
//        sleep(5);
//        break;
//    }
//
//    close_signal = true;
//    thread_obj.join();
//
//    auto db = open_database();
//
//    for (auto x: select_from_database(db, 0, "select * from memory")) {
//        std::cout << "AAA " << x << "\n";
//    }
//
//    close_database(db);
//    return 0;
}