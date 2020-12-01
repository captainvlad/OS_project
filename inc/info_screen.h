//
// Created by vlad on 01.12.20.
//

#ifndef SOLO_INFO_SCREEN_H
#define SOLO_INFO_SCREEN_H

class InfoScreen {
public:
    QLabel* label;
    QLabel* description;
    QWidget* window;
    QPushButton* back_button;

    InfoScreen() {
        window = new QWidget();
        label = new QLabel(window);

        description = new QLabel(window);
        back_button = new QPushButton(window);

        prepare_window();
        prepare_headline();
        prepare_back_button();
        prepare_description();
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
        label->setText("Welcome to Info");
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

    void prepare_description() {
        QRect rec = QApplication::desktop()->screenGeometry();
        QFont font = description->font();

        font.setPointSize(48);
        font.setBold(true);

        description->setAlignment(Qt::AlignCenter);
        description->setFixedWidth(rec.width());

        description->move(0, 400);
        description->setFont(font);

        description->setText("Description is yet to come");
        description->setWordWrap(true);
    }
};

#endif //SOLO_INFO_SCREEN_H
