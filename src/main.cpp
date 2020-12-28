#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <unistd.h>
#include <atomic>
#include <QtGui>

#include <QChart>
#include <QtWidgets/QWidget>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QDesktopWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QLineSeries>
#include <QChartView>
#include <QMainWindow>

#include "proc_analysis.h"
//QApplication* app;

std::atomic_bool close_signal = false;
void update_specs() {
    int s = 0;

    while (true) {
        s++;
//        q->setText( QString(s) );
//        update_memory_table();

        std::cout << "Current value is: " << s << "\n";
        if (close_signal) {
            return;
        }
    }
}

class WorkerThread : public QThread {
    Q_OBJECT

    void run() {
        std::atomic_int i = 0;
        while(1) {
            // ... hard work
            // Now want to notify main thread:
            sleep(1);
            i.operator++();
            emit progressChanged(QString::number(i));
        }
    }
    // Define signal:
signals:
    void progressChanged(QString info);
};

class Screen : public QWidget
{
Q_OBJECT

public:
    Screen(QWidget *parent = 0) {
        init_all_window_items();
        init_welcome_window();

        connect(info_button, SIGNAL(clicked()), this, SLOT(OnInfo()));
        connect(quit_button, SIGNAL(clicked()), this, SLOT(OnQuit()));
        connect(back_button, SIGNAL(clicked()), this, SLOT(OnBack()));
        connect(explore_button, SIGNAL(clicked()), this, SLOT(OnExplore()));
        connect(processes_button, SIGNAL(clicked()), this, SLOT(OnProcesses()));
        connect(cpu_button, SIGNAL(clicked()), this, SLOT(OnCPU()));
        connect(filesystem_button, SIGNAL(clicked()), this, SLOT(OnFilesystem()));
        connect(memory_button, SIGNAL(clicked()), this, SLOT(OnMemory()));

        startWorkInAThread();
    }

    ~Screen(){}

private slots:
    void OnInfo() {
        init_info_window();
    }

    void OnQuit() {
        workerThread->terminate();
        QApplication::quit();
    }

    void OnBack() {
//        workerThread->terminate();
        bool welcome_window_now = headline_label->text() == QString("Welcome");

        if (welcome_window_now)
            return;

        if (headline_label->text() == QString("Welcome to Info") ||
                headline_label->text() == QString("Welcome to Explore screen")) {
            init_welcome_window();
        } else {
            init_explore_window();
        }
    }

    void OnExplore() {
        init_explore_window();
    }

    void OnProcesses() {
        init_processes_window();
    }

    void OnCPU() {
        init_cpu_window();
    }

    void OnFilesystem() {
        init_filesystem_window();
    }

    void OnMemory() {
        init_memory_window();
    }

    void onProgressChanged(QString info) {
        // Processing code
        std::string value = get_dirty_ram();
        update_current_window();
//        dirty_ram->setText(QString::fromStdString(value));
//        init_all_window_items();
//        init_memory_window();
//        init_all_window_items();
    }
private:
    QRect rec = QApplication::desktop()->screenGeometry();

    WorkerThread *workerThread;

    QString title = "GUI STATS";
    QString headline = "Headline sample";
    QString description_text = "This program is designed to present the user information\n"
                               "about system, using /proc information. Using the program,\n you can get info on:"
                               "\n\n -CPU \n -Processes \n -Files \n -Memory ";

    QPushButton* explore_button = new QPushButton("Explore", this);
    QPushButton* info_button = new QPushButton("Info", this);
    QPushButton* quit_button = new QPushButton("Quit", this);
    QPushButton* back_button = new QPushButton("Back", this);
    QPushButton* processes_button = new QPushButton("Processes stats", this);
    QPushButton* cpu_button = new QPushButton("CPU stats", this);
    QPushButton* filesystem_button = new QPushButton("Filesystem stats", this);
    QPushButton* memory_button = new QPushButton("Memory stats", this);

