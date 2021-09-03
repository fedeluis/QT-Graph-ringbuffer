#include "mainwindow.h"
#include "RingBuffer.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    rbuf::RingBuffer buffer(100,4);
    MainWindow w;
    //per passare vettore di punti in fase di inserimento
    double foo[buffer.getChannels()];
    w.show();
    w.setChannels(0);
    // aggiungo punti da w.data_x;
    return a.exec();
}
