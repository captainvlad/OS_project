//
// Created by vlad on 01.12.20.
//

#ifndef SOLO_WELCOME_SCREEN_H
#define SOLO_WELCOME_SCREEN_H

class WelcomeScreen {
public:
    QLabel* label;
    QWidget* window;
    QPushButton* info_button;
    QPushButton* explore_button;
    QPushButton* quit_button;

    WelcomeScreen() {
        window = new QWidget();
        label = new QLabel(window);
        info_button = new QPushButton(window);
        explore_button = new QPushButton(window);
        quit_button = new QPushButton(window);

        prepare_window();
        prepare_headline();
        prepare_info_button();
        prepare_explore_button();
        prepare_quit_button();
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
        label->setText("Welcome");
        label->setFixedWidth(rec.width());
        label->setFixedHeight(200);
        label->setAlignment(Qt::AlignCenter);
    }

    void prepare_info_button() {
        QFont font = info_button->font();
        font.setPointSize(32);

        info_button->setFont(font);
        info_button->setText("Info");

        info_button->setFixedWidth(200);
        info_button->setFixedHeight(100);

        QRect rec = QApplication::desktop()->screenGeometry();
        info_button->move(rec.width() / 2 - 100, rec.height() / 2 - 200);
    }

    void prepare_explore_button() {
        QFont font = explore_button->font();
        font.setPointSize(32);

        explore_button->setFont(font);
        explore_button->setText("Explore");

        explore_button->setFixedWidth(200);
        explore_button->setFixedHeight(100);

        QRect rec = QApplication::desktop()->screenGeometry();
        explore_button->move(rec.width() / 2 - 100, rec.height() / 2 - 50);
    }

    void prepare_quit_button() {
        QFont font = quit_button->font();
        font.setPointSize(32);

        quit_button->setFont(font);
        quit_button->setText("Quit");

        quit_button->setFixedWidth(200);
        quit_button->setFixedHeight(100);

        QRect rec = QApplication::desktop()->screenGeometry();
        quit_button->move(rec.width() / 2 - 100, rec.height() / 2 + 100);
    }
};

#endif //SOLO_WELCOME_SCREEN_H
