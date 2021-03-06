#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <stdlib.h> // rand
#include "unistd.h" // usleep

// salvo valori assi x ed y
double current_x=10;   // 10 secondi
int current_graph_spacer=15;

bool buffer_isfull=false;   // false default
bool cache_buffer_isfull=false;
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
    // first item in combo box
    ui->combo_graph->addItem("All");

    for(int i=0; i<this->channels; i++) {
        ui->plot->addGraph();
        ui->plot->graph(i)->setScatterStyle(QCPScatterStyle::ssNone);
        ui->plot->graph(i)->setLineStyle(QCPGraph::lsLine);

        color.setNamedColor(ColorValues[i%56]);
        pen.setColor(color);
        ui->plot->graph(i)->setPen(pen);

        // salvo posizioni asse y in (# channels) vettori
        QVector<double> data;
        this->_list.append(data);

        // lista con tutti i dati #alldata
        QVector<double> all_data;
        this->_cache_list.append(all_data);


        // adding items in combo box
        QString str = "Channel ";
        str.append(QString::number(i+1));
        ui->combo_graph->addItem(str);
    }
    // salvo posizioni asse x in unico vettore
    QVector<double> data_x;
    this->_list.append(data_x);

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
    ui->plot->yAxis->setRange(0,2*current_graph_spacer*this->channels);

    // vertical line
    ui->plot->graph(this->channels)->addData(vertline_index,2*current_graph_spacer*this->channels);
    ui->plot->graph(this->channels)->addData(vertline_index,0);
}


void MainWindow::on_btn_clear_clicked() {
    plot(-1,NULL);
}

void MainWindow::plot(double x, double* y) {

    // clearData() case
    if(x==-1 && y==NULL) {
        for(int i=0; i<=this->channels; i++) {
            this->_list[i].clear();
        }

        // #alldata
        for(int i=0; i<this->channels; i++) {
            this->_cache_list[i].clear();
        }

        for(int i=0;i<=this->channels; i++) {
            ui->plot->graph(i)->data()->clear();
        }

        vertline_index=0;
        ui->plot->graph(this->channels)->addData(vertline_index,2*current_graph_spacer*this->channels);
        ui->plot->graph(this->channels)->addData(vertline_index,0);
    }
    // adding new points
    else {

        // check if buffer is full
        if( (!buffer_isfull) && (x>current_x) ) {
            buffer_isfull=true;
        }
        if( (!cache_buffer_isfull) && (this->_cache_list[0].size()>=(this->frequency*10)) ) {
            cache_buffer_isfull=true;
        }
        // update x axis for the plot (if it's out of bound)
        while(x>=current_x) {
            x = x-current_x;
        }
        // full buffer case
        if(buffer_isfull) {
            for(int i=0;i<=this->channels;i++) {

                if(i!=this->channels) {
                    this->cacheAdd(i,this->_list[i].takeFirst());
                    //this->_cache_list[i].append(this->_list[i].takeFirst());
                }
                else {
                    this->_list[i].removeFirst();
                }
            }
        }
        // standard case
        this->_list[this->channels].append(x);
        for(int i=0;i<this->channels;i++) {
            this->_list[i].append(y[i]+current_graph_spacer+i*2*current_graph_spacer);

            ui->plot->graph(i)->setData(this->_list[this->channels],this->_list[i]);
        }

        // vertical line update
        vertline_index=x;
        ui->plot->graph(this->channels)->data()->clear();
        ui->plot->graph(this->channels)->addData(vertline_index,2*current_graph_spacer*this->channels);
        ui->plot->graph(this->channels)->addData(vertline_index,0);
    }

    ui->plot->replot();
    //ui->plot->update();
}

