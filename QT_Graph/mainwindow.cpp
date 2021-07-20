#include "mainwindow.h"
#include "ui_mainwindow.h"

// salvo valori assi xx ed y
int current_x=5; // 5 secondi
int current_y=50; // 50 microvolt

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);

    /*
     * Grafico
     */
    ui->plot->addGraph();
    ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->plot->xAxis->setRange(0,current_x);
    ui->plot->yAxis->setRange(-current_y,current_y);
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
    // aggiornamento assi
    if(ui->spin_x_axis->value()!=current_x)
        current_x=ui->spin_x_axis->value();
    if(ui->spin_y_axis->value()!=current_y)
        current_y=ui->spin_y_axis->value();
    ui->plot->xAxis->setRange(0,current_x);
    ui->plot->yAxis->setRange(-current_y,current_y);

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