    QLabel* running_processes_label = new QLabel(this);
    QLabel* forks_since_boot = new QLabel(this);
    QLabel* open_processes = new QLabel(this);
    QLabel* time_since_boot = new QLabel(this);

    QLabel* cpu_amount = new QLabel(this);
    QLabel* cpu_vendor_id = new QLabel(this);
    QLabel* cpu_model_name = new QLabel(this);
    QLabel* last_level_cache_size = new QLabel(this);
    QLabel* cpu_bogomips = new QLabel(this);
    QLabel* cpu_usage = new QLabel(this);
    QLabel* cpu_bugs = new QLabel(this);

    QLabel* description_label = new QLabel(this);
    QLabel *headline_label = new QLabel(this);
    QLabel *cpu_utilization = new QLabel(this);

    QLabel* allocated_descriptors_label = new QLabel(this);
    QLabel* free_descriptors_label = new QLabel(this);
    QLabel* open_descriptors_limit = new QLabel(this);

    QLabel* ram_size_label = new QLabel(this);
    QLabel* available_ram_size_label = new QLabel(this);
    QLabel* cached_ram_size_label = new QLabel(this);
    QLabel* active_ram = new QLabel(this);
    QLabel* inactive_ram = new QLabel(this);
    QLabel* dirty_ram = new QLabel(this);

    void update_current_window() {
        if (headline_label->text().contains("Processes screen")) {
            init_all_window_items();
            init_processes_window();
        } else if (headline_label->text().contains("CPU screen")) {
            init_all_window_items();
            init_cpu_window();
        } else if (headline_label->text().contains("Filesystem screen")) {
            init_all_window_items();
            init_filesystem_window();
        } else if (headline_label->text().contains("Memory screen")) {
            init_all_window_items();
            init_memory_window();
        }
    }

    void init_welcome_window() {
        hide_all_items();
        headline_label->setText("Welcome");

        headline_label->setVisible(true);
        info_button->setVisible(true);

        explore_button->setVisible(true);
        quit_button->setVisible(true);
    }

    void init_cpu_window() {
        hide_all_items();
        headline_label->setText("Welcome to CPU screen");
        headline_label->setVisible(true);

        cpu_amount->setVisible(true);
        cpu_vendor_id->setVisible(true);
        cpu_model_name->setVisible(true);
        last_level_cache_size->setVisible(true);
        cpu_bogomips->setVisible(true);
        cpu_usage->setVisible(true);
        back_button->setVisible(true);
        cpu_bugs->setVisible(true);
        cpu_utilization->setVisible(true);
    }

    void init_info_window() {
        hide_all_items();
        headline_label->setText("Welcome to Info");
        headline_label->setVisible(true);

        back_button->setVisible(true);

        description_label->setText(description_text);
        description_label->setVisible(true);
    }

    void init_explore_window() {
        hide_all_items();

        headline_label->setText("Welcome to Explore screen");
        headline_label->setVisible(true);

        description_label->setText("Choose which component to explore: ");
        description_label->setVisible(true);

        back_button->setVisible(true);
        processes_button->setVisible(true);
        cpu_button->setVisible(true);
        filesystem_button->setVisible(true);
        memory_button->setVisible(true);
    }

    void init_processes_window() {
        hide_all_items();

        back_button->setVisible(true);

        headline_label->setText("Welcome to Processes screen");
        headline_label->setVisible(true);

        running_processes_label->setVisible(true);
        open_processes->setVisible(true);

        forks_since_boot->setVisible(true);
        time_since_boot->setVisible(true);
//        startWorkInAThread();
    }

    void init_filesystem_window() {
        hide_all_items();

        headline_label->setText("Welcome to Filesystem screen");
        headline_label->setVisible(true);

        back_button->setVisible(true);
        allocated_descriptors_label->setVisible(true);
        free_descriptors_label->setVisible(true);
        open_descriptors_limit->setVisible(true);
    }

