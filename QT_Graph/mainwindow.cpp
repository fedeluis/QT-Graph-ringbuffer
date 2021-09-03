#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RingBuffer.hpp"

// salvo valori assi x ed y
int current_x=5;            // 5 secondi
int current_y=10;           // 10 microvolt

bool buffer_isfull=false;   // false default
unsigned int add_index=0;   // index where to add new data in buffer
unsigned int plot_index=0;  // index of data buffer to plot

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

    for(int i=0; i<this->channels; i++) {
        ui->plot->addGraph();
        ui->plot->graph(0)->setScatterStyle(QCPScatterStyle::ssNone);
        ui->plot->graph(0)->setLineStyle(QCPGraph::lsLine);
    }
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

void MainWindow::addPoint(double x, double* y) {
    // controllo se il buffer è pieno (lunghezza data buffer / # canali == campioni dati)
    if( (!buffer_isfull) && ( (this->data_x.size()/this->channels ) == this->samples)) {
        buffer_isfull=true;
        if(add_index == ((this->channels*this->samples)-1) )
            add_index=0;
    }
    // sostituisco i valori interni al buffer quando quest'ultimo è pieno
    if(buffer_isfull) {
        for(int i=0;i<this->channels;i++) {
            this->data_x[add_index]=x;
            this->data_y[add_index]=y[i];
            // non è necessario controllo dato che al massimo arriva a channels*samples-1
            add_index++;
        }
        if(add_index == ((this->channels*this->samples)-1) )
            add_index=0;
    }
    // inserisco coordinate nuovo vettore di punti negli assi su buffer non ancora pieno
    else {
        for(int i=0;i<this->channels;i++) {
            this->data_x.append(x);
            this->data_y.append(y[i]);
            add_index++;
        }
    }
    plot();
}

void MainWindow::plot() {

    // utilizzo quando cancello tutti i dati
    if(this->data_x.isEmpty() && this->data_y.isEmpty()) {
        for(int i=0;i<this->channels;i++)
            ui->plot->graph(i)->setData(this->data_x,this->data_y);
    }
    // inserisco nuovi punti in grafico
    else {
        for(int i=0;i<this->channels;i++) {
            ui->plot->graph(i)->addData(this->data_x[plot_index],this->data_y[plot_index]);
            plot_index++;
        }
        if(plot_index == ((this->channels*this->samples)-1) )
            plot_index=0;
    }
    // aggiorno grafico
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::clearData() {
    data_x.clear();
    data_y.clear();
    plot_index=0;
    buffer_isfull=false;
}

void MainWindow::on_btn_rescale_clicked() {
    bool axis_update=false;

    // aggiornamento asse x
    if(ui->spin_x_axis->value()!=current_x) {
        current_x=ui->spin_x_axis->value();
        axis_update=true;
    }
    // aggiornamento asse y
    if(ui->spin_y_axis->value()!=current_y) {
        current_y=ui->spin_y_axis->value();
        axis_update=true;
    }
    // se ho cambiato qualcosa, aggiorno il range
    if(axis_update) {
        ui->plot->xAxis->setRange(0,current_x);
        ui->plot->yAxis->setRange(-current_y,current_y);
    }
    // aggiorno grafico
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::setChannels(int n) {
    this->channels = n;
}


void MainWindow::setSamples(int n) {
    this->samples = n;
}
