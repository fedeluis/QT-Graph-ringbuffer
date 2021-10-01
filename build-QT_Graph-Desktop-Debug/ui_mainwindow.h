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
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
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
        spin_x_axis->setValue(10);
        spin_y_axis = new QSpinBox(centralwidget);
        spin_y_axis->setObjectName(QString::fromUtf8("spin_y_axis"));
        spin_y_axis->setGeometry(QRect(240, 440, 171, 26));
        spin_y_axis->setMinimum(10);
        spin_y_axis->setMaximum(200);
        spin_y_axis->setSingleStep(10);
        spin_y_axis->setValue(20);
        btn_rescale = new QPushButton(centralwidget);
        btn_rescale->setObjectName(QString::fromUtf8("btn_rescale"));
        btn_rescale->setGeometry(QRect(430, 414, 89, 51));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(40, 490, 121, 17));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setEnabled(true);
        label_2->setGeometry(QRect(40, 410, 67, 17));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(240, 410, 67, 17));
        combo_graph = new QComboBox(centralwidget);
        combo_graph->setObjectName(QString::fromUtf8("combo_graph"));
        combo_graph->setGeometry(QRect(170, 490, 101, 25));
        btn_graph = new QPushButton(centralwidget);
        btn_graph->setObjectName(QString::fromUtf8("btn_graph"));
        btn_graph->setGeometry(QRect(290, 490, 101, 25));
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
        label->setText(QApplication::translate("MainWindow", "Graph selection:", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "X Axis", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "Y Axis", nullptr));
        btn_graph->setText(QApplication::translate("MainWindow", "Select graph", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