    void init_memory_window() {
        hide_all_items();

        headline_label->setText("Welcome to Memory screen");
        headline_label->setVisible(true);

        back_button->setVisible(true);
        ram_size_label->setVisible(true);
        available_ram_size_label->setVisible(true);
        cached_ram_size_label->setVisible(true);
        active_ram->setVisible(true);
        inactive_ram->setVisible(true);
        dirty_ram->setVisible(true);
    }

    void prepare_ram_size_label() {
        std::string value = "Total RAM size: " + get_total_ram_size();

        QFont font = ram_size_label->font();
        font.setPointSize(26);

        ram_size_label->setFont(font);
        ram_size_label->setText(QString::fromStdString(value));

        ram_size_label->setFixedHeight(200);
        ram_size_label->move(100, 200);
        ram_size_label->setAlignment(Qt::AlignCenter);
    }

    void prepare_allocated_descriptors_label() {
        std::string value = "Total allocated descriptors number: " + std::to_string(get_total_allocated_descriptors());

        QFont font = allocated_descriptors_label->font();
        font.setPointSize(26);

        allocated_descriptors_label->setFont(font);

        allocated_descriptors_label->setFixedHeight(200);
        allocated_descriptors_label->move(100, 200);

        allocated_descriptors_label->setText(QString::fromStdString(value));
        allocated_descriptors_label->setAlignment(Qt::AlignCenter);
    }

    void prepare_free_descriptors_label() {
        std::string value = "Total free descriptors number:  " + std::to_string(get_total_free_descriptors());

        QFont font = free_descriptors_label->font();
        font.setPointSize(26);

        free_descriptors_label->setFont(font);
        free_descriptors_label->setText(QString::fromStdString(value));

        free_descriptors_label->setFixedHeight(200);
        free_descriptors_label->move(100, 250);
        free_descriptors_label->setAlignment(Qt::AlignCenter);
    }

    void prepare_running_processes() {
        std::string value = "Running processes number: " +
                            std::to_string(get_running_processes_amount());

        QFont font = running_processes_label->font();
        font.setPointSize(26);

        running_processes_label->setFont(font);
        running_processes_label->setText(QString::fromStdString(value));

        running_processes_label->setFixedHeight(200);
        running_processes_label->move(100, 400);
        running_processes_label->setAlignment(Qt::AlignCenter);
    }

    void prepare_back_button() {
        QFont font = back_button->font();

        font.setPointSize(36);
        font.setBold(true);

        back_button->setFont(font);
        back_button->move(200, 800);

        back_button->setFixedWidth(200);
        back_button->setFixedHeight(100);
    }

    void prepare_description() {
        description_label->setText(description_text);
        QFont font = description_label->font();
        font.setPointSize(36);

        description_label->setAlignment(Qt::AlignCenter);
        description_label->setFixedWidth(rec.width());

        description_label->move(0, 400);
        description_label->setFont(font);
        description_label->setWordWrap(true);
    }

    void prepare_window() {
        setWindowState(Qt::WindowMaximized);
        setWindowTitle(title);
    }

    void prepare_headline() {
        headline_label->setText(headline);
        headline_label->setFixedWidth(rec.width());

        QFont font = headline_label->font();
        font.setPointSize(72);
        font.setBold(true);

        headline_label->setFont(font);
        headline_label->setFixedHeight(200);
        headline_label->setAlignment(Qt::AlignCenter);
    }

    void prepare_info_button() {
        QFont font = headline_label->font();
        font.setPointSize(32);
        info_button->setFont(font);

        info_button->setFixedWidth(200);
        info_button->setFixedHeight(100);
        info_button->move(rec.width() / 2 - 100, rec.height() / 2 - 200);
    }

    void prepare_explore_button() {
        QFont font = explore_button->font();

        font.setBold(true);
        font.setPointSize(32);

        explore_button->setFixedWidth(200);
        explore_button->setFixedHeight(100);

        explore_button->setFont(font);
        explore_button->move(rec.width() / 2 - 100, rec.height() / 2 - 50);
    }

