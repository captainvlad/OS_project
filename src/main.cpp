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
#include "info_screen.h"
#include "database_manipulation.h"

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

QApplication* app;

void back_button_callback() {
    app->closeAllWindows();
    auto window = WelcomeScreen();

//    QPushButton::connect(window.quit_button, &QPushButton::released, app, quit_button_callback);
//    QPushButton::connect(window.info_button, &QPushButton::released, app, info_button_callback);
    window.window->show();
}

void quit_button_callback() {
    app->quit();
}

void info_button_callback() {
    app->closeAllWindows();
    InfoScreen().window->show();
}

void init_welcome_screen() {
    
}

int main (int argc, char *argv[]) {

    app = new QApplication(argc, argv);
    auto window = WelcomeScreen();

    QPushButton::connect(window.quit_button, &QPushButton::released, app, quit_button_callback);
    QPushButton::connect(window.info_button, &QPushButton::released, app, info_button_callback);

//    QPushButton::connect(back_button, &QPushButton::released, app, back_button_callback);

    window.window->show();

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