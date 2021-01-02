//
// Created by vlad on 29.12.20.
//

#ifndef SOLO_SCREEN_H
#define SOLO_SCREEN_H

#include "proc_analysis.h"
#include "database_manipulation.h"

class WorkerThread : public QThread {
Q_OBJECT

    void run() {
        while(1) {
            sleep(1);

            update_cpu_table();
            update_files_table();
            update_memory_table();
            update_processes_table();

            emit progressChanged("Update message");
        }
    }
    // Define signal:
signals:
    void progressChanged(QString info);
};

class Screen : public QWidget {
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

        connect(cpu_utilization_label, SIGNAL(clicked()), this, SLOT(createCpuUtilizationGraph()));
        connect(running_processes_label, SIGNAL(clicked()), this, SLOT(createRunningProcessesGraph()));
        connect(open_processes_label, SIGNAL(clicked()), this, SLOT(createOpenProcessesGraph()));

        connect(forks_since_boot_label, SIGNAL(clicked()), this, SLOT(createForksSinceBoot()));
        connect(time_since_boot_label, SIGNAL(clicked()), this, SLOT(createTimeSinceBoot()));

        connect(allocated_descriptors_label, SIGNAL(clicked()), this, SLOT(createAllocatedDescriptors()));
        connect(free_descriptors_label, SIGNAL(clicked()), this, SLOT(createFreeDescriptors()));

        connect(active_ram, SIGNAL(clicked()), this, SLOT(createActiveRamSize()));connect(active_ram, SIGNAL(clicked()), this, SLOT(createActiveRamSize()));
        connect(available_ram_size_label, SIGNAL(clicked()), this, SLOT(createAvailibleRamSize()));
        connect(cached_ram_size_label, SIGNAL(clicked()), this, SLOT(createCachedRamSize()));
        connect(inactive_ram, SIGNAL(clicked()), this, SLOT(createInactiveRamSize()));
        connect(dirty_ram, SIGNAL(clicked()), this, SLOT(createDirtyRamSize()));

        connect(cpu_usage_label, SIGNAL(clicked()), this, SLOT(createCPUusageGraph()));

        connect(remove_graph_button, SIGNAL(clicked()), this, SLOT(OnRemoveGraph()));

        connect(clear_database_button, SIGNAL(clicked()), this, SLOT(clear_database_and_quit()));
        connect(no_clear_database_button, SIGNAL(clicked()), this, SLOT(quit()));

        initialize_database_and_tables();
        startWorkInAThread();
    }

    ~Screen(){}

private slots:
//    These are listeners for different buttons clicks and are defined in 'Screen_listeners.h' file.
    void OnInfo();
    void OnQuit();

    void OnBack();
    void OnExplore();

    void OnProcesses();
    void OnCPU();

    void OnFilesystem();
    void OnMemory();

    void createCpuUtilizationGraph();
    void createRunningProcessesGraph();

    void OnRemoveGraph();
    void createOpenProcessesGraph();

    void createForksSinceBoot();
    void createTimeSinceBoot();

    void createAllocatedDescriptors();
    void createFreeDescriptors();

    void createAvailibleRamSize();
    void createCachedRamSize();
    void createActiveRamSize();
    void createInactiveRamSize();
    void createDirtyRamSize();

    void createCPUusageGraph();

    void clear_database_and_quit();
    void quit();

    void onProgressChanged(QString info) {
        update_current_window();
    }
private:
    bool grapghIsUsed = false;

//  Text and other constants to be used later
    WorkerThread *workerThread;
    QRect rec = QApplication::desktop()->screenGeometry();

    std::string graph_title = "";
    std::string table_name = "";
    std::string column_name = "";

    QString title = "GUI STATS";
    QString description_text = "This program is designed to present the user information\n"
                               "about system, using /proc information. Using the program,\n you can get info on:"
                               "\n\n -CPU \n -Processes \n -Files \n -Memory ";

//  General purpose labels
    QLabel* headline_label = new QLabel(this);
    QLabel* description_label = new QLabel(this);

