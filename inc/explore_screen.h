//
// Created by vlad on 01.12.20.
//

#ifndef SOLO_EXPLORE_SCREEN_H
#define SOLO_EXPLORE_SCREEN_H

class ExploreScreen {
public:
    QLabel* label;
    QWidget* window;
    QLabel* description;
    QPushButton* back_button;
    QPushButton* processes_button;
    QPushButton* cpu_button;
    QPushButton* files_button;
    QPushButton* memory_button;

    ExploreScreen() {
        window = new QWidget();
        label = new QLabel(window);

        description = new QLabel(window);
        back_button = new QPushButton(window);

        processes_button = new QPushButton(window);
        cpu_button = new QPushButton(window);

        files_button = new QPushButton(window);
        memory_button = new QPushButton(window);

        prepare_window();
        prepare_headline();
        prepare_back_button();
        prepare_description();
        prepare_processes_button();
        prepare_files_button();
        prepare_cpu_button();
        prepare_memory_button();
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
        label->setText("Welcome to Explore screen");
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

        description->setFixedWidth(rec.width());
        description->move(200, 400);

        description->setWordWrap(true);
        description->setFont(font);

        description->setText("Choose which component to explore: ");
    }

    void prepare_processes_button() {
        processes_button->setText("Processes stats");
        QFont font = processes_button->font();

        font.setPointSize(36);

        processes_button->setFont(font);
        processes_button->move(1200, 500);

        processes_button->setFixedSize(400, 50);
    }

    void prepare_cpu_button() {
        cpu_button->setText("CPU stats");
        QFont font = cpu_button->font();

        font.setPointSize(36);

        cpu_button->setFont(font);
        cpu_button->move(1200, 600);

        cpu_button->setFixedSize(400, 50);
    }

    void prepare_files_button() {
        files_button->setText("Filesystem stats");
        QFont font = cpu_button->font();

        font.setPointSize(36);

        files_button->setFont(font);
        files_button->move(1200, 700);

        files_button->setFixedSize(400, 50);
    }

    void prepare_memory_button() {
        memory_button->setText("Memory stats");
        QFont font = memory_button->font();

        font.setPointSize(36);

        memory_button->setFont(font);
        memory_button->move(1200, 800);

        memory_button->setFixedSize(400, 50);
    }
};

#endif //SOLO_EXPLORE_SCREEN_H
