#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <eigen3/Eigen/Dense>
#include "RingBuffer.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    /*! \brief  Updates graph with new points
     *  \param  x   Coordinate for X-axis
     *  \param  y   Coordinate for Y-axis
     */
    void plot(double x, double *y);

    /*! \brief  Set number of channels
     *  \param  c   number of channels
     */
    void setChannels(int c);

    /*! \brief  Set number of samples
     *  \param  s   number of samples
     */
    void setSamples(int s);

    /*! \brief  Set frequency
     *  \param  f   frequency
     */
    void setFrequency(double f);

    /*! \brief  Set up of graph's parameters
     */
    void graphSetup();

private slots:

    void on_btn_clear_clicked();

    void on_btn_rescale_clicked();

    void on_btn_graph_clicked();

    void on_btn_plot_clicked();

private:

    Ui::MainWindow *ui;

    /*! \brief  List that contains data vectors
     */
    QList<QVector<double>> _list;

    /*! \brief  list that contains maxed size data vectors
     */
    QList<QVector<double>> _cache_list;

    /*! \brief  Number of channels
     */
    int channels;

    /*! \brief  Number of samples
     */
    int samples;

    /*! \brief  Data frequency
     */
    double frequency;

    /*! \brief  add data in cache
     *  \param  i   index of the channel to update
     *  \param  s   sample to add
     */
    void cacheAdd(int i, double s);
};
#endif // MAINWINDOW_H
