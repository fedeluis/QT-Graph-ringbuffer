#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    /*! \brief  Add point in graph
     *  \param  x   Coordinate for X-axis
     *  \param  y   Coordinate for Y-axis
     */
    void addPoint(double x, double y);
    /*! \brief Clear all points on the graph
     */
    void clearData();
    /*! \brief  Updates graph with new points
     */
    void plot();

private slots:
    void on_btn_plot_clicked();

    void on_btn_clear_clicked();

    void on_btn_rescale_clicked();

private:
    Ui::MainWindow *ui;

    /*! \brief  Vectors where point are stored
     */
    QVector<double> data_x, data_y;
};
#endif // MAINWINDOW_H
