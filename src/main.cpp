#include <thread>
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

// Do not remove 'unused' includes!
#include "Screen.h"
#include "Screen_inits.h"
#include "Screen_listeners.h"
#include "Screen_preparations.h"
#include "Screen_graphs_maker.h"
#include "Screen_manipulations.h"

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);
    Screen window;
    window.show();
    return app.exec();
}