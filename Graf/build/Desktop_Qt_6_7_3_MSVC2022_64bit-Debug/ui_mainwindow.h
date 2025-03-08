/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGroupBox *groupBox;
    QRadioButton *radioOriented;
    QRadioButton *radioUnoriented;
    QPushButton *checkTreeButton;
    QPushButton *findRootButton;
    QPushButton *showConnectedComponentsButton;
    QPushButton *runKruskalButton;
    QPushButton *calculateGenericTreeButton;
    QPushButton *calculatePrimMSTButton;
    QPushButton *HighlightButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(40, 10, 120, 80));
        radioOriented = new QRadioButton(groupBox);
        radioOriented->setObjectName("radioOriented");
        radioOriented->setGeometry(QRect(0, 20, 112, 26));
        radioUnoriented = new QRadioButton(groupBox);
        radioUnoriented->setObjectName("radioUnoriented");
        radioUnoriented->setGeometry(QRect(0, 50, 112, 26));
        radioUnoriented->setChecked(true);
        checkTreeButton = new QPushButton(centralwidget);
        checkTreeButton->setObjectName("checkTreeButton");
        checkTreeButton->setGeometry(QRect(40, 110, 81, 31));
        findRootButton = new QPushButton(centralwidget);
        findRootButton->setObjectName("findRootButton");
        findRootButton->setGeometry(QRect(40, 160, 83, 29));
        showConnectedComponentsButton = new QPushButton(centralwidget);
        showConnectedComponentsButton->setObjectName("showConnectedComponentsButton");
        showConnectedComponentsButton->setGeometry(QRect(40, 210, 83, 29));
        runKruskalButton = new QPushButton(centralwidget);
        runKruskalButton->setObjectName("runKruskalButton");
        runKruskalButton->setGeometry(QRect(140, 290, 83, 29));
        calculateGenericTreeButton = new QPushButton(centralwidget);
        calculateGenericTreeButton->setObjectName("calculateGenericTreeButton");
        calculateGenericTreeButton->setGeometry(QRect(50, 290, 83, 29));
        calculatePrimMSTButton = new QPushButton(centralwidget);
        calculatePrimMSTButton->setObjectName("calculatePrimMSTButton");
        calculatePrimMSTButton->setGeometry(QRect(230, 290, 83, 29));
        HighlightButton = new QPushButton(centralwidget);
        HighlightButton->setObjectName("HighlightButton");
        HighlightButton->setGeometry(QRect(320, 290, 83, 29));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Graf", nullptr));
        radioOriented->setText(QCoreApplication::translate("MainWindow", "Orientat", nullptr));
        radioUnoriented->setText(QCoreApplication::translate("MainWindow", "Neorientat", nullptr));
        checkTreeButton->setText(QCoreApplication::translate("MainWindow", "Verifica arbore", nullptr));
        findRootButton->setText(QCoreApplication::translate("MainWindow", "CautaRadacina", nullptr));
        showConnectedComponentsButton->setText(QCoreApplication::translate("MainWindow", "ShowConnectedComponents", nullptr));
        runKruskalButton->setText(QCoreApplication::translate("MainWindow", "Kruskall", nullptr));
        calculateGenericTreeButton->setText(QCoreApplication::translate("MainWindow", "Generic", nullptr));
        calculatePrimMSTButton->setText(QCoreApplication::translate("MainWindow", "Prim", nullptr));
        HighlightButton->setText(QCoreApplication::translate("MainWindow", "boruvka", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