void MainWindow::on_btn_rescale_clicked() {
    bool axis_update=false;
    double previous_x=current_x;
    int previous_graph_spacer=current_graph_spacer;

    // aggiornamento asse x
    if(ui->spin_x_axis->value()!=current_x) {
        current_x=ui->spin_x_axis->value();
        axis_update=true;
    }
    // aggiornamento asse y
    if(ui->spin_y_axis->value()!=current_graph_spacer) {
        current_graph_spacer=ui->spin_y_axis->value();
        axis_update=true;
    }
    // se ho cambiato qualcosa, aggiorno il range
    if(axis_update) {
        ui->plot->xAxis->setRange(0,current_x);
        ui->plot->yAxis->setRange(0,current_graph_spacer*2*this->channels);

        // (I) caso in cui allargo l'ascisse
        if(current_x>previous_x) {
            // #alldata

            double time_gap = current_x-previous_x;
            // aggiorno l'asse x
            for(int i=0; i<this->_list[this->channels].size(); i++) {
                this->_list[this->channels][i] = this->_list[this->channels].value(i)+time_gap;
            }
            // aggiungo nuovi punti
            for(double i=(1/this->frequency); i<=time_gap; i+=(1/this->frequency) ) {
                this->_list[this->channels].prepend(time_gap-i);
                for(int j=0; j<this->channels; j++) {
                    this->_list[j].prepend(this->_cache_list[j].takeLast());
                }
            }
            cache_buffer_isfull=false;
        }
        // (II) caso in cui restringo il range, ma i dati ci stanno nel nuovo range e buffer non ?? pieno
        else if(!buffer_isfull && (vertline_index<current_x) ) { }
        // (III) caso in cui non modifico l'asse x
        else if(current_x==previous_x) { }
        // (IV) caso in cui restringo il range e devo scartare dati (dati da salvare in linea)
        else if(vertline_index>=current_x) {
            // elimino dati non compresi nell'intervallo [vertline_index,vertline_index-current_x]
            while( (this->_list[this->channels].first()>=vertline_index) || (this->_list[this->channels].first()<vertline_index-current_x) ) {
                for(int i=0; i<=this->channels; i++) {
                    if(i!=this->channels) {
                        this->cacheAdd(i,this->_list[i].takeFirst());
                    }
                    else {
                        this->_list[i].removeFirst();
                    }
                }
            }
            // aggiorno asse x dei rimanenti dati
            for(int i=0; i<this->_list[this->channels].size(); i++) {
                this->_list[this->channels][i] = this->_list[this->channels].value(i)-(vertline_index-current_x);
            }
            // aggiorno vertline
            vertline_index=0;
        }
        // (V) caso in cui i dati da salvare sono spezzati
        else if(buffer_isfull && (vertline_index<current_x) ) {
            // elimino dati compresi nell'intervallo [vertline_index,previous_x-(current_x-vertline_index)]
            while( this->_list[this->channels].first()<previous_x-(current_x-vertline_index) ) {
                for(int i=0; i<=this->channels; i++) {
                    if(i!=this->channels) {
                        this->cacheAdd(i,this->_list[i].takeFirst());
                    }
                    else {
                        this->_list[i].removeFirst();
                    }
                }
            }
            // aggiorno asse x dei rimanenti dati
            for(int i=0; i<this->_list[this->channels].size(); i++) {
                this->_list[this->channels][i] = this->_list[this->channels].value(i)+(current_x-vertline_index);

                if(this->_list[this->channels].value(i)>=previous_x) {
                    this->_list[this->channels][i] = this->_list[this->channels].value(i)-previous_x;
                }
            }
            // aggiorno vertline
            vertline_index=0;
        }

        // graph update
        for(int i=0;i<this->channels;i++) {
            ui->plot->graph(i)->data()->clear();

            int _list_size=this->_list[i].size();
            for(int j=0; j<_list_size && (previous_graph_spacer!=current_graph_spacer); j++) {
                this->_list[i][j]=this->_list[i][j]-previous_graph_spacer-i*2*previous_graph_spacer+current_graph_spacer+i*2*current_graph_spacer;
            }
            ui->plot->graph(i)->setData(this->_list[this->channels],this->_list[i]);
        }
        // vertical line update
        ui->plot->graph(this->channels)->data()->clear();
        ui->plot->graph(this->channels)->addData(vertline_index,2*current_graph_spacer*this->channels);
        ui->plot->graph(this->channels)->addData(vertline_index,0);
    }
    // graph update
    ui->plot->replot();
    //ui->plot->update();
}

void MainWindow::on_btn_graph_clicked() {
    if(ui->combo_graph->currentIndex()==0) {
        for(int i=0; i<this->channels; i++) {
            ui->plot->graph(i)->setVisible(true);
        }
    }
    else {
        for(int i=0; i<this->channels; i++) {
            if(i==ui->combo_graph->currentIndex()-1) {
                ui->plot->graph(i)->setVisible(true);
            }
            else {
                ui->plot->graph(i)->setVisible(false);
            }
        }
    }
    // aggiorno grafico
    ui->plot->replot();
    //ui->plot->update();
}

void MainWindow::setChannels(int c) {
    this->channels = c;
}


void MainWindow::setSamples(int s) {
    this->samples = s;
}

void MainWindow::setFrequency(double f) {
    this->frequency = f;
}

void MainWindow::cacheAdd(int i, double s) {
    if(cache_buffer_isfull) {
        this->_cache_list[i].append(s);
        this->_cache_list[i].removeFirst();
    }
    else {
        this->_cache_list[i].append(s);
    }
}

void MainWindow::on_btn_plot_clicked() {

    rbuf::RingBuffer _buffer(this->samples,this->channels);

    // inserimento dati in RingBuffer
    Eigen::MatrixXd data_input(this->channels,1);
    for(int i=0; i<this->samples; i++) {
        for(int j=0; j<this->channels; j++) {
            data_input(j,0) = (rand() % 30) - 15;
        }
        _buffer.add(data_input);
    }

    double x_axis=0;
    // plotting dati
    for(int i=0; i<this->samples; i++) {

        _buffer.get(data_input);

        usleep(250000);

        this->plot(x_axis,data_input.data());
        x_axis+=1/this->frequency;

    }
}
