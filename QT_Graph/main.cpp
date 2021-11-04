#include "mainwindow.h"
#include "RingBuffer.hpp"
#include <QApplication>
#include <stdlib.h> // rand
#include "unistd.h"

int channels = 64;
int samples = 74;
double freq = 4;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rbuf::RingBuffer buffer(samples,channels);
    MainWindow w;

    // setup del grafico
    w.setChannels(buffer.getChannels());
    w.setSamples(buffer.getSamples());
    w.setFrequency(freq);
    w.graphSetup();
    w.show();



    return a.exec();
}