    void prepare_quit_button() {
        QFont font = quit_button->font();

        font.setBold(true);
        font.setPointSize(32);

        quit_button->setFixedWidth(200);
        quit_button->setFixedHeight(100);

        quit_button->setFont(font);
        quit_button->move(rec.width() / 2 - 100, rec.height() / 2 + 100);
    }

    void prepare_processes_button() {
        QFont font = processes_button->font();

        font.setPointSize(36);

        processes_button->setFont(font);
        processes_button->move(1200, 500);

        processes_button->setFixedSize(400, 50);
    }

    void prepare_cpu_button() {
        QFont font = cpu_button->font();
        font.setPointSize(36);

        cpu_button->setFont(font);
        cpu_button->move(1200, 600);

        cpu_button->setFixedSize(400, 50);
    }

    void prepare_filesystem_button() {
        QFont font = filesystem_button->font();
        font.setPointSize(36);

        filesystem_button->setFont(font);
        filesystem_button->move(1200, 700);

        filesystem_button->setFixedSize(400, 50);
    }

    void prepare_memory_button() {
        QFont font = memory_button->font();

        font.setPointSize(36);

        memory_button->setFont(font);
        memory_button->move(1200, 800);

        memory_button->setFixedSize(400, 50);
    }

    void prepare_cpu_bugs() {
        std::string value = "CPU bugs: \n\t" + get_cpu_bugs();

        QFont font = cpu_bugs->font();
        font.setPointSize(26);

        cpu_bugs->setFont(font);
        cpu_bugs->setText(QString::fromStdString(value));

        cpu_bugs->setFixedHeight(100);
        cpu_bugs->move(100, 175);
    }

    void prepare_available_ram_size() {
        std::string value = "Available RAM size: " + get_availible_ram();

        QFont font = available_ram_size_label->font();
        font.setPointSize(26);

        available_ram_size_label->setFont(font);
        available_ram_size_label->setText(QString::fromStdString(value));

        available_ram_size_label->setFixedHeight(200);
        available_ram_size_label->move(100, 250);
        available_ram_size_label->setAlignment(Qt::AlignCenter);
    }

    void hide_all_items() {
        explore_button->setVisible(false);
        headline_label->setVisible(false);
        info_button->setVisible(false);
        quit_button->setVisible(false);
        back_button->setVisible(false);
        description_label->setVisible(false);
        processes_button->setVisible(false);
        cpu_button->setVisible(false);
        filesystem_button->setVisible(false);
        memory_button->setVisible(false);
        running_processes_label->setVisible(false);
        open_processes->setVisible(false);
        forks_since_boot->setVisible(false);
        time_since_boot->setVisible(false);

        cpu_amount->setVisible(false);
        cpu_vendor_id->setVisible(false);
        cpu_model_name->setVisible(false);
        last_level_cache_size->setVisible(false);
        cpu_bogomips->setVisible(false);
        cpu_usage->setVisible(false);
        cpu_bugs->setVisible(false);
        cpu_utilization->setVisible(false);

        allocated_descriptors_label->setVisible(false);
        free_descriptors_label->setVisible(false);
        open_descriptors_limit->setVisible(false);

        ram_size_label->setVisible(false);
        available_ram_size_label->setVisible(false);
        cached_ram_size_label->setVisible(false);
        active_ram->setVisible(false);
        inactive_ram->setVisible(false);
        dirty_ram->setVisible(false);
    }

    void init_all_window_items() {
        prepare_window();
        prepare_headline();

        prepare_quit_button();
        prepare_info_button();

        prepare_back_button();
        prepare_explore_button();

        prepare_description();
        prepare_processes_button();
        prepare_cpu_button();
        prepare_filesystem_button();
        prepare_memory_button();
        prepare_running_processes();
        prepare_open_processes();
        prepare_forks_since_boot();
        prepare_time_since_boot();

        prepare_cpu_amount();
        prepare_cpu_vendor_id();
        prepare_cpu_model_name();
        prepare_last_level_cache_size();
        prepare_cpu_bogomips();
        prepare_cpu_bugs();
        prepare_cpu_utilization();
        prepare_cpu_usage();

        prepare_allocated_descriptors_label();
        prepare_free_descriptors_label();
        prepare_open_descriptors_limit();

        prepare_ram_size_label();
        prepare_available_ram_size();
        prepare_cached_ram_size();
        prepare_active_ram_size();
        prepare_inactive_ram_size();
        prepare_dirty_ram_size();
    }

