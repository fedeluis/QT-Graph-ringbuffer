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
    QPushButton *btn_plot;
    QPushButton *btn_clear;
    QCustomPlot *plot;
    QSpinBox *spin_x_axis;
    QSpinBox *spin_y_axis;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        btn_plot = new QPushButton(centralwidget);
        btn_plot->setObjectName(QString::fromUtf8("btn_plot"));
        btn_plot->setGeometry(QRect(510, 440, 89, 25));
        btn_clear = new QPushButton(centralwidget);
        btn_clear->setObjectName(QString::fromUtf8("btn_clear"));
        btn_clear->setGeometry(QRect(640, 440, 89, 25));
        plot = new QCustomPlot(centralwidget);
        plot->setObjectName(QString::fromUtf8("plot"));
        plot->setGeometry(QRect(40, 50, 691, 351));
        spin_x_axis = new QSpinBox(centralwidget);
        spin_x_axis->setObjectName(QString::fromUtf8("spin_x_axis"));
        spin_x_axis->setGeometry(QRect(40, 440, 181, 26));
        spin_x_axis->setMinimum(1);
        spin_x_axis->setMaximum(10);
        spin_y_axis = new QSpinBox(centralwidget);
        spin_y_axis->setObjectName(QString::fromUtf8("spin_y_axis"));
        spin_y_axis->setGeometry(QRect(240, 440, 171, 26));
        spin_y_axis->setMinimum(10);
        spin_y_axis->setMaximum(200);
        spin_y_axis->setSingleStep(10);
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
        btn_plot->setText(QApplication::translate("MainWindow", "Plot", nullptr));
        btn_clear->setText(QApplication::translate("MainWindow", "Clear", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
