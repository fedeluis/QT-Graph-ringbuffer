#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_btn_plot_clicked() {
    plot();
}

void MainWindow::on_btn_clear_clicked() {
    clearData();
    plot();
}

void MainWindow::addPoint(double x, double y) {
    // inserisco coordinate nuovo punto nei vettori
    x_ax.append(x);
    y_ax.append(y);
}
void MainWindow::plot() {
    // inserisco nuovi punti in grafico
    ui->plot->graph(0)->setData(x_ax, y_ax);
    // aggiorno grafico
    ui->plot->replot();
    ui->plot->update();
}
void MainWindow::clearData() {
    x_ax.clear();
    y_ax.clear();
}
