#include "mainwindow.h"
#include "ui_mainwindow.h"

// salvo valori assi xx ed y
int current_x=5; // 5 secondi
int current_y=10; // 50 microvolt

int numero=3;


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);
/*  TENTATIVO GRAFICO MULTIPLO
 *  NON FUNZIONANTE
    ui->plot->plotLayout()->clear();

    QCPAxisRect *wideAxisRect[numero];
    QCPGraph *graf[numero];

    for(int i=0;i<numero;i++) {
        wideAxisRect[i]= new QCPAxisRect(ui->plot);
        wideAxisRect[i]->setupFullAxesBox(true);


        QCPAxis *x = new QCPAxis(wideAxisRect[i],QCPAxis::atBottom);
        x->setRange(0,current_x);
        QCPAxis *y = new QCPAxis(wideAxisRect[i],QCPAxis::atBottom);
        y->setRange(-current_y,current_y);

        ui->plot->plotLayout()->addElement(i, 0, wideAxisRect[i]);
        graf[i] = ui->plot->addGraph(x, y);
        graf[i]->keyAxis()->setRange(0,current_x);
        graf[i]->valueAxis()->setRange(-current_y,current_y);
        // richiamo rescale
        //on_btn_rescale_clicked();
    }

    QCPLayoutGrid *gridLayout = new QCPLayoutGrid; // contenitore per subgraphs
*/







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
    data_x.append(x);
    data_y.append(y);
}
void MainWindow::plot() {
    // inserisco nuovi punti in grafico
    ui->plot->graph(0)->setData(data_x, data_y);
    // aggiorno grafico
    ui->plot->replot();
    ui->plot->update();
}
void MainWindow::clearData() {
    data_x.clear();
    data_y.clear();
}

void MainWindow::on_btn_rescale_clicked() {
    bool axis_update=false;
    // aggiornamento assi
    if(ui->spin_x_axis->value()!=current_x) {
        current_x=ui->spin_x_axis->value();
        axis_update=true;
    }
    if(ui->spin_y_axis->value()!=current_y) {
        current_y=ui->spin_y_axis->value();
        axis_update=true;
    }
    if(axis_update) {
        for(int i=0;i<3;i++) {
            //QCPAxis *x = new QCPAxis(wideAxisRect[i],QCPAxis::atBottom);
            //x->setRange(0,current_x);
            //QCPAxis *y = new QCPAxis(wideAxisRect[i],QCPAxis::atBottom);
            //y->setRange(-current_y,current_y);

            //ui->plot->graph(i)->setKeyAxis(x);
            //ui->plot->graph(i)->setValueAxis(y);
        }
        //ui->plot->xAxis->setRange(0,current_x);
        //ui->plot->yAxis->setRange(-current_y,current_y);
    }

    ui->plot->xAxis->setRange(0,current_x);
    ui->plot->yAxis->setRange(-current_y,current_y);
    // aggiorno grafico
    ui->plot->replot();
    ui->plot->update();
}