    void prepare_cached_ram_size() {
        std::string value = "Cached RAM size:" + get_cached_ram();

        QFont font = cached_ram_size_label->font();
        font.setPointSize(26);

        cached_ram_size_label->setFont(font);
        cached_ram_size_label->setText(QString::fromStdString(value));

        cached_ram_size_label->setFixedHeight(200);
        cached_ram_size_label->move(100, 300);
        cached_ram_size_label->setAlignment(Qt::AlignCenter);
    }

    void prepare_active_ram_size() {
        std::string value = "Active RAM size:" + get_active_ram();

        QFont font = active_ram->font();
        font.setPointSize(26);

        active_ram->setFont(font);
        active_ram->setText(QString::fromStdString(value));

        active_ram->setFixedHeight(200);
        active_ram->move(100, 350);
        active_ram->setAlignment(Qt::AlignCenter);
    }

    void prepare_inactive_ram_size() {
        std::string value = "Inactive RAM size:" + get_inactive_ram();

        QFont font = inactive_ram->font();
        font.setPointSize(26);

        inactive_ram->setFont(font);
        inactive_ram->setText(QString::fromStdString(value));

        inactive_ram->setFixedHeight(200);
        inactive_ram->move(100, 400);
        inactive_ram->setAlignment(Qt::AlignCenter);
    }

    void prepare_dirty_ram_size() {
        std::string value = "Dirty RAM size:" + get_dirty_ram();

        QFont font = dirty_ram->font();
        font.setPointSize(26);

        dirty_ram->setFont(font);
        dirty_ram->setText(QString::fromStdString(value));

        dirty_ram->setFixedHeight(200);
        dirty_ram->move(100, 450);
        dirty_ram->setAlignment(Qt::AlignCenter);
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

    // Explore value adequacy
    void prepare_open_descriptors_limit() {
        std::string value = "Open descriptors limit: " + std::to_string(get_open_descriptors_limit());

        QFont font = open_descriptors_limit->font();
        font.setPointSize(26);

        open_descriptors_limit->setFont(font);
        open_descriptors_limit->setText(QString::fromStdString(value));

        open_descriptors_limit->setFixedHeight(200);
        open_descriptors_limit->move(100, 300);
        open_descriptors_limit->setAlignment(Qt::AlignCenter);
    }

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

    void prepare_cpu_utilization() {
        std::string value = "CPU utilization: ";

        for (auto item: get_cpu_utilization()) {
            value += item;
        }

        QFont font = cpu_utilization->font();
        font.setPointSize(26);

        cpu_utilization->setFont(font);
        cpu_utilization->setText(QString::fromStdString(value));

        cpu_utilization->setFixedHeight(200);
        cpu_utilization->move(600, 400);
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
        cpu_usage->move(100, 525);
    }

    void startWorkInAThread() {
        workerThread = new WorkerThread();
        connect(workerThread, SIGNAL(progressChanged(QString)), SLOT(onProgressChanged(QString)));
        // Setup callback for cleanup when it finishes
        connect(workerThread, SIGNAL(finished()),
                workerThread, SLOT(deleteLater()));
        // Run, Forest, run!
        workerThread->start(); // This invokes WorkerThread::run in a new thread
    }
};

#include "main.moc"

int main (int argc, char *argv[]) {
    using namespace QtCharts;

    QApplication app(argc, argv);
//    Screen window;
//
//    window.show();

    QLineSeries *series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    QMainWindow window;
    window.setCentralWidget(chartView);
    window.resize(400, 300);
    window.show();

    return app.exec();
}