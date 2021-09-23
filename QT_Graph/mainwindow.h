#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <eigen3/Eigen/Dense>

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
     *  \param  n   number of channels
     */
    void setChannels(int n);

    /*! \brief  Set number of samples
     *  \param  n   number of samples
     */
    void setSamples(int n);

    /*! \brief  Set up of graph' parameters
     */
    void graphSetup();

private slots:

    void on_btn_clear_clicked();

    void on_btn_rescale_clicked();

private:

    Ui::MainWindow *ui;

    /*! \brief  Vectors where point are stored
     */
    //QVector<double> data_x, data_y;
    /*! \brief  List that contains data vectors
     */
    QList<QVector<double>> list;

    /*! \brief  Number of channels
     */
    int channels;

    /*! \brief  Number of samples
     */
    int samples;
};
#endif // MAINWINDOW_H
