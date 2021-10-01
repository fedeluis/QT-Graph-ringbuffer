#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "RingBuffer.hpp"
#include <stdlib.h> // rand

// salvo valori assi x ed y
double current_x=10;   // 10 secondi
int current_y=20;   // 20 microvolt

bool buffer_isfull=false;   // false default
double vertline_index=0;    //index for vertical line

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {

    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::graphSetup() {

    // serve per colorare diversamente i grafici
    QPen pen;
    QColor color;
    static QVector<QString> ColorValues = {
            "#FF0000", "#00FF00", "#0000FF", "#FFFF00", "#FF00FF", "#00FFFF", "#000000",
            "#800000", "#008000", "#000080", "#808000", "#800080", "#008080", "#808080",
            "#C00000", "#00C000", "#0000C0", "#C0C000", "#C000C0", "#00C0C0", "#C0C0C0",
            "#400000", "#004000", "#000040", "#404000", "#400040", "#004040", "#404040",
            "#200000", "#002000", "#000020", "#202000", "#200020", "#002020", "#202020",
            "#600000", "#006000", "#000060", "#606000", "#600060", "#006060", "#606060",
            "#A00000", "#00A000", "#0000A0", "#A0A000", "#A000A0", "#00A0A0", "#A0A0A0",
            "#E00000", "#00E000", "#0000E0", "#E0E000", "#E000E0", "#00E0E0", "#E0E0E0",
        };

    for(int i=0; i<this->channels; i++) {
        ui->plot->addGraph();
        ui->plot->graph(i)->setScatterStyle(QCPScatterStyle::ssNone);
        ui->plot->graph(i)->setLineStyle(QCPGraph::lsLine);

        color.setNamedColor(ColorValues[i%56]);
        pen.setColor(color);
        ui->plot->graph(i)->setPen(pen);

        // salvo posizioni asse y in (# channels) vettori
        QVector<double> data;
        this->list.append(data);

        // adding items in combo box
        QString str = "Channel ";
        str.append(QString::number(i+1));
        ui->combo_graph->addItem(str);
    }
    // salvo posizioni asse x in unico vettore
    QVector<double> data_x;
    this->list.append(data_x);

    // final item in combo box
    ui->combo_graph->addItem("All");

    // vertical line for updating
    ui->plot->addGraph();
    ui->plot->graph(this->channels)->setScatterStyle(QCPScatterStyle::ssNone);
    ui->plot->graph(this->channels)->setLineStyle(QCPGraph::lsLine);
    color.setNamedColor("#000000");
    pen.setColor(color);
    ui->plot->graph(this->channels)->setPen(pen);

    ui->plot->xAxis->setLabel("time");
    ui->plot->yAxis->setLabel("EEG signal");
    ui->plot->xAxis->setRange(0,current_x);
    ui->plot->yAxis->setRange(-current_y,current_y);

    // vertical line
    ui->plot->graph(this->channels)->addData(vertline_index,current_y);
    ui->plot->graph(this->channels)->addData(vertline_index,-current_y);
}


void MainWindow::on_btn_clear_clicked() {
    plot(-1,NULL);
}

void MainWindow::plot(double x, double* y) {

    // clearData() case
    if(x==-1 && y==NULL) {
        for(int i=0; i<=this->channels; i++) {
            this->list[i].clear();
        }

        for(int i=0;i<=this->channels; i++) {
            ui->plot->graph(i)->data()->clear();
        }

        vertline_index=0;
        ui->plot->graph(this->channels)->addData(vertline_index,current_y);
        ui->plot->graph(this->channels)->addData(vertline_index,-current_y);
    }
    // adding new points
    else {

        // check if buffer is full
        if( (!buffer_isfull) && (x>current_x) ) {
            buffer_isfull=true;
        }
        // update x axis for the plot (if it's out of bound)
        while(x>=current_x) {
            x = x-current_x;
        }
        // full buffer case
        if(buffer_isfull) {
            for(int i=0;i<=this->channels;i++) {
                this->list[i].removeFirst();
            }
        }
        // standard case
        this->list[this->channels].append(x);
        for(int i=0;i<this->channels;i++) {
            this->list[i].append(y[i]);
            ui->plot->graph(i)->setData(this->list[this->channels],this->list[i]);
        }

        // vertical line update
        vertline_index=x;
        ui->plot->graph(this->channels)->data()->clear();
        ui->plot->graph(this->channels)->addData(vertline_index,current_y);
        ui->plot->graph(this->channels)->addData(vertline_index,-current_y);
    }

    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::on_btn_rescale_clicked() {
    bool axis_update=false;
    double previous_x=current_x;

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

        // caso in cui allargo l'ascisse
        if(current_x>previous_x) { }
        // caso in cui current_x si trovi alla destra di vertline con i dati tutti in linea
        else if(vertline_index+current_x<=previous_x) {
            // elimino dati non compresi nell'intervallo [vertline_index,current_x]
            while((this->list[this->channels].last()>=current_x+vertline_index) || (this->list[this->channels].last()<=vertline_index)) {
                for(int i=0; i<=this->channels; i++) {
                    this->list[i].pop_back();
                }
            }
            // aggiorno asse x dei rimanenti dati
            for(int i=0; i<this->list[this->channels].size(); i++) {
                this->list[this->channels][i] = this->list[this->channels].value(i)-vertline_index;
            }
            // aggiorno posizione verline
            vertline_index=0;
        }
        // nel caso in cui vertline si trovi a destra di current_x ed i dati son divisi
        else if(vertline_index+current_x>previous_x) {
            // elimino dati compresi nell'intervallo [current_x,vertline_index]
            while(this->list[this->channels].last()>=(vertline_index+current_x-previous_x) ) {
                for(int i=0; i<=this->channels; i++) {
                    this->list[i].pop_back();
                }
            }
            //aggiorno asse x dei rimanenti
            for(int i=0; i<this->list[this->channels].size(); i++) {
                double tmp = this->list[this->channels].value(i) - vertline_index;
                if(tmp>=0) {
                    this->list[this->channels][i] = tmp;
                }
                else {
                    tmp+=previous_x;
                    this->list[this->channels][i] = tmp;
                }
            }
            // aggiorno posizione verline
            vertline_index=0;

        }
        // graph update
        for(int i=0;i<this->channels;i++) {
            ui->plot->graph(i)->data().clear();
            ui->plot->graph(i)->setData(this->list[this->channels],this->list[i]);
        }
        // vertical line update
        ui->plot->graph(this->channels)->data()->clear();
        ui->plot->graph(this->channels)->addData(vertline_index,current_y);
        ui->plot->graph(this->channels)->addData(vertline_index,-current_y);
    }
    // graph update
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::on_btn_graph_clicked() {
    if(ui->combo_graph->currentIndex()==this->channels) {
        for(int i=0; i<this->channels; i++) {
            ui->plot->graph(i)->setVisible(true);
        }
    }
    else {
        for(int i=0; i<this->channels; i++) {
            if(i==ui->combo_graph->currentIndex()) {
                ui->plot->graph(i)->setVisible(true);
            }
            else {
                ui->plot->graph(i)->setVisible(false);
            }
        }
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
