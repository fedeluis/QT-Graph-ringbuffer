#include "mainwindow.h"
#include "RingBuffer.hpp"
#include <QApplication>
#include <stdlib.h> // rand
#include "unistd.h"

int channels = 2;
int samples = 24;
double freq = 2;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rbuf::RingBuffer buffer(samples,channels);
    MainWindow w;

    // setup del grafico
    w.setChannels(buffer.getChannels());
    w.setSamples(buffer.getSamples());
    w.graphSetup();
    w.show();

    // inserimento dati in RingBuffer
    Eigen::MatrixXd data_input(buffer.getChannels(),1);
    for(int i=0; i<samples; i++) {
        for(int j=0; j<channels; j++) {
            data_input(j,0) = (rand() % 30) - 15;
        }
        buffer.add(data_input);
    }

    double x_axis=0;
    // plotting dati
    for(int i=0; i<samples; i++) {

        buffer.get(data_input);

        //sleep(1000);
        //std::cout << data_input.data();
        w.plot(x_axis,data_input.data());
        x_axis+=1/freq;

    }

    return a.exec();
}
