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

// Do not remove 'unused' includes!
#include "Screen.h"
#include "Screen_inits.h"
#include "Screen_listeners.h"
#include "Screen_preparations.h"
#include "Screen_graphs_maker.h"
#include "Screen_manipulations.h"

#include "proc_analysis.h"
#include "database_manipulation.h"

int main (int argc, char *argv[]) {
//    using namespace QtCharts;
//    auto b = create_table(a, "SAMPLE", "(contact_id INTEGER)");
//
//    initialize_database_and_tables();
//    update_processes_table();
//
//    auto a = open_database();
//
//    clear_all_tables();
//    insert_in_table(a, "processes", "(running_processes, blocked_processes, open_processes, forks_since_boot, time_since_boot) VALUES ('2', '3', '4', '5', '6')");
//    insert_in_table(a, "processes", "(running_processes, blocked_processes, open_processes, forks_since_boot, time_since_boot) VALUES ('3', '4', '5', '6', '7')");
//    update_processes_table();
//
//    auto s = select_from_database(a, 0, "SELECT running_processes from processes ");
//    close_database(a);
//
//    std::cout << "Size of s: " << s.size() << "\n";
//
//    for (auto x: s) {
//        std::cout << x << "\n";
//    }
//    return 0;

    QApplication app(argc, argv);
    Screen window;
    window.show();

//    QtCharts::QLineSeries *series = new QtCharts::QLineSeries();
//    series->append(0, 6);
//    series->append(2, 4);
//    series->append(3, 8);
//    series->append(7, 4);
//    series->append(10, 5);
//
//    series->clear();
//
//    series->append(0, 10);
//    series->append(2, 10);
//    series->append(3, 10);
//    series->append(7, 10);
//    series->append(10, 10);

//    QtCharts::QChart *chart = new QtCharts::QChart();
//    chart->legend()->hide();
//    chart->addSeries(series);
//    chart->createDefaultAxes();
//    chart->setTitle("Simple line chart example");

//    QtCharts::QChartView *chartView = new QtCharts::QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);
//    chartView->setFixedSize(400, 400);
//
//    QMainWindow window;
//    window.showMaximized();
//    window.setCentralWidget(chartView);
//    window.show();

    return app.exec();
}