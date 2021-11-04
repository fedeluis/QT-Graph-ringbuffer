/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *btn_clear;
    QCustomPlot *plot;
    QSpinBox *spin_x_axis;
    QSpinBox *spin_y_axis;
    QPushButton *btn_rescale;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *combo_graph;
    QPushButton *btn_graph;
    QPushButton *btn_plot;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(880, 556);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btn_clear = new QPushButton(centralwidget);
        btn_clear->setObjectName(QString::fromUtf8("btn_clear"));
        btn_clear->setGeometry(QRect(210, 10, 51, 25));
        plot = new QCustomPlot(centralwidget);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(270, 10, 601, 511));
        spin_x_axis = new QSpinBox(centralwidget);
        spin_x_axis->setObjectName(QString::fromUtf8("spin_x_axis"));
        spin_x_axis->setGeometry(QRect(10, 30, 81, 26));
        spin_x_axis->setMinimum(1);
        spin_x_axis->setMaximum(10);
        spin_x_axis->setValue(10);
        spin_y_axis = new QSpinBox(centralwidget);
        spin_y_axis->setObjectName(QString::fromUtf8("spin_y_axis"));
        spin_y_axis->setGeometry(QRect(10, 90, 81, 26));
        spin_y_axis->setMinimum(10);
        spin_y_axis->setMaximum(200);
        spin_y_axis->setSingleStep(5);
        spin_y_axis->setValue(15);
        btn_rescale = new QPushButton(centralwidget);
        btn_rescale->setObjectName(QString::fromUtf8("btn_rescale"));
        btn_rescale->setGeometry(QRect(110, 10, 61, 101));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 150, 121, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(10, 10, 81, 17));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 70, 71, 17));
        combo_graph = new QComboBox(centralwidget);
        combo_graph->setObjectName(QString::fromUtf8("combo_graph"));
        combo_graph->setGeometry(QRect(10, 180, 121, 25));
        btn_graph = new QPushButton(centralwidget);
        btn_graph->setObjectName(QString::fromUtf8("btn_graph"));
        btn_graph->setGeometry(QRect(140, 150, 91, 61));
        btn_plot = new QPushButton(centralwidget);
        btn_plot->setObjectName(QString::fromUtf8("btn_plot"));
        btn_plot->setGeometry(QRect(30, 260, 181, 25));
        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        btn_clear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
        btn_rescale->setText(QApplication::translate("MainWindow", "Rescale", nullptr));
        label->setText(QApplication::translate("MainWindow", "Graph selection", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "X Axis", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Y Axis", nullptr));
        btn_graph->setText(QApplication::translate("MainWindow", "Select graph", nullptr));
        btn_plot->setText(QApplication::translate("MainWindow", "Plot", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
