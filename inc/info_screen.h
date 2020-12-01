//
// Created by vlad on 01.12.20.
//

#ifndef SOLO_INFO_SCREEN_H
#define SOLO_INFO_SCREEN_H

class InfoScreen {
public:
    QLabel* label;
    QWidget* window;
    QPushButton* back_button;

    InfoScreen() {
        window = new QWidget();
        label = new QLabel(window);
        back_button = new QPushButton(window);

        prepare_window();
        prepare_headline();
        prepare_back_button();
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
    }
};

#endif //SOLO_INFO_SCREEN_H