//  Buttons to be used in the application
    QPushButton* info_button = new QPushButton("Info", this);
    QPushButton* quit_button = new QPushButton("Quit", this);
    QPushButton* back_button = new QPushButton("Back", this);
    QPushButton* cpu_button = new QPushButton("CPU stats", this);
    QPushButton* explore_button = new QPushButton("Explore", this);
    QPushButton* memory_button = new QPushButton("Memory stats", this);
    QPushButton* processes_button = new QPushButton("Processes stats", this);
    QPushButton* remove_graph_button = new QPushButton("Remove graph", this);
    QPushButton* filesystem_button = new QPushButton("Filesystem stats", this);

//  Labels needed for 'Processes' screen
    QPushButton* open_processes_label = new QPushButton(this);
    QPushButton* time_since_boot_label = new QPushButton(this);
    QPushButton* forks_since_boot_label = new QPushButton(this);
    QPushButton* running_processes_label = new QPushButton(this);

//  Labels needed for 'CPU' screen
    QLabel* cpu_bugs_label = new QLabel(this);
    QPushButton* cpu_usage_label = new QPushButton(this);
    QLabel* cpu_amount_label = new QLabel(this);
    QLabel* cpu_bogomips_label = new QLabel(this);
    QLabel* cpu_vendor_id_label = new QLabel(this);
    QLabel* cpu_model_name_label = new QLabel(this);
    QPushButton* cpu_utilization_label = new QPushButton(this);
    QLabel* last_level_cache_size_label = new QLabel(this);

//  Labels needed for 'Filesystem' screen
    QLabel* open_descriptors_limit = new QLabel(this);
    QPushButton* free_descriptors_label = new QPushButton(this);
    QPushButton* allocated_descriptors_label = new QPushButton(this);

//  Labels needed for 'Memory' screen
    QPushButton* dirty_ram = new QPushButton(this);
    QPushButton* active_ram = new QPushButton(this);
    QPushButton* inactive_ram = new QPushButton(this);
    QLabel* ram_size_label = new QLabel(this);
    QPushButton* cached_ram_size_label = new QPushButton(this);
    QPushButton* available_ram_size_label = new QPushButton(this);

    QtCharts::QChart *chart = new QtCharts::QChart();
    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart, this);

    QPushButton* clear_database_button = new QPushButton("Yes", this);
    QPushButton* no_clear_database_button = new QPushButton("No", this);

    //  Functions responsible for windows initializing, are defined in "Screen_inits.h" file
    void init_welcome_window();
    void init_cpu_window();

    void init_info_window();
    void init_explore_window();

    void init_processes_window();
    void init_filesystem_window();

    void init_memory_window();
    void init_all_window_items();

    void init_post_quit_window();

//  Functions, responsible for initializing separate ui items (labels, buttons etc). Defined in "Screen_preparations.h"
    void prepare_ram_size_label();
    void prepare_allocated_descriptors_label();

    void prepare_free_descriptors_label();
    void prepare_running_processes_label();

    void prepare_back_button();
    void prepare_description();

    void prepare_window();
    void prepare_headline();

    void prepare_info_button();
    void prepare_explore_button();

    void prepare_quit_button();
    void prepare_processes_button();

    void prepare_cpu_button();
    void prepare_filesystem_button();

    void prepare_memory_button();
    void prepare_cpu_bugs();

    void prepare_cached_ram_size();
    void prepare_available_ram_size();

    void prepare_active_ram_size();
    void prepare_inactive_ram_size();

    void prepare_dirty_ram_size();
    void prepare_time_since_boot();

    void prepare_open_descriptors_limit();
    void prepare_open_processes();

    void prepare_forks_since_boot();
    void prepare_cpu_amount();

    void prepare_cpu_vendor_id();
    void prepare_cpu_model_name();

    void prepare_last_level_cache_size();
    void prepare_cpu_bogomips();

    void prepare_cpu_utilization();
    void prepare_cpu_usage();

    void prepare_remove_graph_button();
    void prepare_chartview();

    void prepare_yes_no_clear_buttons();

//  Methods for manipulations with screens, defined in "Screen_manipulations.h"
    void hide_all_items();
    void startWorkInAThread();
    void update_current_window();
    void createGraph(std::string title, std::string table_name, std::string column_name);
};

#include "main.moc"
#endif //SOLO_SCREEN_H
